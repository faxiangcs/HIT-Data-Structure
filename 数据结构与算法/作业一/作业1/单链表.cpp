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
typedef Lnode* LinkList;

//��ʼ��
int InitList(LinkList& L) {
	L = new Lnode;
	L->next = NULL;
	return OK;
}

//����������β�巨��
void CreatList(LinkList& L,int n) //n�����½ڵ�ĸ���
{
	for (int i = 0; i < n; i++) {
		Lnode *p = new Lnode;
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}
//��ӡ����Ԫ��
void PrintList(LinkList& L) {
	int count = 0;
	while (L->next != NULL) {
		cout << L->data<<" ";
		count++;
	}
	cout << "�����Ԫ�ظ�����:" << count << endl;
}
int main()
{
	LinkList L;
	InitList(L);
	CreatList(L, 3);
	PrintList(L);
	return 0;
}

