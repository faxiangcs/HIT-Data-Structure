#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define MaxSize 100
//������
struct Lnode {
	int data;
	Lnode* next;
};
typedef Lnode *LinkList;

//��ʼ��
int InitList(LinkList& L) {
	L = new Lnode;
	L->next = NULL;
	return OK;
}

//����������β�巨��
void CreatList(LinkList& L,int n) //n�����½ڵ�ĸ���
{
	LinkList r=L;  //����ָ��rָ��β�ڵ㣬Lһֱָ��ͷ��� 
	cout<<"��������ӦԪ��"<<endl;
	for (int i = 0; i < n; i++) {
		Lnode *p = new Lnode;
		cin >> p->data;
		r->next = p;
		r=p;
		p->next = NULL;
		
	}
}
//��ӡ����Ԫ��
void PrintList(LinkList L) {
	int count = 0;
	LinkList p = L->next; 
	while (p) {
		cout << p->data<<" ";
		p = p->next;
		count++;
	}
	cout << "�����Ԫ�ظ�����:" << count << endl;
}
//ɾ������Ԫ�ص��㷨
int DeleteList(LinkList& L,int i){//ɾ��Ԫ��i 
	LinkList p=L;
	int flag=0;
	if(p->next==NULL){
		cout<<"����Ϊ��"<<endl;
		return ERROR;
	}
	while(p->next!=NULL){
		if(p->next->data==i){
			LinkList q = p->next;
			p->next=p->next->next;
			flag=1;//�����Ѿ�����ɾ����
			delete q; 
		}
		else
		    p=p->next;	
	}
	if(flag==0){
		cout<<"�������"<<endl;
		return ERROR;
	}
	return OK;
} 
//ɾ���ظ�Ԫ�ص��㷨
int DeleteRptNum(LinkList &L){
	LinkList p=L;
	if(p->next==NULL){
		cout<<"����Ϊ��"<<endl;
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
//���Ա������㷨(�Ͽ�ͷ�����ͷ��)
int InversionList(LinkList &L){
	LinkList p=L->next;
	LinkList q=NULL;
	L->next=NULL;//�Ͽ�ͷ��� 
	while(p!=NULL){
		q=p;
		p=p->next;
		q->next=L->next;//ͷ�巨 
		L->next=q;
	}
	return OK;
} 
//ѭ������kλ���㷨
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
//�ϲ������ź��������
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
	CreatList(L, 5);//��������5��Ԫ�ص����� 
	PrintList(L);
	DeleteList(L,3);//ɾ�����е�Ԫ��3 
	PrintList(L); 
	DeleteRptNum(L);//ɾ���ظ���Ԫ�� 
	PrintList(L);
	InversionList(L);//���� 
	PrintList(L);
	MoveList(L,2);//������������2λ 
	PrintList(L);
	CreatList(T, 5);//����һ�����������ںϲ� 
	Integrate(L,T,R);
	PrintList(R);
	return 0;
}
/*
�������ݣ�
���� 1 4 2 2 3
ɾ��Ԫ��3��õ�1 4 2 2
ɾ���ظ���Ԫ��2�õ�1 4 2
�������ú�õ�2 4 1
������������2λ��õ�1 2 4����ʱǡ���ź���
������һ��Ԫ�ع���������3 4 5 6 7
���������Ϊ1 2 3 4 4 5 6 7 
*/ 
