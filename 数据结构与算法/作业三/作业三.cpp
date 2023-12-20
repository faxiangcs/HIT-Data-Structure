//作业三：图形结构及其应用
//测试数据见word说明 
#include<iostream>
using namespace std;
#define MaxVertices 30  //假设最大顶点有30个 
struct MGraph{
	char vertex[MaxVertices];  //顶点表 
	int edge[MaxVertices][MaxVertices];  //边表 
	int n,e;  //顶点数和边数 
};
typedef MGraph *MTGraph;

struct Node{  //边表结点 
	int adjvex; //下标 
	int cost;  //权值
	struct Node *next; 
};
typedef Node *EdgeNode;

struct Vnode{  //顶点表结点 
	char vertex;
	Node *firstedge;
};
typedef Vnode *VertexNode;

struct Adjgraph{  //图的邻接表 
	int n,e;
	Vnode vexlist[MaxVertices];  
};
typedef Adjgraph *AdjGraph;

bool visited[MaxVertices];//访问标记数组
int dfn[MaxVertices]; //顶点的先身编号 
int count;

struct Qnode{
	int front,rear;
    char data[MaxVertices]; 
};
typedef Qnode *Queue;
//查找顶点对应下标 
int look(MTGraph &G,char v){
	int i;
	for(i=0;i<G->n;i++){
		if(G->vertex[i]==v){
			return i;
		}
	}
	return -1;
}

//创建图的邻接矩阵
//时间复杂度O(n^2),空间复杂度O(n^2) 
void CreateMGragh(MTGraph &G){
	char v1,v2;
	int i,j,w;
	cout<<"请输入图的顶点数和边数"<<endl;
	cin>>G->n>>G->e;
	cout<<"请依次输入图的顶点"<<endl;
	for(int i=0;i<G->n;i++){
		cin>>G->vertex[i];  //输入顶点信息 
	}
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			G->edge[i][j]=0;  //初始化 
		}
	}
	cout<<"请输入边的两个顶点和权值"<<endl;
	for(int k=0;k<G->e;k++){
		cin>>v1>>v2>>w;  //输入两顶点(v1,v2)和边的权值 
		i= look(G,v1),j=look(G,v2);
		G->edge[i][j]=w;
		G->edge[j][i]=w;
	}
} 
//创建图的邻接表存储结构
//时间复杂度O(n+e),空间复杂度O(n+e) 
void CreatGraph(AdjGraph &G, MTGraph &M){
	char head,tail;
	int w;  //头、尾、权 
	cout<<"请输入图的顶点数和边数"<<endl;
	cin>>G->n>>G->e;
	M->n = G->n;
	M->e = G->e;
	cout<<"请依次输入顶点标签"<<endl;
	for(int i=0;i<G->n;i++){
		cin>>G->vexlist[i].vertex;
		M->vertex[i] = G->vexlist[i].vertex;
		G->vexlist[i].firstedge=NULL; 
	}
	cout<<"请依次输入边的两个顶点和权值"<<endl;
	for(int k=0;k<G->e;k++){
		cin>>head>>tail>>w;
		int i = look(M, head);
		int j = look(M, tail);
		Node *p = new Node;  //建立边结点 
		p->adjvex = j;
		p->cost = w;    
		p->next = G->vexlist[i].firstedge; //尾插法建立出边表 
		G->vexlist[i].firstedge=p;
		Node *q = new Node;
		q->adjvex = i;
		q->cost = w;    
		q->next = G->vexlist[j].firstedge; //尾插法建立出边表 
		G->vexlist[j].firstedge=q;
	}
}

//打印图的顶点和边（邻接矩阵法） 
void PrintMGraph(MTGraph &G){
	cout<<"图的邻接矩阵为："<<endl;
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			cout<<G->edge[i][j]<<"\t";
			if(j==(G->n)-1){
				cout<<endl;
			}
		}
	}
}
//打印图的顶点的边（邻接表） 
void PrintGraph(AdjGraph &G){
	for(int i=0;i<G->n;i++){
		cout<<"顶点"<<G->vexlist[i].vertex<<"与以下几个顶点相连：";
		Node *q = new Node; //指针
		q=G->vexlist[i].firstedge;
		while(q){
			cout<<G->vexlist[q->adjvex].vertex<<"("<<q->cost<<")"<<" ";
			q=q->next; 
		} 
		cout<<endl;
	}
}

//邻接表到邻接矩阵
void ListToMat(AdjGraph &AG,MTGraph &G) {
	for(int i=0;i<AG->n;i++){
		Node *p = AG->vexlist[i].firstedge;
		while(p){
			G->edge[i][p->adjvex]=p->cost;
			p=p->next;
		}
	}
	G->n=AG->n;
	G->e=AG->e;
}

//邻接矩阵到邻接表 
void MatToList(AdjGraph &AG,MTGraph &G){
	for(int i=0;i<G->n;i++){
		AG->vexlist[i].vertex=G->vertex[i];
		AG->vexlist[i].firstedge=NULL;
	}
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			if(G->edge[i][j]!=0){
				Node *p = new Node;
				p->adjvex = j;
				p->cost = G->edge[i][j];
				p->next = AG->vexlist[i].firstedge;
				AG->vexlist[i].firstedge=p;
			}
		}
	}
	AG->n=G->n;
	AG->e=G->e;
}

