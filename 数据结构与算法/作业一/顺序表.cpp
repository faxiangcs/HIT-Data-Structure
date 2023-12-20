#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define MaxSize 100

//顺序表定义
struct SeqList
{
	int *elem;//假设线性表最大长度为100
	int length;
};
//初始化
int InitList(SeqList& L)
{
	L.elem = new int[MaxSize]; //开辟内存
	if (!L.elem)
	{
		cerr << "error" << endl;
		return ERROR;
	}
	L.length = 0;//设定线性表长度为0
	return OK;
}
//建立一个顺序表
int CreatList(SeqList &L,int a[],int n)  //n表示元素个数，a[]表示各个元素
{
	if (n > MaxSize){
		cout << "存储空间不足，请改变长度！" << endl;
		return ERROR;
	}
	for (int i = 0; i < n; i++){
		L.elem[i] = a[i];
	}
	L.length = n;
	return OK;
}
//输出顺序表的元素
void PrintList(SeqList &L){
	cout << "线性表的元素个数为" << L.length << endl;
	for (int i = 0; i < L.length; i++)
	{
		cout << L.elem[i] << " ";
	}
	cout<<endl;
}
//删除给定元素的算法
int DeleteElem(SeqList &L, int n)//删除第n个元素
{
	if (n<1 || n>L.length){
		cout << "删除位置错误，请重新输入" << endl;
		return ERROR;
	}
	if (L.length == 0){
		return ERROR;//线性表长度为0
	}
	for (int i = n; i < L.length; i++){
		L.elem[i-1] = L.elem[i];
	}
	L.length--;
	return OK;
}
//删除所有重复元素的算法
int DeleteRptElem(SeqList& L){
	for (int i = 0; i < L.length-1; i++){
		if (L.elem[i] == L.elem[i + 1]) {
			for (int j = i+1; j < L.length; j++) {
				L.elem[j-1] = L.elem[j];
			}
			L.length--;
			i--;//为了处理出现多个元素的重复现象 
		}
	}
	return OK;
}
//线性表“逆置”算法
int InversionList(SeqList &L,SeqList &T)
{
	for (int i = 0; i < L.length; i++) {
		T.elem[i] = L.elem[L.length - 1-i];
	}
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = T.elem[i];
	}
	return OK;
}
//线性表循环左移 k 位的算法，右移同理
int MoveList(SeqList &L,SeqList &T ,int k) {
	for (int i = 0; i < L.length; i++) {
		if (i - k < 0) {
			T.elem[L.length + i - k] = L.elem[i];
		}
		else {
			T.elem[i - k] = L.elem[i];
		}
	}
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = T.elem[i];
	}
	return OK;
}
// 合并两个已排好序的顺序表（降序）
int Integrate(SeqList& L, SeqList &T, SeqList &C) {
	int i = 0, j = 0, k = 0;
	while (i < L.length && j < T.length) {
		if (L.elem[i] > T.elem[j]) {
			C.elem[k] = L.elem[i];
			i++;
			k++;
		}
		else if (T.elem[j] > L.elem[i]) {
			C.elem[k] = T.elem[j];
			j++;
			k++;
		}
		else if (L.elem[i] == T.elem[j]) {
			C.elem[k] = L.elem[i];
			i++;
			k++;
			C.elem[k] = T.elem[j];
			j++;
			k++;
		}
	}
	while (i < L.length && j > T.length-1) {
		C.elem[k] = L.elem[i];
		i++;
		k++;
	}
	while (i > L.length && j < T.length-1) {
		C.elem[k] = T.elem[j];
		j++;
		k++;
	}
	C.length = k;
	return OK;
}
int main()
{
	SeqList L;
	SeqList T;
	InitList(L);
	InitList(T);
	int a[7] = { 1,2,2,3,4,4,5 };
	CreatList(L, a, 7);  //创建一个顺序表，元素为1223445
	PrintList(L);
	DeleteElem(L, 3);//删除第3个元素
	PrintList(L);
	DeleteRptElem(L);//删除重复元素
	PrintList(L);
	InversionList(L, T);//线性表逆置
	PrintList(L);
	MoveList(L, T, 2);//顺序表循环左移2位
	PrintList(L);
	MoveList(L, T, 3);//变回54321继续操作
	int b[3] = { 7,6,5 };
	CreatList(T, b, 3); //创造一个顺序表，元素为765
	SeqList C;//合并后的总表C
	InitList(C);
	C.elem = new int[MaxSize];//开辟更大的空间给C
	Integrate(L, T, C); //合并
	PrintList(C); 
	return 0;
}
/*测试数据
 创建一个顺序表，元素为1223445
 删除第3个元素，变成123445
 删除重复元素，变成12345 
 线性表逆置，变成54321
 顺序表循环左移2位，变成32154
 左移3位变回54321继续操作
 创造一个新的线性表元素为765 
 输出合并后的表76554321
*/
