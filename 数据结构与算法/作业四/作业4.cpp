//作业四：查找结构及其应用 
#include<iostream>
#include<fstream>
using namespace std;
#define MAX 1024

struct TreeNode{
	int data;
	struct TreeNode *lchild,*rchild;
}; 
typedef TreeNode *BST;
int count=0;//查找次数
int ans = 0;//数组下标 
int count1=0;//记录折半查找次数 

//插入算法 
void Insert (BST &T,int k){
	if(T==NULL){
		T=new TreeNode;
		T->lchild=NULL;
		T->rchild=NULL;
		T->data = k;
	}
	else if(T->data==k){
		cout<<"关键字已经存在,请继续插入其它关键字"<<endl;
	}
	else if(T->data<k){
		Insert(T->rchild,k);
	}
	else{
		Insert(T->lchild,k);
	}
}

//查找算法
TreeNode *Search(BST &T,int k){
	if(T==NULL){
		return T;
	}
	count++; 
	if(T->data==k){
		return T;
	}
	else if(T->data>k){
		return Search(T->lchild,k);
	}
	else {
		return Search(T->rchild,k);
	}	
}	

//删除BST树的最小值的节点并返回该最小值 
int DeleteMin(BST &T){
    int tmp;
    BST p;
    if(T->lchild==NULL){
        p=T;
        tmp=T->data ;
        T=T->rchild ;
        delete p;
        return tmp;
}

    else{
        DeleteMin(T->lchild);
    }
}

//删除算法
void Delete(BST &T,int k){//删除BST树的关键字为k的节点 
    if(T!=NULL){
        if(T->data<k){
            Delete(T->rchild,k);//递归的到右子树去删除 
        }
        else if(T->data>k){
            Delete(T->lchild,k);//递归的到左子树去删除 
        }
        else{
            if(T->lchild==NULL){
                T=T->rchild ;//右链继承 
            }
            else if(T->rchild==NULL){
                T=T->lchild ;//左链继承 
            }
            else{
                T->data=DeleteMin(T->rchild); //递归删除 
            }
        }
    }
    else{
		cout<<"节点不存在"<<endl;
	}
}

//排序算法
void Order(BST &T,int list[]){
	if(T==NULL){
		return;
	}
	Order(T->rchild,list);
	list[ans]=T->data;
	ans++;
	Order(T->rchild,list);
} 

//折半查找算法
int HalfSearch(int L[],int k,int high){
	int low=0;
	int mid=0;
	
	while(low<high){
		mid=(low+high)/2;
		count1++;
		if(L[mid]==k){
			return count1;
		} 
		else if(L[mid]>k){
			high=mid-1;
		}
		else{
			low = mid+1;
		}
	}
	return 0;
}

//创建BST树1
BST Create1(){
	fstream in;
	in.open("shuju1.txt");
	BST p=NULL;
	int k;
	for(int i=0;i<MAX;i++){
		in>>k;
		Insert(p,k);
	}
	in.close();
	return p;
}  
BST Create2(){
    fstream in;
	in.open("shuju2.txt");
	BST p=NULL;
	int k;
	for(int i=0;i<MAX;i++){
		in>>k;
		Insert(p,k);
	}
	in.close();
	return p;	
}
//求查找的次数 
void cishu(BST &T){
	float sum1=0.0,sum2=0.0;//奇数是查找成功，偶数是查找失败 
	BST p=NULL;
	for(int i=0;i<MAX;i++){
		count=0;
		p=Search(T,2*i+1);
		sum1=sum1+count;
	}
	cout<<"查找成功的平均次数为："<<float(sum1/MAX)<<endl;
    for(int i=0;i<MAX;i++){
		count=0;
		p=Search(T,2*i);
		sum2=sum2+count;
	}
	cout<<"查找失败的平均次数为："<<float(sum2/MAX)<<endl;
}


void testhalf(){//测试折半查找平均查找长度 
    int i,sum=0;
    float aver;
    int a[MAX];
    for(int i=0;i<MAX;i++){
     a[i]=2*i+1;
 }   
    for(i=0;i<MAX;i++){
     count1=0;
        HalfSearch(a,2*i+1,MAX-1);
        sum+=count1;
    }
    aver=(float)sum/MAX;//平均查找总次数 
    cout<<"折半查找成功平均长度为"<<aver<<endl; 
    sum=0;
	ans=0;
    for(i=0;i<MAX;i++){
        count1=0;
        HalfSearch(a,2*i,MAX-1);
        sum+=count1;
    }
    HalfSearch(a,2048,MAX-1);
    sum+=count1;
    aver=(float)sum/(MAX+1);
    cout<<"折半查找失败平均长度为"<<aver<<endl;  
}
int main() {
    BST T1 = Create1();
    BST T2 = Create2();

    cout << "测试插入功能：" << endl;
    int insertValue = 6;
    cout << "插入的值为 " << insertValue<< endl;
    Insert(T1, insertValue);
    cout << "数值 " << insertValue << "已经成功插入" << endl;

    cout << "\n测试查找功能：" << endl;
    int searchValue = 8;
    cout << "查找的值为 " << searchValue<< endl;
    TreeNode* searchResult = Search(T1, searchValue);
    if (searchResult != NULL) {
        cout << "数值 " << searchValue << " 已经被找到" << endl;
    } else {
        cout << "数值 " << searchValue << " 没有被找到" << endl;
    }

    cout << "\n测试删除功能" << endl;
    int deleteValue = 6;
    cout << "删除的数值为 " << deleteValue << endl;
    Delete(T1, deleteValue);
    cout << "数值 " << deleteValue << " 已经成功删除" << endl;

    cout << "\n第一组测试数据：" << endl;
    cishu(T1);
    testhalf();
    cout << "第二组测试数据：" << endl;
    cishu(T2);
    testhalf();

    return 0;
}


/*BST查找和折半查找的时间复杂度都是O(logn),但是如果根据有规律的数字建树就会导致BST不能够
满足平衡性深度会‘深深浅浅’，当使用特定的数据进行查询的时候就会可能导致性能下降，比如本次实验，
用顺序序列建树的时候，就会形成一条链，也就是右斜树，导致每次查找后面的数据性能特别差，
对于随机的数进行查找效果仍然很差。但是如果给的数字不是规律的，二是随机的，比如第二组测试数据，
我们发现他的平均查找时间性能和折半查找时间性能相差很小，如果我们的数字更随机一点，
那么我们认为折半查找和BST查找的时间性能差不多。
*/
