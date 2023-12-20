#include<iostream>
#include<string.h>
#include<cctype>
using namespace std;

#define ERROR 0
#define OK 1
#define MAXSIZE 50
//��������� 
struct Node
{
	char data;
	struct Node *lchild;
	struct Node *rchild;
};
typedef Node *BiTree;
//����˳��ջ�����ڷǵݹ�洢
struct Lnode
{
    struct Node *data[MAXSIZE];//�������ֵ��50��������ڵ�ĵ�ַ 
	int top=-1;
};
typedef Lnode *Stack; 
//������У����ڲ������ 
struct Qnode
{
	struct Node *data[MAXSIZE];
	int front,rear;
	int flag[MAXSIZE]={0};//���ڼ���������Ŀ�� 
};
typedef Qnode *Queue;
//����������(�ݹ�ʵ��) 
void CreatBiTree(BiTree &T){
	char ch;
	cin>>ch;
	//#�����ǿ��� 
	if(ch=='#'){
		T=NULL;
	}
	else{
		T=new Node;
		T->data=ch;  //���ɸ��ڵ�
		CreatBiTree(T->lchild);  //���������� 
	    CreatBiTree(T->rchild);  //���������� 
	}
}
//����������������ݹ飩
void PreOrder(BiTree &T){
	if(T!=NULL){
		cout<<T->data<<" ";
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}	
}
//����������������ݹ飩
void InOrder(BiTree &T){
	if(T!=NULL){
		InOrder(T->lchild);
		cout<<T->data<<" ";
		InOrder(T->rchild);
	}
} 
//�����������������ݹ飩
void PostOrder(BiTree &T){
	if(T!=NULL){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout<<T->data<<" ";
	}	
}
//����������������ǵݹ飩
void PreOrders(BiTree &T){
	if(T==NULL){
		cout<<"����";
		return; 
	}
	Stack s=new Lnode;
	while(T!=NULL||s->top!=-1){
		while(T!=NULL){
			cout<<T->data<<" ";  //�������ֵ 
			if(s->top==MAXSIZE-1){
				cout<<"ջ���"<<endl;
				exit(0);
			}
			s->data[++s->top]=T;  //Ȼ����������� 
			T=T->lchild;
		}
		if(s->top!=-1){
			T=s->data[s->top--];  
			T=T->rchild;  //���������� 
		}
	} 
} 
//����������������ǵݹ飩
void InOrders(BiTree &T){
	if(T==NULL){
		cout<<"����";
		return; 
	}
	Stack s=new Lnode;
	while(T!=NULL||s->top!=-1){
		while(T!=NULL){
			if(s->top==MAXSIZE-1){
				cout<<"ջ���"<<endl;
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
//�����������������ǵݹ飩
void PostOrders(BiTree &T){
    if(T==NULL){
		cout<<"����";
		return; 
	}
	Stack s= new Lnode;
    BiTree lastVisit = NULL;  //���ڱ���Ƿ��Ѿ��������������� 
    while(T!=NULL||s->top!=-1){
        while(T!=NULL){
            if(s->top==MAXSIZE-1){
                cout<<"ջ���"<<endl;
                exit(0);
            }
            s->data[++s->top]=T;   //����������ֱ����Ϊ�� 
            T=T->lchild;
        }
        T = s->data[s->top];
        if(T->rchild == NULL || T->rchild == lastVisit){  //���������Ϊ�ջ��߷��������������������� 
            cout<<T->data<<" ";
            s->top--;
            lastVisit = T;  //��¼�Ѿ������� 
            T = NULL;
        } 
		else {         //����ͷ��������� 
            T=T->rchild;
        }
    }
}
//�������
void LeverOrder(BiTree &T){
	Queue q=new Qnode;  //�������в���ʼ�� 
	q->front=0;
	q->rear=0;
	if(T==NULL){
		cout<<"����";
		return; 
	}
	q->data[q->rear] = T;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //����δ����δ��ʱѭ��ִ�� 
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
//�ж��Ƿ�Ϊ��ȫ������
void isFull(BiTree &T){
	if(T==NULL){
		cout<<"����";
		return; 
	}
	Queue q=new Qnode;  //�������в���ʼ�� 
	int flag=0;
	q->front=0;
	q->rear=0;
	q->data[q->rear] = T;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //����δ����δ��ʱѭ��ִ�� 
		T=q->data[q->front];
		q->data[q->rear] = T->lchild;  //��������������������� 
		q->rear=(q->rear)+1 % MAXSIZE;
		q->data[q->rear] = T->rchild;
		q->rear=(q->rear)+1 % MAXSIZE;
		q->front=(q->front+1) % MAXSIZE;
		while(q->data[q->front]==NULL){  //������ͷ�ǿ�ָ���ʱ��ֻ���ж϶��к�����û��Ԫ�ؼ��� 
			q->front=(q->front+1) % MAXSIZE;
			if(q->front==q->rear)
			{
				cout<<"����ȫ������";
				flag=1;
				break;
			}
			else if(q->data[q->front]!=NULL){
				cout<<"������ȫ������";
				flag=1;
				break;
			}
		}
		if(flag==1){
			break;
		}
	}
		
}
//������������ 
void WidthTree(BiTree &T){
    Queue q=new Qnode;  //�������в���ʼ�� 
	q->front=0;
	q->rear=0;
	if(T==NULL){
		cout<<"���������Ϊ0";
		return; 
	}
	q->data[q->rear] = T;
	q->flag[q->rear] = 1;
	q->rear=(q->rear)+1 % MAXSIZE;
	while(q->front!=q->rear){  //������� 
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
	int n=q->flag[q->rear-1];//n������� 
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
	cout<<"�������������Ϊ"<<max<<endl;	
}
int main(){
	BiTree T,root;
	cout<<"�밴����������ķ�ʽ������������#����û������"<<endl;
	CreatBiTree(T);   //���������� 
	root=T;//������ڵ��λ�� 
	cout<<"�ݹ�õ�������ʽΪ��";
	PreOrder(T);
	cout<<endl;
	T=root; //���ø��ڵ��λ�� 
	cout<<"�ݹ�õ�������ʽΪ��";
	InOrder(T);
	cout<<endl;
	T=root;
	cout<<"�ݹ�õ��������ʽΪ��";
	PostOrder(T);
	cout<<endl;
	T=root;
	cout<<"�ǵݹ�õ�������ʽΪ��";
	PreOrders(T);
	cout<<endl;
	T=root;
	cout<<"�ǵݹ�õ�������ʽΪ��";
	InOrders(T);
	cout<<endl;
	T=root;
	cout<<"�ǵݹ�õ��������ʽΪ��"; 
	PostOrders(T);
	cout<<endl;
	T=root;
	cout<<"������ʽΪ��";
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
/*�������ݣ� 
��һ�飺 
ABDH##I##E##CF#J##G##
����� 
������ʽΪ��A B D H I E C F J G
������ʽΪ��H D I B E A F J C G
�������ʽΪ��H I D E B J F G C A
������ʽΪ��A B C D E F G H I J
������ȫ������
�������������Ϊ4
�ڶ��飺
ABD#G###CE##F##
����� 
������ʽΪ��D G B A E C F
�����ʽΪ��G D B E F C A
������ʽΪ��A B C D E F G
������ȫ������
�������������Ϊ3
�����飺
ABCD#####��б���� 
����� 
������ʽΪ��A B C D
������ʽΪ��D C B A
�������ʽΪ��D C B A
������ʽΪ��A B C D
������ȫ������
�������������Ϊ1
*/
