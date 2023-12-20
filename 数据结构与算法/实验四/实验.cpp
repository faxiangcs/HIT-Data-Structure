//实验四：排序算法及其应用 
#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
//快速排序 
void Quicksort(int *arr, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int left = begin;
    int right = end;
    int key = arr[begin]; // 左边为key，右边先走
    int temp;
    while (begin < end) {
        while (arr[end] >= key && begin < end) {
            end--;
        }
        while (arr[begin] <= key && begin < end) {
            begin++;
        }
        temp = arr[begin];  // 交换左右元素 
        arr[begin] = arr[end];
        arr[end] = temp;
    }
    arr[left] = arr[begin];
    arr[begin] = key;
    Quicksort(arr, left, begin - 1);
    Quicksort(arr, begin + 1, right);
}


int Read(FILE *fp,int a[]){
	//文件读取 
	int num=0;
	fp=fopen("sort.txt","r");
	if(fp==NULL){
		cout<<"文件打开错误";
		return 0;
	}
	fscanf(fp,"%d\n",&num);
	for(int j=1;j<=num;j++){
		fscanf(fp,"%d",&a[j]);
	}
	return num;
}

void Print(int a[], int num){
    //打印元素 
    for(int j=1;j<=num;j++){
        cout<<a[j]<<" ";
    }
}

//单次归并
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
	//当半段排好半段没排好 
	while(i<=mid){
		temp[k++]=a[i++];
	}
	while(j<=last){
		temp[k++]=a[j++];
	} 
	//排好序的数组输入到a中
	for(i=0;i<k;i++){
		a[first+i]=temp[i];
	} 
} 
//归并排序算法 
void Mergesort(int a[],int first,int last,int temp[]){
	if(first<last){
		int mid = (first+last)/2;		
		Mergesort(a,first,mid,temp);  //左半边排序 
		Mergesort(a,mid+1,last,temp);  //右半边排序
		Merge(a,temp,first,mid,last);  //合并两数组 
	}
}

//插入排序
void InsertSort(int arr[],int n){
	for(int i=0;i<n;i++){
		int last = i;
		int temp = arr[i+1];  //记录数据 
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
	int a[100000];  //定义最大值 
	int temp[100000];  //归并交换开辟的数组 
	int n=0;//文件中的数字个数 
	int m=0;//排序方式 
	 // 计算排序函数的运行时间
	clock_t start_time, end_time;
	double time_spent;
	
	do {
	    cout<<"请选择排序方式，1为归并排序，2为快速排序，3为插入排序"<<endl; 
	    cin>>m;
	    switch (m) {
	        case 1:
	            n=Read(fp,a);
				start_time = clock();
				Mergesort(a,0,n,temp);
				end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("排序函数运行时间: %.6f 毫秒\n", time_spent);
	            break;
	        case 2:
	            n=Read(fp,a);
	            start_time = clock();
	            Quicksort(a,0,n);
	           	end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("排序函数运行时间: %.6f 毫秒\n", time_spent);
	            break;
	        case 3:
	            n=Read(fp,a);
	            start_time = clock();
	            InsertSort(a,n);
	            end_time = clock();
				time_spent = (double)(end_time - start_time)*1000/ CLOCKS_PER_SEC;
	            Print(a,n);
	            printf("排序函数运行时间: %.6f 毫秒\n", time_spent);
	            break;
	        default:
	            cout<<"输入错误"<<endl;    
	            break;    
	    }
	    cout<<endl; 
	    cout<<"请选择操作，4退出，5再次排序"<<endl;
	    cin>>m;
	} while(m==5);
	fclose(fp);
	return 0;
}
