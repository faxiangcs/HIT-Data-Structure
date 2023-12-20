#include<iostream>
#include<string.h>
#include<cctype>
using namespace std;

#define ERROR 0
#define OK 1
#define MAXSIZE 50
//定义二叉树 
struct Node
{
	char data;
	struct Node *lchild;
	struct Node *rchild;
};
typedef Node *BiTree;
//定义顺序栈，用于非递归存储
struct Lnode
{
    struct Node *data[MAXSIZE];//定义最大值是50，存放树节点的地址 
	int top=-1;
};
typedef Lnode *Stack; 
//定义队列，用于层序遍历 
struct Qnode
{
	struct Node *data[MAXSIZE];
	int front,rear;
	int flag[MAXSIZE]={0};//用于计算二叉树的宽度 
};
typedef Qnode *Queue;
//建立二叉树(递归实现) 
void CreatBiTree(BiTree &T){
	char ch;
	cin>>ch;
	//#代表是空树 
	if(ch=='#'){
		T=NULL;
	}
	else{
		T=new Node;
		T->data=ch;  //生成根节点
		CreatBiTree(T->lchild);  //建立左字树 
	    CreatBiTree(T->rchild);  //建立右子树 
	}
}
//先序遍历二叉树（递归）
void PreOrder(BiTree &T){
	if(T!=NULL){
		cout<<T->data<<" ";
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}	
}
//中序遍历二叉树（递归）
void InOrder(BiTree &T){
	if(T!=NULL){
		InOrder(T->lchild);
		cout<<T->data<<" ";
		InOrder(T->rchild);
	}
} 
//后续遍历二叉树（递归）
void PostOrder(BiTree &T){
	if(T!=NULL){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout<<T->data<<" ";
	}	
}
//先序遍历二叉树（非递归）
void PreOrders(BiTree &T){
	if(T==NULL){
		cout<<"错误";
		return; 
	}
	Stack s=new Lnode;
	while(T!=NULL||s->top!=-1){
		while(T!=NULL){
			cout<<T->data<<" ";  //输出根的值 
			if(s->top==MAXSIZE-1){
				cout<<"栈溢出"<<endl;
				exit(0);
			}
			s->data[++s->top]=T;  //然后遍历左子树 
			T=T->lchild;
		}
		if(s->top!=-1){
			T=s->data[s->top--];  
			T=T->rchild;  //遍历右子树 
		}
	} 
} 
//中序遍历二叉树（非递归）
void InOrders(BiTree &T){
	if(T==NULL){
		cout<<"错误";
		return; 
	}
	Stack s=new Lnode;
	while(T!=NULL||s->top!=-1){
		while(T!=NULL){
			if(s->top==MAXSIZE-1){
				cout<<"栈溢出"<<endl;
				exit(0);
			}
			s->data[++s->top]=T;
			T=T->lchild;
		}
		if(s->top!=-1){
			T=s->data[s->top--];
			cout<<T->data<<" ";  
			T=T->rchild;
		}
	} 
} 
//后续遍历二叉树（非递归）
void PostOrders(BiTree &T){
    if(T==NULL){
		cout<<"错误";
		return; 
	}
	Stack s= new Lnode;
    BiTree lastVisit = NULL;  //用于标记是否已经访问完左右子树 
    while(T!=NULL||s->top!=-1){
        while(T!=NULL){
            if(s->top==MAXSIZE-1){
                cout<<"栈溢出"<<endl;
                exit(0);
            }
            s->data[++s->top]=T;   //遍历左子树直到根为空 
            T=T->lchild;
        }
        T = s->data[s->top];
        if(T->rchild == NULL || T->rchild == lastVisit){  //如果右字树为空或者访问了右子树，则输出序号 
            cout<<T->data<<" ";
            s->top--;
            lastVisit = T;  //记录已经访问了 
            T = NULL;
        } 
		else {         //否则就访问右子树 
            T=T->rchild;
        }
    }
}
//层序遍历
void LeverOrder(BiTree &T){
	Queue q=new Qnode;  //建立队列并初始化 
	q->front=0;
	q->rear=0;
	if(T==NULL){
		cout<<"错误";
		return; 
	}
	q->data[q->rear] = T;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //队列未满和未空时循环执行 
		cout<<q->data[q->front]->data<<" ";
		T=q->data[q->front];
		if(T->lchild!=NULL){
			q->data[q->rear] = T->lchild;
			q->rear=(q->rear)+1 % MAXSIZE;
		}
		if(T->rchild!=NULL){
			q->data[q->rear] = T->rchild;
			q->rear=(q->rear)+1 % MAXSIZE;
		}
		q->front=(q->front+1) % MAXSIZE;
	}
	
	
}
//判断是否为完全二叉树
void isFull(BiTree &T){
	if(T==NULL){
		cout<<"错误";
		return; 
	}
	Queue q=new Qnode;  //建立队列并初始化 
	int flag=0;
	q->front=0;
	q->rear=0;
	q->data[q->rear] = T;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //队列未满和未空时循环执行 
		T=q->data[q->front];
		q->data[q->rear] = T->lchild;  //将左右字树都存进队列里 
		q->rear=(q->rear)+1 % MAXSIZE;
		q->data[q->rear] = T->rchild;
		q->rear=(q->rear)+1 % MAXSIZE;
		q->front=(q->front+1) % MAXSIZE;
		while(q->data[q->front]==NULL){  //当队列头是空指针的时候，只需判断队列后面有没有元素即可 
			q->front=(q->front+1) % MAXSIZE;
			if(q->front==q->rear)
			{
				cout<<"是完全二叉树";
				flag=1;
				break;
			}
			else if(q->data[q->front]!=NULL){
				cout<<"不是完全二叉树";
				flag=1;
				break;
			}
		}
		if(flag==1){
			break;
		}
	}
		
}
//计算二叉树宽度 
void WidthTree(BiTree &T){
    Queue q=new Qnode;  //建立队列并初始化 
	q->front=0;
	q->rear=0;
	if(T==NULL){
		cout<<"二叉树宽度为0";
		return; 
	}
	q->data[q->rear] = T;
	q->flag[q->rear] = 1;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //遍历标号 
		T=q->data[q->front];
		if(T->lchild!=NULL){
			q->data[q->rear] = T->lchild;
		    q->flag[q->rear] = q->flag[q->front]+1;
			q->rear=(q->rear)+1 % MAXSIZE;
		}
		if(T->rchild!=NULL){
			q->data[q->rear] = T->rchild;
			q->flag[q->rear] = q->flag[q->front]+1;
			q->rear=(q->rear)+1 % MAXSIZE;
		}
		q->front=(q->front+1) % MAXSIZE;
	}
	int n=q->flag[q->rear-1];//n代表层数 
	int count,max;
	count=0;max=0;
	for(int i=1;i<=n;i++){
		count=0;
		for(int j=0;j<q->rear;j++){
			if(q->flag[j]==i){
				count++;
			}
			if(max<count){
				max=count;
			}
		}
	}
	cout<<"二叉树的最大宽度为"<<max<<endl;	
}
int main(){
	BiTree T,root;
	cout<<"请按照先序遍历的方式建立二叉树，#代表没有子树"<<endl;
	CreatBiTree(T);   //建立二叉树 
	root=T;//保存根节点的位置 
	cout<<"递归得到先序表达式为：";
	PreOrder(T);
	cout<<endl;
	T=root; //重置根节点的位置 
	cout<<"递归得到中序表达式为：";
	InOrder(T);
	cout<<endl;
	T=root;
	cout<<"递归得到后续表达式为：";
	PostOrder(T);
	cout<<endl;
	T=root;
	cout<<"非递归得到先序表达式为：";
	PreOrders(T);
	cout<<endl;
	T=root;
	cout<<"非递归得到中序表达式为：";
	InOrders(T);
	cout<<endl;
	T=root;
	cout<<"非递归得到后续表达式为："; 
	PostOrders(T);
	cout<<endl;
	T=root;
	cout<<"层序表达式为：";
	LeverOrder(T);
	cout<<endl;
	T=root;
	isFull(T);
	cout<<endl;
	T=root;
	WidthTree(T);
	delete T;
	return 0;	
}
/*测试数据： 
第一组： 
ABDH##I##E##CF#J##G##
结果： 
先序表达式为：A B D H I E C F J G
中序表达式为：H D I B E A F J C G
后续表达式为：H I D E B J F G C A
层序表达式为：A B C D E F G H I J
不是完全二叉树
二叉树的最大宽度为4
第二组：
ABD#G###CE##F##
结果： 
中序表达式为：D G B A E C F
续表达式为：G D B E F C A
层序表达式为：A B C D E F G
不是完全二叉树
二叉树的最大宽度为3
第三组：
ABCD#####（斜树） 
结果： 
先序表达式为：A B C D
中序表达式为：D C B A
后续表达式为：D C B A
层序表达式为：A B C D
不是完全二叉树
二叉树的最大宽度为1
*/
