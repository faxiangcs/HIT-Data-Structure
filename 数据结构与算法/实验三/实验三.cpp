//实验三：最短路径算法
#include<iostream>
#include<fstream>
using namespace std;
#define Max 50   //定义最大顶点数为50 
#define MaxEdge 65535 //定义最大边长为65535
struct mygraph{
	int vertex[Max];
	int edge[Max][Max];
	int n,e;
};
typedef mygraph *Graph;

int P[Max];  //记录每个最短路径的某个节点的前一个节点的编号 
int D[Max];  //记录原点到顶点最短路径的长度 
bool S[Max];  //是否已经选中 
int P1[Max][Max];  // 记录两点间的最短路径编号 
int D1[Max][Max];  // 记录两点间的最短路径长度

//求当前距离最小的下标 
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

//求最短路径和最短长度 
void Dijkstra(Graph &G){
	//初始化,假设原点是0 
	for(int i=0;i<G->n;i++){
		D[i]=G->edge[0][i];
		P[i]=0;
		S[i]=false;
	}
	S[0]=true;
	for(int i=0;i<G->n;i++){
		int w = Minweight(G);  //求原点直接相连的最短路径距离 
		S[w]=true;
		for(int j=0;j<G->n;j++){
			if(S[j]==false&&G->edge[w][j]!=MaxEdge){
				int sum=D[w]+G->edge[w][j];  
				if(D[j]>sum){  //比较原点直接到j和原点到w+w到j的距离大小 
					D[j]=sum;
					P[j]=w;
				}
			}
		}
	}
}
//打印最短长度函数（利用栈来反向输出） 
void PrintPath(int v){
	    if(P[v] != 0){
	        PrintPath(P[v]);
	    }
	    cout << v << " ";
	}

//打印最短路径和最短长度（Dijkstra算法） 
void Print1(Graph &G){
	for(int i=1;i<G->n;i++){
		if(S[i]==true)
	    	cout<<"从源点0到顶点"<<i<<"的最短长度是:"<<D[i]<<endl; 
	}	
	for(int i=1;i<G->n;i++){
		cout << "从源点0到顶点" <<i<< "的最短路径是：";
		PrintPath(i);
		cout << endl;
	}
}

//Folyd算法求最短路径 
void Folyd(Graph &G){
	//初始化
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
					D1[i][j]=D1[i][k]+D1[k][j];  //更新最短距离 
					P1[i][j]=P1[i][k];  //经过的编号 
				}
			}
		}
	}
}
//打印最短路径编号 
void FolydPath(int m,int n){
	int temp;
	temp = m; 
	while(temp!=n){
		if(P1[temp][n]!=-1){
		    cout<<P1[temp][n]<<" ";
		    temp=P1[temp][n];
		}
		else{
			cout<<"不存在路径"<<endl;
			break;
		}
	}
}

//打印最短路径和最短长度（Folyd算法） 
void Print2(Graph &G){ 
	cout<<"每个顶点之间的最短路径长度如下图："<<endl; 
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
	            cout<<"∞"<<"\t";
	        }
	    }
	    cout<<endl;
	}
	cout<<"请输入任意一个目标顶点"<<endl;
	int k;
	cin>>k;
	for(int i=0;i<G->n;i++){
		cout<<"两顶点的最短路径为"<<i<<" ";
		FolydPath(i,k);
		cout<<endl;
	}
	
	cout<<"请输入任意两个顶点"<<endl;
	int m,n;
	cin>>m>>n;
	if(m==n){
		cout<<"两顶点重复，输入错误"<<endl;
	}
	if(D1[m][n]!=MaxEdge){
		cout<<"两顶点的最短距离为"<<D1[m][n]<<endl; 
		cout<<"两顶点的最短路径为"<<m<<" ";
		FolydPath(m,n);
	}	
}
void CreateMGragh(Graph &G){
    int v1, v2, w;
    FILE *fp;
    fp = fopen("test.txt", "r");
    if(fp == NULL){
        printf("文件打开失败\n");
        return;
    }
    fscanf(fp, "%d%d", &(G->n), &(G->e));
    for(int i = 0; i < G->n; i++){
        G->vertex[i] = i;  //输入顶点信息 
    }
    for(int i = 0; i < G->n; i++){
        for(int j = 0; j < G->n; j++){
            G->edge[i][j] = MaxEdge;  //初始化
        }
    }
    for(int i = 0; i < G->e; i++){
        fscanf(fp, "%d%d%d", &v1, &v2, &w);  //输入两顶点(v1,v2)和边的权值 
        G->edge[v1][v2] = w;
        G->edge[v2][v1] = w;
    }
    fclose(fp);
    printf("文件读取完毕\n");
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
