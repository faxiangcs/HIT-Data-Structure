//ʵ���������·���㷨
#include<iostream>
#include<fstream>
using namespace std;
#define Max 50   //������󶥵���Ϊ50 
#define MaxEdge 65535 //�������߳�Ϊ65535
struct mygraph{
	int vertex[Max];
	int edge[Max][Max];
	int n,e;
};
typedef mygraph *Graph;

int P[Max];  //��¼ÿ�����·����ĳ���ڵ��ǰһ���ڵ�ı�� 
int D[Max];  //��¼ԭ�㵽�������·���ĳ��� 
bool S[Max];  //�Ƿ��Ѿ�ѡ�� 
int P1[Max][Max];  // ��¼���������·����� 
int D1[Max][Max];  // ��¼���������·������

//��ǰ������С���±� 
int Minweight(Graph &G){
	int temp =  MaxEdge;
	int w = 0;
	for(int i=0;i<G->n;i++){
		if(S[i]==false&&D[i]<temp){
			temp = D[i];
			w = i;
		}
	}
	return w;
}

//�����·������̳��� 
void Dijkstra(Graph &G){
	//��ʼ��,����ԭ����0 
	for(int i=0;i<G->n;i++){
		D[i]=G->edge[0][i];
		P[i]=0;
		S[i]=false;
	}
	S[0]=true;
	for(int i=0;i<G->n;i++){
		int w = Minweight(G);  //��ԭ��ֱ�����������·������ 
		S[w]=true;
		for(int j=0;j<G->n;j++){
			if(S[j]==false&&G->edge[w][j]!=MaxEdge){
				int sum=D[w]+G->edge[w][j];  
				if(D[j]>sum){  //�Ƚ�ԭ��ֱ�ӵ�j��ԭ�㵽w+w��j�ľ����С 
					D[j]=sum;
					P[j]=w;
				}
			}
		}
	}
}
//��ӡ��̳��Ⱥ���������ջ����������� 
void PrintPath(int v){
	    if(P[v] != 0){
	        PrintPath(P[v]);
	    }
	    cout << v << " ";
	}

//��ӡ���·������̳��ȣ�Dijkstra�㷨�� 
void Print1(Graph &G){
	for(int i=1;i<G->n;i++){
		if(S[i]==true)
	    	cout<<"��Դ��0������"<<i<<"����̳�����:"<<D[i]<<endl; 
	}	
	for(int i=1;i<G->n;i++){
		cout << "��Դ��0������" <<i<< "�����·���ǣ�";
		PrintPath(i);
		cout << endl;
	}
}

//Folyd�㷨�����·�� 
void Folyd(Graph &G){
	//��ʼ��
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			D1[i][j]=G->edge[i][j];
			P1[i][j]=j;
		}
	}
	for(int k=0;k<G->n;k++){
		for(int i=0;i<G->n;i++){
			for(int j=0;j<G->n;j++){
				if(D1[i][j]>D1[i][k]+D1[k][j]){
					D1[i][j]=D1[i][k]+D1[k][j];  //������̾��� 
					P1[i][j]=P1[i][k];  //�����ı�� 
				}
			}
		}
	}
}
//��ӡ���·����� 
void FolydPath(int m,int n){
	int temp;
	temp = m; 
	while(temp!=n){
		if(P1[temp][n]!=-1){
		    cout<<P1[temp][n]<<" ";
		    temp=P1[temp][n];
		}
		else{
			cout<<"������·��"<<endl;
			break;
		}
	}
}

//��ӡ���·������̳��ȣ�Folyd�㷨�� 
void Print2(Graph &G){ 
	cout<<"ÿ������֮������·����������ͼ��"<<endl; 
	for(int i=0;i<G->n;i++){
	    cout<<"\t"<<i;
	}
	cout<<endl;
	for(int i=0;i<G->n;i++){
	    cout<<i<<"\t";
	    for(int j=0;j<G->n ;j++){
	        if(i == j){
	            cout<<"0\t";
	        }
	        else if(D1[i][j]!=MaxEdge)
	            cout<<D1[i][j]<<"\t";
	        else {
	            cout<<"��"<<"\t";
	        }
	    }
	    cout<<endl;
	}
	cout<<"����������һ��Ŀ�궥��"<<endl;
	int k;
	cin>>k;
	for(int i=0;i<G->n;i++){
		cout<<"����������·��Ϊ"<<i<<" ";
		FolydPath(i,k);
		cout<<endl;
	}
	
	cout<<"������������������"<<endl;
	int m,n;
	cin>>m>>n;
	if(m==n){
		cout<<"�������ظ����������"<<endl;
	}
	if(D1[m][n]!=MaxEdge){
		cout<<"���������̾���Ϊ"<<D1[m][n]<<endl; 
		cout<<"����������·��Ϊ"<<m<<" ";
		FolydPath(m,n);
	}	
}
void CreateMGragh(Graph &G){
    int v1, v2, w;
    FILE *fp;
    fp = fopen("test.txt", "r");
    if(fp == NULL){
        printf("�ļ���ʧ��\n");
        return;
    }
    fscanf(fp, "%d%d", &(G->n), &(G->e));
    for(int i = 0; i < G->n; i++){
        G->vertex[i] = i;  //���붥����Ϣ 
    }
    for(int i = 0; i < G->n; i++){
        for(int j = 0; j < G->n; j++){
            G->edge[i][j] = MaxEdge;  //��ʼ��
        }
    }
    for(int i = 0; i < G->e; i++){
        fscanf(fp, "%d%d%d", &v1, &v2, &w);  //����������(v1,v2)�ͱߵ�Ȩֵ 
        G->edge[v1][v2] = w;
        G->edge[v2][v1] = w;
    }
    fclose(fp);
    printf("�ļ���ȡ���\n");
}
int main()
{
	Graph G = new mygraph;
	CreateMGragh(G);
	Dijkstra(G);
	Print1(G);
	Folyd(G);
	Print2(G);
	return 0;
} 
