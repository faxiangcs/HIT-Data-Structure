//ʵ���ģ������㷨����Ӧ�� 
#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
//�������� 
void Quicksort(int *arr, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int left = begin;
    int right = end;
    int key = arr[begin]; // ���Ϊkey���ұ�����
    int temp;
    while (begin < end) {
        while (arr[end] >= key && begin < end) {
            end--;
        }
        while (arr[begin] <= key && begin < end) {
            begin++;
        }
        temp = arr[begin];  // ��������Ԫ�� 
        arr[begin] = arr[end];
        arr[end] = temp;
    }
    arr[left] = arr[begin];
    arr[begin] = key;
    Quicksort(arr, left, begin - 1);
    Quicksort(arr, begin + 1, right);
}


int Read(FILE *fp,int a[]){
	//�ļ���ȡ 
	int num=0;
	fp=fopen("sort.txt","r");
	if(fp==NULL){
		cout<<"�ļ��򿪴���";
		return 0;
	}
	fscanf(fp,"%d\n",&num);
	for(int j=1;j<=num;j++){
		fscanf(fp,"%d",&a[j]);
	}
	return num;
}

void Print(int a[], int num){
    //��ӡԪ�� 
    for(int j=1;j<=num;j++){
        cout<<a[j]<<" ";
    }
}

//���ι鲢
void Merge(int a[],int temp[],int first,int mid,int last){
	int i=first;
	int j = mid+1;
	int k=0;
	while(i<=mid&&j<=last){
		if(a[i]<a[j]){
			temp[k++]=a[i++];
		}
		else{
			temp[k++]=a[j++];
		}
	}
	//������źð��û�ź� 
	while(i<=mid){
		temp[k++]=a[i++];
	}
	while(j<=last){
		temp[k++]=a[j++];
	} 
	//�ź�����������뵽a��
	for(i=0;i<k;i++){
		a[first+i]=temp[i];
	} 
} 
//�鲢�����㷨 
void Mergesort(int a[],int first,int last,int temp[]){
	if(first<last){
		int mid = (first+last)/2;		
		Mergesort(a,first,mid,temp);  //�������� 
		Mergesort(a,mid+1,last,temp);  //�Ұ������
		Merge(a,temp,first,mid,last);  //�ϲ������� 
	}
}

//��������
void InsertSort(int arr[],int n){
	for(int i=0;i<n;i++){
		int last = i;
		int temp = arr[i+1];  //��¼���� 
		while(last>=0){
			if(temp<arr[last]){
				arr[last+1]=arr[last];
				last--;
			}
			else{
				break;
			}
		}
		arr[last+1]=temp;
	}
	
}
 
int main(){
	FILE *fp=NULL;
	int a[100000];  //�������ֵ 
	int temp[100000];  //�鲢�������ٵ����� 
	int n=0;//�ļ��е����ָ��� 
	int m=0;//����ʽ 
	 // ����������������ʱ��
	clock_t start_time, end_time;
	double time_spent;
	
	do {
	    cout<<"��ѡ������ʽ��1Ϊ�鲢����2Ϊ��������3Ϊ��������"<<endl; 
	    cin>>m;
	    switch (m) {
	        case 1:
	            n=Read(fp,a);
				start_time = clock();
				Mergesort(a,0,n,temp);
				end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("����������ʱ��: %.6f ����\n", time_spent);
	            break;
	        case 2:
	            n=Read(fp,a);
	            start_time = clock();
	            Quicksort(a,0,n);
	           	end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("����������ʱ��: %.6f ����\n", time_spent);
	            break;
	        case 3:
	            n=Read(fp,a);
	            start_time = clock();
	            InsertSort(a,n);
	            end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("����������ʱ��: %.6f ����\n", time_spent);
	            break;
	        default:
	            cout<<"�������"<<endl;    
	            break;    
	    }
	    cout<<endl; 
	    cout<<"��ѡ�������4�˳���5�ٴ�����"<<endl;
	    cin>>m;
	} while(m==5);
	fclose(fp);
	return 0;
}
