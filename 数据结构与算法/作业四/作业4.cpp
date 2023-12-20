//��ҵ�ģ����ҽṹ����Ӧ�� 
#include<iostream>
#include<fstream>
using namespace std;
#define MAX 1024

struct TreeNode{
	int data;
	struct TreeNode *lchild,*rchild;
}; 
typedef TreeNode *BST;
int count=0;//���Ҵ���
int ans = 0;//�����±� 
int count1=0;//��¼�۰���Ҵ��� 

//�����㷨 
void Insert (BST &T,int k){
	if(T==NULL){
		T=new TreeNode;
		T->lchild=NULL;
		T->rchild=NULL;
		T->data = k;
	}
	else if(T->data==k){
		cout<<"�ؼ����Ѿ�����,��������������ؼ���"<<endl;
	}
	else if(T->data<k){
		Insert(T->rchild,k);
	}
	else{
		Insert(T->lchild,k);
	}
}

//�����㷨
TreeNode *Search(BST &T,int k){
	if(T==NULL){
		return T;
	}
	count++; 
	if(T->data==k){
		return T;
	}
	else if(T->data>k){
		return Search(T->lchild,k);
	}
	else {
		return Search(T->rchild,k);
	}	
}	

//ɾ��BST������Сֵ�Ľڵ㲢���ظ���Сֵ 
int DeleteMin(BST &T){
    int tmp;
    BST p;
    if(T->lchild==NULL){
        p=T;
        tmp=T->data ;
        T=T->rchild ;
        delete p;
        return tmp;
}

    else{
        DeleteMin(T->lchild);
    }
}

//ɾ���㷨
void Delete(BST &T,int k){//ɾ��BST���Ĺؼ���Ϊk�Ľڵ� 
    if(T!=NULL){
        if(T->data<k){
            Delete(T->rchild,k);//�ݹ�ĵ�������ȥɾ�� 
        }
        else if(T->data>k){
            Delete(T->lchild,k);//�ݹ�ĵ�������ȥɾ�� 
        }
        else{
            if(T->lchild==NULL){
                T=T->rchild ;//�����̳� 
            }
            else if(T->rchild==NULL){
                T=T->lchild ;//�����̳� 
            }
            else{
                T->data=DeleteMin(T->rchild); //�ݹ�ɾ�� 
            }
        }
    }
    else{
		cout<<"�ڵ㲻����"<<endl;
	}
}

//�����㷨
void Order(BST &T,int list[]){
	if(T==NULL){
		return;
	}
	Order(T->rchild,list);
	list[ans]=T->data;
	ans++;
	Order(T->rchild,list);
} 

//�۰�����㷨
int HalfSearch(int L[],int k,int high){
	int low=0;
	int mid=0;
	
	while(low<high){
		mid=(low+high)/2;
		count1++;
		if(L[mid]==k){
			return count1;
		} 
		else if(L[mid]>k){
			high=mid-1;
		}
		else{
			low = mid+1;
		}
	}
	return 0;
}

//����BST��1
BST Create1(){
	fstream in;
	in.open("shuju1.txt");
	BST p=NULL;
	int k;
	for(int i=0;i<MAX;i++){
		in>>k;
		Insert(p,k);
	}
	in.close();
	return p;
}  
BST Create2(){
    fstream in;
	in.open("shuju2.txt");
	BST p=NULL;
	int k;
	for(int i=0;i<MAX;i++){
		in>>k;
		Insert(p,k);
	}
	in.close();
	return p;	
}
//����ҵĴ��� 
void cishu(BST &T){
	float sum1=0.0,sum2=0.0;//�����ǲ��ҳɹ���ż���ǲ���ʧ�� 
	BST p=NULL;
	for(int i=0;i<MAX;i++){
		count=0;
		p=Search(T,2*i+1);
		sum1=sum1+count;
	}
	cout<<"���ҳɹ���ƽ������Ϊ��"<<float(sum1/MAX)<<endl;
    for(int i=0;i<MAX;i++){
		count=0;
		p=Search(T,2*i);
		sum2=sum2+count;
	}
	cout<<"����ʧ�ܵ�ƽ������Ϊ��"<<float(sum2/MAX)<<endl;
}


void testhalf(){//�����۰����ƽ�����ҳ��� 
    int i,sum=0;
    float aver;
    int a[MAX];
    for(int i=0;i<MAX;i++){
     a[i]=2*i+1;
 }   
    for(i=0;i<MAX;i++){
     count1=0;
        HalfSearch(a,2*i+1,MAX-1);
        sum+=count1;
    }
    aver=(float)sum/MAX;//ƽ�������ܴ��� 
    cout<<"�۰���ҳɹ�ƽ������Ϊ"<<aver<<endl; 
    sum=0;
	ans=0;
    for(i=0;i<MAX;i++){
        count1=0;
        HalfSearch(a,2*i,MAX-1);
        sum+=count1;
    }
    HalfSearch(a,2048,MAX-1);
    sum+=count1;
    aver=(float)sum/(MAX+1);
    cout<<"�۰����ʧ��ƽ������Ϊ"<<aver<<endl;  
}
int main() {
    BST T1 = Create1();
    BST T2 = Create2();

    cout << "���Բ��빦�ܣ�" << endl;
    int insertValue = 6;
    cout << "�����ֵΪ " << insertValue<< endl;
    Insert(T1, insertValue);
    cout << "��ֵ " << insertValue << "�Ѿ��ɹ�����" << endl;

    cout << "\n���Բ��ҹ��ܣ�" << endl;
    int searchValue = 8;
    cout << "���ҵ�ֵΪ " << searchValue<< endl;
    TreeNode* searchResult = Search(T1, searchValue);
    if (searchResult != NULL) {
        cout << "��ֵ " << searchValue << " �Ѿ����ҵ�" << endl;
    } else {
        cout << "��ֵ " << searchValue << " û�б��ҵ�" << endl;
    }

    cout << "\n����ɾ������" << endl;
    int deleteValue = 6;
    cout << "ɾ������ֵΪ " << deleteValue << endl;
    Delete(T1, deleteValue);
    cout << "��ֵ " << deleteValue << " �Ѿ��ɹ�ɾ��" << endl;

    cout << "\n��һ��������ݣ�" << endl;
    cishu(T1);
    testhalf();
    cout << "�ڶ���������ݣ�" << endl;
    cishu(T2);
    testhalf();

    return 0;
}


/*BST���Һ��۰���ҵ�ʱ�临�Ӷȶ���O(logn),������������й��ɵ����ֽ����ͻᵼ��BST���ܹ�
����ƽ������Ȼᡮ����ǳǳ������ʹ���ض������ݽ��в�ѯ��ʱ��ͻ���ܵ��������½������籾��ʵ�飬
��˳�����н�����ʱ�򣬾ͻ��γ�һ������Ҳ������б��������ÿ�β��Һ�������������ر�
��������������в���Ч����Ȼ�ܲ��������������ֲ��ǹ��ɵģ���������ģ�����ڶ���������ݣ�
���Ƿ�������ƽ������ʱ�����ܺ��۰����ʱ����������С��������ǵ����ָ����һ�㣬
��ô������Ϊ�۰���Һ�BST���ҵ�ʱ�����ܲ�ࡣ
*/
