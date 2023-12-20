#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include<bitset>
using namespace std;
 
struct NODE{
	double weight;//权值 
	int lchild;//左孩子 
	int rchild;//右孩子 
	int parent; 
};
typedef NODE HT[];	//静态三叉链表 
 
int Getchar(char message, char sign[], int sum[], int len){		
//读取字符，若与之前的字符重复则个数加一，否则将此字符新加入字符数组。返回字符数组长度 
	int flag=0;
	for (int i=0; i<len; i++){
		if (message == sign[i]){
			flag = 1;		//遇到之前存有的字符，直接sum[i]++ 
			sum[i]++;
			break;
		}
	}
	if (flag == 0){		//若遇到新字符，将新字符存入sign[] 
		sign[len] = message;
		sum[len]++;
		len++;
	}
	return len;		//不同种字符个数 
}
 
void Percent(int sum[], double percent[], int len, int num){//计算字符权值并存入数组
	for(int i=0; i<len; i++){
		percent[i] = (double)sum[i]/num;
	}
}
void InitTree(HT T, double p[], int n, int m){		//初始化哈夫曼树函数，将权值及左右子树，双亲输入HT结构体数组中。 
	for (int i=0; i<n; i++){
		T[i].weight = p[i];
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
	for (int i=n; i<m; i++){
		T[i].weight = 0;
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
}
void SelectMin(HT T, int n, int &p1, int &p2){		//选出HT中权重最小的两个节点 
	int i,j;
	for (i=0; i<=n; i++){   //先找到一个 
		if (T[i].parent == -1) {
			p1 = i; 
			break;
		}
	}	
	for (j=i+1; j<=n; j++){  
		if(T[j].parent == -1)
		{
			p2 = j; 
			break;
		}
	}
	for (i=0; i<=n; i++){  //再寻找最小的节点 
		if((T[p1].weight > T[i].weight) && (T[i].parent == -1) && (p2 != i)) 
		    p1 = i;
	}
	for (j=0; j<=n; j++){
		if((T[p2].weight > T[j].weight) && (T[j].parent == -1) && (p1 != j)) 
		    p2 = j;
	}
}
void CreateTree(HT T, int n, int m){		//前n个是叶节点，从第n个结点创造哈夫曼树 
	int i,p1,p2;
	for (i=n; i<m; i++){	
		SelectMin(T, i-1, p1, p2);	
		T[p1].parent = T[p2].parent = i;	//产生新节点从n开始存放
		T[i].lchild = p1;
		T[i].rchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight; //新的权值等于两字树的权值和，继续去比较 
	}
}

 
int FindMostLeft(HT T, int m){		//找到并返回哈夫曼树最左结点下标，防止其编码为全0 
	int p = m-1;
	while (T[p].lchild != -1) p = T[p].lchild;
	return p;
}
 
void Encode(HT T, string code[], int n, int m){		//生成每种字符的哈夫曼编码 
	for (int i=0; i<n; i++){
		int j = i;
		int p = FindMostLeft(T, m);
		string temp;
		while (T[j].parent != -1){
			int k = T[j].parent;
			if (j == p) temp += "10";//如果为哈夫曼最左树，则在末尾加上一个1，防止补码时全0译码错误 
			else if (T[k].lchild == j) 
			    temp += '0';		//左儿子编码为0
			else if (T[k].rchild == j) 
			    temp += '1';		//右儿子编码为1 
			j = k;  //继续回溯遍历 
		}
		reverse(temp.begin(),temp.end());  //将元素颠倒顺序放置 
		code[i] = temp;  //将编码存储在code数组里面 
	}
}
 
string Read(char message[], char sign[], string code[]){ //文章变成字符串 
    string final;	//final为整个文章翻译成的01串 
    cout << "读出二进制哈夫曼编码为：" <<endl; 
    for (int i=0; i<strlen(message); i++){ //遍历文章字符数组message[]和哈夫曼编码字符数组sign[]
    	for (int j=0; j<strlen(sign); j++)
		if (message[i] == sign[j]){
    		final += code[j];  //若相同，则把对应的编码存进字符串 
		}
    }
    cout << final;
    cout <<endl; 
 	return final;
}
 
string BitStrToStr(string str){ 	//将二进制01字符串每八位压缩成一个ASCII码 
	string s;
    int sum = 0; //代表十进制数 
    int count = 0;
    for(int i=0; i<str.length(); i++){
        count++;
        if(str[i] == '1') 
		    sum = sum*2 +1;
        else 
		    sum = sum * 2;
        if(count == 8){		//等于8位时直接将二进制的ASCII作为char存入s中 
            s = s + char(sum);
            sum = 0;	
			count = 0;	
        }
    }
    if(count < 8){		//不足8位时直接在最后补0
        while(count < 8){
            sum =sum*2;
            count++;
        }
        s += char(sum);
    }
    return s;
}
 
string StrToBitStr(string str)		//将压缩string(每个字符代表八位二进制哈夫曼编码) 
{   
    string s;
    for(int i = 0; i<str.length()-1; i++){
        bitset<8> bits = bitset<8>(str[i]);	//创建一个名为bits的位集，然后将字符串str中的第i个字符转换为一个8位的二进制数，并存储在bits中。 
        for(int j = 7; j >= 0; j--)			//bits倒序存储，故反向加入s 
            s += '0'+bits[j];
    }
    return s;
}
 
void Compress(string final){		//将BitStrToStr函数中得到的压缩string存入二进制文件 
	cout << endl;
    ofstream outfile ( "zip.dat", ios::out | ios::binary );  //以二进制的方式写入文件zip.dat 
    string s = BitStrToStr(final); //每八位压缩 
    outfile.write(s.c_str(), s.size());//s.c_str()是将字符串s转换为字符数组，s.size()是要写入的字符数
    outfile.close();
	cout << "编码压缩完成" <<endl;
}
 
void CalculateRate (double percent[], string code[], int n){		//计算哈夫曼树平均编码长度与压缩率 
	double avercode = 0.0;
	for (int i=0; i<n; i++){
		avercode += (double)code[i].length()*percent[i];  //平均长度乘出现频率 
	}
	cout << "哈夫曼树平均编码长度为：" << avercode <<endl;
	cout << "哈夫曼树压缩率为：" << 1-avercode/8 <<endl; //一个字节有8位 
}
 
void DecodeFile(char sign[],int n, string code[]){	//解码并写入译码文件 
	cout <<endl;
	ifstream inFile("zip.dat", ifstream::in | ifstream::binary);
    if(!inFile){
        cout<<"Error!"<<endl;
    }
    ofstream outFile("decode.txt", ios::out);
    string ret = "";  //定义一个为空的字符串 
    string stack;
    while(inFile.good()){
        ret += inFile.get(); //若文件不空，读取每个字符，添加到字符串中 
    }
    inFile.close();
    ret = StrToBitStr(ret);		//将压缩串转换为01串
    for(int i = 0; i < ret.length(); i++){
		if(ret[i] == '1')
		    stack += '1';
        else if(ret[i] == '0')
		    stack +='0';
        for(int j = 0; j < n; j++){
            if(code[j] == stack){		//stack依次与保存的字符集01串匹配 
                outFile.write(&sign[j], sizeof(sign[j]));
                stack.clear();
            }
        }
    }
	cout << "解码完成" <<endl; 
}
 
bool Compare(char message[]){		//比较原文件和译码文件 
	string s_message = message;
	ifstream readFile("decode.txt");
	char decode[2000] = { 0 };
	readFile.getline(decode, 2000, 0); 
	readFile.close();
	cout << "译码文件:" <<endl;
	cout << decode <<endl;
	string s_decode = decode;
	if (s_message == s_decode) 
	    return true;
	else 
	    return false;
}
 
int main(){
	ifstream readFile("yingwen.txt");
	char message[2000] = { 0 };
	readFile.getline(message, 2000);						
	cout << "原文本:" <<endl;
	cout << message << endl;
	readFile.close();
	int sum_num = strlen(message);	//定义总字符数 
	cout << "总字符数:" << sum_num <<endl;		
	char sign[strlen(message)]={0};		//储存出现的不同的字符 
	int sum[strlen(message)]={0};		//储存每个字符出现的次数 
	double percent[strlen(message)] = {0};//储存每个字符的比例 
	int len = 1;
	sum[0] = 1;
	sign[0] = message[0]; //均为初始化操作
	 
	for (int i=1; i<strlen(message); i++){ 
	    len = Getchar(message[i], sign, sum, len);//1.读取字符，返回字符长度 
	}
	Percent(sum, percent, len, sum_num);//2.计算权值 
	int n = len;	//开始构造哈夫曼树，n为叶子数,m为结点总数
	int m = 2*n-1; 
	NODE HT[m];
	InitTree(HT, percent, n, m);//3.初始哈夫曼树 
	CreateTree(HT, n, m);	//4.构建哈夫曼树（选最小的） 
	string code[len];		//储存每个字符的哈夫曼编码
	Encode(HT, code, n, m);	//5.对每种字符开始进行01串编码
	cout << "字符" << "	  " << "出现次数" << "	" << "权值"<< "		" << "	哈夫曼编码" <<endl; 
	for (int i=0; i<len; i++){
		cout << sign[i] << "	  " << sum[i] << "		" << percent[i] << "		" << code[i] <<endl;
	}
	string final_code = Read(message, sign, code);	//6.将文章转换成串，final code为整个文章转码的01串 
	Compress(final_code);    //7.压缩01串，将其转换成ascii码存储 
	CalculateRate(percent, code, n);	//8.计算平均编码长度和压缩率 
	DecodeFile(sign, n, code);		//9.二进制文件译码
	cout << "原文件:" <<endl;
	cout << message <<endl; 
	if (Compare(message)) cout << "经比较，原文件与译码文件相同"<<endl;		//10.比较两个文件 
	else cout << "经比较，原文件与译码文件不同" <<endl; 
    return 0;
}
