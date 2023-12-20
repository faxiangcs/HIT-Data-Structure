#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define MaxSize 100
//链表定义
struct Lnode {
	int data;
	Lnode* next;
};
typedef Lnode *LinkList;

//初始化
int InitList(LinkList& L) {
	L = new Lnode;
	L->next = NULL;
	return OK;
}

//创建新链表（尾插法）
void CreatList(LinkList& L,int n) //n代表新节点的个数
{
	LinkList r=L;  //定义指针r指向尾节点，L一直指向头结点 
	cout<<"请输入相应元素"<<endl;
	for (int i = 0; i < n; i++) {
		Lnode *p = new Lnode;
		cin >> p->data;
		r->next = p;
		r=p;
		p->next = NULL;
		
	}
}
//打印链表元素
void PrintList(LinkList L) {
	int count = 0;
	LinkList p = L->next; 
	while (p) {
		cout << p->data<<" ";
		p = p->next;
		count++;
	}
	cout << "链表的元素个数是:" << count << endl;
}
//删除给定元素的算法
int DeleteList(LinkList& L,int i){//删除元素i 
	LinkList p=L;
	int flag=0;
	if(p->next==NULL){
		cout<<"链表为空"<<endl;
		return ERROR;
	}
	while(p->next!=NULL){
		if(p->next->data==i){
			LinkList q = p->next;
			p->next=p->next->next;
			flag=1;//代表已经操作删除了
			delete q; 
		}
		else
		    p=p->next;	
	}
	if(flag==0){
		cout<<"输入错误"<<endl;
		return ERROR;
	}
	return OK;
} 
//删除重复元素的算法
int DeleteRptNum(LinkList &L){
	LinkList p=L;
	if(p->next==NULL){
		cout<<"链表为空"<<endl;
		return ERROR;
	}
	while(p->next!=NULL){
		if(p->next->data==p->data){
			LinkList q=p->next;
			p->next=p->next->next;
			delete q; 
		}
		else
		    p=p->next;
	}
	
	return OK;
} 
//线性表逆置算法(断开头结点再头插)
int InversionList(LinkList &L){
	LinkList p=L->next;
	LinkList q=NULL;
	L->next=NULL;//断开头结点 
	while(p!=NULL){
		q=p;
		p=p->next;
		q->next=L->next;//头插法 
		L->next=q;
	}
	return OK;
} 
//循环左移k位的算法
int MoveList(LinkList &L,int k){
	Lnode *phead = new Lnode;
	LinkList r=phead;
	LinkList p=L->next;
	LinkList end=NULL;
	for(int i=0;i<k;i++){
		p=p->next;
	} 
	end=p;
	while(p->next!=end){
	    if(p->next!=NULL){
	        Lnode *q = new Lnode;
	        q->data=p->data;
	        r->next=q;
	        r=q;
	        q->next=NULL;
	        p=p->next;
	        }
	    else if(p->next==NULL){
		    Lnode *q = new Lnode;
		    q->data=p->data;
		    r->next=q;
		    r=q;
		    q->next=NULL;
		    p=L->next;
	    }
	}
	Lnode *q = new Lnode;
	q->data=p->data;
	r->next=q;
	r=q;
	q->next=NULL;
	p=L->next;
	q=phead->next;
	while(q){
		p->data=q->data;
		r=q;
		q=q->next;
		p=p->next;
		delete r;
	}	
	delete phead;
	return OK;
} 
//合并两个排好序的链表
int Integrate(LinkList &L,LinkList &T,LinkList &R){
	LinkList p=L->next;
	LinkList q=T->next;
	LinkList r=R;
	while(p!=NULL&&q!=NULL){
		if(p->data>q->data){
			Lnode *s=new Lnode;
			s->data=q->data;
			r->next=s;
			r=s;
			s->next=NULL;
			q=q->next;
		}
		else{
		    Lnode *s=new Lnode;
			s->data=p->data;
			r->next=s;
			r=s;
			s->next=NULL;
			p=p->next;	
		}
	}
	while(q){
		Lnode *s=new Lnode;
		s->data=q->data;
		r->next=s;
		r=s;
		s->next=NULL;
		q=q->next;	
	}
	while(p){
        Lnode *s=new Lnode;
		s->data=p->data;
		r->next=s;
		r=s;
		s->next=NULL;
		p=p->next;		
	}
	return OK;
} 
int main()
{
	LinkList L;
	LinkList T;
	LinkList R;
	InitList(L);
	InitList(T);
	InitList(R);
	CreatList(L, 5);//创建含有5个元素的链表 
	PrintList(L);
	DeleteList(L,3);//删除其中的元素3 
	PrintList(L); 
	DeleteRptNum(L);//删除重复的元素 
	PrintList(L);
	InversionList(L);//逆置 
	PrintList(L);
	MoveList(L,2);//链表整体左移2位 
	PrintList(L);
	CreatList(T, 5);//创建一个新链表用于合并 
	Integrate(L,T,R);
	PrintList(R);
	return 0;
}
/*
测试数据：
输入 1 4 2 2 3
删除元素3后得到1 4 2 2
删除重复的元素2得到1 4 2
链表逆置后得到2 4 1
链表整体左移2位后得到1 2 4，此时恰好排好序
再输入一组元素构成新链表3 4 5 6 7
最后输出结果为1 2 3 4 4 5 6 7 
*/ 
