#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include<bitset>
using namespace std;
 
struct NODE{
	double weight;//Ȩֵ 
	int lchild;//���� 
	int rchild;//�Һ��� 
	int parent; 
};
typedef NODE HT[];	//��̬�������� 
 
int Getchar(char message, char sign[], int sum[], int len){		
//��ȡ�ַ�������֮ǰ���ַ��ظ��������һ�����򽫴��ַ��¼����ַ����顣�����ַ����鳤�� 
	int flag=0;
	for (int i=0; i<len; i++){
		if (message == sign[i]){
			flag = 1;		//����֮ǰ���е��ַ���ֱ��sum[i]++ 
			sum[i]++;
			break;
		}
	}
	if (flag == 0){		//���������ַ��������ַ�����sign[] 
		sign[len] = message;
		sum[len]++;
		len++;
	}
	return len;		//��ͬ���ַ����� 
}
 
void Percent(int sum[], double percent[], int len, int num){//�����ַ�Ȩֵ����������
	for(int i=0; i<len; i++){
		percent[i] = (double)sum[i]/num;
	}
}
void InitTree(HT T, double p[], int n, int m){		//��ʼ������������������Ȩֵ������������˫������HT�ṹ�������С� 
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
void SelectMin(HT T, int n, int &p1, int &p2){		//ѡ��HT��Ȩ����С�������ڵ� 
	int i,j;
	for (i=0; i<=n; i++){   //���ҵ�һ�� 
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
	for (i=0; i<=n; i++){  //��Ѱ����С�Ľڵ� 
		if((T[p1].weight > T[i].weight) && (T[i].parent == -1) && (p2 != i)) 
		    p1 = i;
	}
	for (j=0; j<=n; j++){
		if((T[p2].weight > T[j].weight) && (T[j].parent == -1) && (p1 != j)) 
		    p2 = j;
	}
}
void CreateTree(HT T, int n, int m){		//ǰn����Ҷ�ڵ㣬�ӵ�n����㴴��������� 
	int i,p1,p2;
	for (i=n; i<m; i++){	
		SelectMin(T, i-1, p1, p2);	
		T[p1].parent = T[p2].parent = i;	//�����½ڵ��n��ʼ���
		T[i].lchild = p1;
		T[i].rchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight; //�µ�Ȩֵ������������Ȩֵ�ͣ�����ȥ�Ƚ� 
	}
}

 
int FindMostLeft(HT T, int m){		//�ҵ������ع��������������±꣬��ֹ�����Ϊȫ0 
	int p = m-1;
	while (T[p].lchild != -1) p = T[p].lchild;
	return p;
}
 
void Encode(HT T, string code[], int n, int m){		//����ÿ���ַ��Ĺ��������� 
	for (int i=0; i<n; i++){
		int j = i;
		int p = FindMostLeft(T, m);
		string temp;
		while (T[j].parent != -1){
			int k = T[j].parent;
			if (j == p) temp += "10";//���Ϊ������������������ĩβ����һ��1����ֹ����ʱȫ0������� 
			else if (T[k].lchild == j) 
			    temp += '0';		//����ӱ���Ϊ0
			else if (T[k].rchild == j) 
			    temp += '1';		//�Ҷ��ӱ���Ϊ1 
			j = k;  //�������ݱ��� 
		}
		reverse(temp.begin(),temp.end());  //��Ԫ�صߵ�˳����� 
		code[i] = temp;  //������洢��code�������� 
	}
}
 
string Read(char message[], char sign[], string code[]){ //���±���ַ��� 
    string final;	//finalΪ�������·���ɵ�01�� 
    cout << "���������ƹ���������Ϊ��" <<endl; 
    for (int i=0; i<strlen(message); i++){ //���������ַ�����message[]�͹����������ַ�����sign[]
    	for (int j=0; j<strlen(sign); j++)
		if (message[i] == sign[j]){
    		final += code[j];  //����ͬ����Ѷ�Ӧ�ı������ַ��� 
		}
    }
    cout << final;
    cout <<endl; 
 	return final;
}
 
string BitStrToStr(string str){ 	//��������01�ַ���ÿ��λѹ����һ��ASCII�� 
	string s;
    int sum = 0; //����ʮ������ 
    int count = 0;
    for(int i=0; i<str.length(); i++){
        count++;
        if(str[i] == '1') 
		    sum = sum*2 +1;
        else 
		    sum = sum * 2;
        if(count == 8){		//����8λʱֱ�ӽ������Ƶ�ASCII��Ϊchar����s�� 
            s = s + char(sum);
            sum = 0;	
			count = 0;	
        }
    }
    if(count < 8){		//����8λʱֱ�������0
        while(count < 8){
            sum =sum*2;
            count++;
        }
        s += char(sum);
    }
    return s;
}
 
string StrToBitStr(string str)		//��ѹ��string(ÿ���ַ������λ�����ƹ���������) 
{   
    string s;
    for(int i = 0; i<str.length()-1; i++){
        bitset<8> bits = bitset<8>(str[i]);	//����һ����Ϊbits��λ����Ȼ���ַ���str�еĵ�i���ַ�ת��Ϊһ��8λ�Ķ������������洢��bits�С� 
        for(int j = 7; j >= 0; j--)			//bits����洢���ʷ������s 
            s += '0'+bits[j];
    }
    return s;
}
 
void Compress(string final){		//��BitStrToStr�����еõ���ѹ��string����������ļ� 
	cout << endl;
    ofstream outfile ( "zip.dat", ios::out | ios::binary );  //�Զ����Ƶķ�ʽд���ļ�zip.dat 
    string s = BitStrToStr(final); //ÿ��λѹ�� 
    outfile.write(s.c_str(), s.size());//s.c_str()�ǽ��ַ���sת��Ϊ�ַ����飬s.size()��Ҫд����ַ���
    outfile.close();
	cout << "����ѹ�����" <<endl;
}
 
void CalculateRate (double percent[], string code[], int n){		//�����������ƽ�����볤����ѹ���� 
	double avercode = 0.0;
	for (int i=0; i<n; i++){
		avercode += (double)code[i].length()*percent[i];  //ƽ�����ȳ˳���Ƶ�� 
	}
	cout << "��������ƽ�����볤��Ϊ��" << avercode <<endl;
	cout << "��������ѹ����Ϊ��" << 1-avercode/8 <<endl; //һ���ֽ���8λ 
}
 
void DecodeFile(char sign[],int n, string code[]){	//���벢д�������ļ� 
	cout <<endl;
	ifstream inFile("zip.dat", ifstream::in | ifstream::binary);
    if(!inFile){
        cout<<"Error!"<<endl;
    }
    ofstream outFile("decode.txt", ios::out);
    string ret = "";  //����һ��Ϊ�յ��ַ��� 
    string stack;
    while(inFile.good()){
        ret += inFile.get(); //���ļ����գ���ȡÿ���ַ�����ӵ��ַ����� 
    }
    inFile.close();
    ret = StrToBitStr(ret);		//��ѹ����ת��Ϊ01��
    for(int i = 0; i < ret.length(); i++){
		if(ret[i] == '1')
		    stack += '1';
        else if(ret[i] == '0')
		    stack +='0';
        for(int j = 0; j < n; j++){
            if(code[j] == stack){		//stack�����뱣����ַ���01��ƥ�� 
                outFile.write(&sign[j], sizeof(sign[j]));
                stack.clear();
            }
        }
    }
	cout << "�������" <<endl; 
}
 
bool Compare(char message[]){		//�Ƚ�ԭ�ļ��������ļ� 
	string s_message = message;
	ifstream readFile("decode.txt");
	char decode[2000] = { 0 };
	readFile.getline(decode, 2000, 0); 
	readFile.close();
	cout << "�����ļ�:" <<endl;
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
	cout << "ԭ�ı�:" <<endl;
	cout << message << endl;
	readFile.close();
	int sum_num = strlen(message);	//�������ַ��� 
	cout << "���ַ���:" << sum_num <<endl;		
	char sign[strlen(message)]={0};		//������ֵĲ�ͬ���ַ� 
	int sum[strlen(message)]={0};		//����ÿ���ַ����ֵĴ��� 
	double percent[strlen(message)] = {0};//����ÿ���ַ��ı��� 
	int len = 1;
	sum[0] = 1;
	sign[0] = message[0]; //��Ϊ��ʼ������
	 
	for (int i=1; i<strlen(message); i++){ 
	    len = Getchar(message[i], sign, sum, len);//1.��ȡ�ַ��������ַ����� 
	}
	Percent(sum, percent, len, sum_num);//2.����Ȩֵ 
	int n = len;	//��ʼ�������������nΪҶ����,mΪ�������
	int m = 2*n-1; 
	NODE HT[m];
	InitTree(HT, percent, n, m);//3.��ʼ�������� 
	CreateTree(HT, n, m);	//4.��������������ѡ��С�ģ� 
	string code[len];		//����ÿ���ַ��Ĺ���������
	Encode(HT, code, n, m);	//5.��ÿ���ַ���ʼ����01������
	cout << "�ַ�" << "	  " << "���ִ���" << "	" << "Ȩֵ"<< "		" << "	����������" <<endl; 
	for (int i=0; i<len; i++){
		cout << sign[i] << "	  " << sum[i] << "		" << percent[i] << "		" << code[i] <<endl;
	}
	string final_code = Read(message, sign, code);	//6.������ת���ɴ���final codeΪ��������ת���01�� 
	Compress(final_code);    //7.ѹ��01��������ת����ascii��洢 
	CalculateRate(percent, code, n);	//8.����ƽ�����볤�Ⱥ�ѹ���� 
	DecodeFile(sign, n, code);		//9.�������ļ�����
	cout << "ԭ�ļ�:" <<endl;
	cout << message <<endl; 
	if (Compare(message)) cout << "���Ƚϣ�ԭ�ļ��������ļ���ͬ"<<endl;		//10.�Ƚ������ļ� 
	else cout << "���Ƚϣ�ԭ�ļ��������ļ���ͬ" <<endl; 
    return 0;
}