//图的深度优先搜索算法（邻接表） 
void DFSTraverse1(AdjGraph &G){
	count =1;
	void DFS1(AdjGraph &G,int i);//定义 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //标志数组初始化 
	}
	for(int i=0;i<G->n;i++){  //观察有没有未访问的顶点，考虑非连通图的情况 
		if(!visited[i]){  
			DFS1(G,i);  //从顶点i出发的一次搜索 
		}
	}
}
//从一个顶点出发的深度优先遍历 （邻接表） 
void DFS1(AdjGraph &G,int i){
	EdgeNode p;
	cout<<G->vexlist[i].vertex<<" ";
	visited[i]=true;
	dfn[i]=count++;
	p=G->vexlist[i].firstedge;
	while(p){
		if(!visited[p->adjvex]){
			DFS1(G,p->adjvex);
		}
		p=p->next;
	}
}
//图的深度优先算法（邻接矩阵）
void DFSTraverse2(MTGraph &G){
	count =1;
	void DFS2(MTGraph &G,int i);//定义 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //标志数组初始化 
	}
	for(int i=0;i<G->n;i++){  //观察有没有未访问的顶点，考虑非连通图的情况 
		if(!visited[i]){  
			DFS2(G,i);  //从顶点i出发的一次搜索 
		}
	}
}
//从一个顶点出发的深度优先遍历（邻接矩阵） 
void DFS2(MTGraph &G,int i){
	int j;
	cout<<G->vertex[i]<<" ";
	visited[i]=true;
	dfn[i]=count++;
	for(j=0;j<G->n;j++){
		if(G->edge[i][j]!=0 && !visited[i]){
			DFS2(G,i);
		}
	}
}
//图的广度优先算法（邻接表） 
void BFSTraverse1(AdjGraph &G){
	count =1;
	void BFS1(AdjGraph &G,int i);//定义 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //标志数组初始化 
	}
	for(int i=0;i<G->n;i++){  //观察有没有未访问的顶点，考虑非连通图的情况 
		if(!visited[i]){  
			BFS1(G,i);  //从顶点i出发的一次搜索 
		}
	}
}
//图的广度优先算法（邻接矩阵） 
void BFSTraverse2(MTGraph &G){
	count = 1;
	void BFS2(MTGraph &G,int i);//定义 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //标志数组初始化 
	}
	for(int i=0;i<G->n;i++){  //观察有没有未访问的顶点，考虑非连通图的情况 
		if(!visited[i]){  
			BFS2(G,i);  //从顶点i出发的一次搜索 
		}
	}
}
//从一个顶点出发的广度优先遍历 （邻接表）
void BFS1(AdjGraph &G,int k){
	int i;
	Queue Q = new Qnode;
	EdgeNode p;
	Q->rear=0,Q->front=0; //初始化队列
	cout<<G->vexlist[k].vertex<<" ";  //输出最开始进入队列的元素 
	visited[k]=true;
	Q->data[Q->rear]=G->vexlist[k].vertex;  //入队 
	Q->rear=(Q->rear+1)%MaxVertices;
	while(Q->front!=Q->rear){  //当队伍不为空时 
		i=Q->front; //队首元素出队 
		Q->front = (Q->front+1)%MaxVertices;
		p = G->vexlist[i].firstedge; //取边表的头指针
		while(p){
			if(!visited[p->adjvex]){
				cout<<G->vexlist[p->adjvex].vertex<<" ";
				visited[p->adjvex]=true;
				Q->data[Q->rear] = G->vexlist[p->adjvex].vertex;//入队 
				Q->rear = (Q->rear+1)%MaxVertices;
			}
		    p=p->next;
		} 
		
	}
}
//从一个顶点出发的广度优先遍历 （邻接矩阵）
void BFS2(MTGraph &G,int k){
	int i,j;
	Queue Q = new Qnode;
	Q->rear=0,Q->front=0; //初始化队列
	cout<<G->vertex[k]<<" ";  //输出最开始进入队列的元素 
	visited[k]=true;
	Q->data[Q->rear]=G->vertex[k];  //入队 
	Q->rear=(Q->rear+1)%MaxVertices;
	while(Q->front!=Q->rear){  //当队伍不为空时 
		i=Q->front; //队首元素出队 
		Q->front = (Q->front+1)%MaxVertices;
		for(j=0;j<G->n;j++){
			if(!visited[j]&&G->edge[i][j]!=0){
				cout<<G->vertex[j]<<" ";
				visited[j]=true;
				Q->data[Q->rear] = G->vertex[j];//入队 
				Q->rear = (Q->rear+1)%MaxVertices;
			}
		} 
	}
}
//计算每个顶点的度数
void Calculate(AdjGraph &G){
	EdgeNode p;
	int count;
	for(int i=0;i<G->n;i++){
		count = 0;
		p=G->vexlist[i].firstedge;
		while(p){
			count++;
			p=p->next;
		}
		cout<<"顶点"<<G->vexlist[i].vertex<<"的度数为"<<count<<endl; 
	}
}
int main(){
	MTGraph G=new MGraph;
	AdjGraph AG=new Adjgraph;
	CreateMGragh(G);  //创建邻接矩阵 
	PrintMGraph(G);
	CreatGraph(AG,G);  //创建邻接表 
    PrintGraph(AG);
//    ListToMat(AG,G);   //邻接矩阵到邻接表 
//    PrintMGraph(G);
//    MatToList(AG,G);  //邻接表到邻接矩阵 
//    PrintGraph(AG);
//    DFSTraverse1(AG);  //深度搜索邻接表 
//    DFSTraverse2(G);  //深度搜索邻接矩阵 
//    BFSTraverse1(AG);  //广度搜索邻接表 
//    BFSTraverse2(G);  //广度搜索邻接矩阵 
//    Calculate(AG);  //求顶点度数 
    delete G;
    delete AG;
	return 0;
}
