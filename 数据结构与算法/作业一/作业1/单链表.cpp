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
typedef Lnode* LinkList;

//初始化
int InitList(LinkList& L) {
	L = new Lnode;
	L->next = NULL;
	return OK;
}

//创建新链表（尾插法）
void CreatList(LinkList& L,int n) //n代表新节点的个数
{
	for (int i = 0; i < n; i++) {
		Lnode *p = new Lnode;
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}
//打印链表元素
void PrintList(LinkList& L) {
	int count = 0;
	while (L->next != NULL) {
		cout << L->data<<" ";
		count++;
	}
	cout << "链表的元素个数是:" << count << endl;
}
int main()
{
	LinkList L;
	InitList(L);
	CreatList(L, 3);
	PrintList(L);
	return 0;
}

