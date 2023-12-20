#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define MaxSize 100

//˳�����
struct SeqList
{
	int *elem;//�������Ա���󳤶�Ϊ100
	int length;
};
//��ʼ��
int InitList(SeqList& L)
{
	L.elem = new int[MaxSize]; //�����ڴ�
	if (!L.elem)
	{
		cerr << "error" << endl;
		return ERROR;
	}
	L.length = 0;//�趨���Ա���Ϊ0
	return OK;
}
//����һ��˳���
int CreatList(SeqList &L,int a[],int n)  //n��ʾԪ�ظ�����a[]��ʾ����Ԫ��
{
	if (n > MaxSize){
		cout << "�洢�ռ䲻�㣬��ı䳤�ȣ�" << endl;
		return ERROR;
	}
	for (int i = 0; i < n; i++){
		L.elem[i] = a[i];
	}
	L.length = n;
	return OK;
}
//���˳����Ԫ��
void PrintList(SeqList &L){
	cout << "���Ա��Ԫ�ظ���Ϊ" << L.length << endl;
	for (int i = 0; i < L.length; i++)
	{
		cout << L.elem[i] << " ";
	}
	cout<<endl;
}
//ɾ������Ԫ�ص��㷨
int DeleteElem(SeqList &L, int n)//ɾ����n��Ԫ��
{
	if (n<1 || n>L.length){
		cout << "ɾ��λ�ô�������������" << endl;
		return ERROR;
	}
	if (L.length == 0){
		return ERROR;//���Ա���Ϊ0
	}
	for (int i = n; i < L.length; i++){
		L.elem[i-1] = L.elem[i];
	}
	L.length--;
	return OK;
}
//ɾ�������ظ�Ԫ�ص��㷨
int DeleteRptElem(SeqList& L){
	for (int i = 0; i < L.length-1; i++){
		if (L.elem[i] == L.elem[i + 1]) {
			for (int j = i+1; j < L.length; j++) {
				L.elem[j-1] = L.elem[j];
			}
			L.length--;
			i--;//Ϊ�˴�����ֶ��Ԫ�ص��ظ����� 
		}
	}
	return OK;
}
//���Ա����á��㷨
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
//���Ա�ѭ������ k λ���㷨������ͬ��
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
// �ϲ��������ź����˳�������
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
	CreatList(L, a, 7);  //����һ��˳���Ԫ��Ϊ1223445
	PrintList(L);
	DeleteElem(L, 3);//ɾ����3��Ԫ��
	PrintList(L);
	DeleteRptElem(L);//ɾ���ظ�Ԫ��
	PrintList(L);
	InversionList(L, T);//���Ա�����
	PrintList(L);
	MoveList(L, T, 2);//˳���ѭ������2λ
	PrintList(L);
	MoveList(L, T, 3);//���54321��������
	int b[3] = { 7,6,5 };
	CreatList(T, b, 3); //����һ��˳���Ԫ��Ϊ765
	SeqList C;//�ϲ�����ܱ�C
	InitList(C);
	C.elem = new int[MaxSize];//���ٸ���Ŀռ��C
	Integrate(L, T, C); //�ϲ�
	PrintList(C); 
	return 0;
}
/*��������
 ����һ��˳���Ԫ��Ϊ1223445
 ɾ����3��Ԫ�أ����123445
 ɾ���ظ�Ԫ�أ����12345 
 ���Ա����ã����54321
 ˳���ѭ������2λ�����32154
 ����3λ���54321��������
 ����һ���µ����Ա�Ԫ��Ϊ765 
 ����ϲ���ı�76554321
*/
