//��ҵ����ͼ�νṹ����Ӧ��
//�������ݼ�word˵�� 
#include<iostream>
using namespace std;
#define MaxVertices 30  //������󶥵���30�� 
struct MGraph{
	char vertex[MaxVertices];  //����� 
	int edge[MaxVertices][MaxVertices];  //�߱� 
	int n,e;  //�������ͱ��� 
};
typedef MGraph *MTGraph;

struct Node{  //�߱��� 
	int adjvex; //�±� 
	int cost;  //Ȩֵ
	struct Node *next; 
};
typedef Node *EdgeNode;

struct Vnode{  //������� 
	char vertex;
	Node *firstedge;
};
typedef Vnode *VertexNode;

struct Adjgraph{  //ͼ���ڽӱ� 
	int n,e;
	Vnode vexlist[MaxVertices];  
};
typedef Adjgraph *AdjGraph;

bool visited[MaxVertices];//���ʱ������
int dfn[MaxVertices]; //����������� 
int count;

struct Qnode{
	int front,rear;
    char data[MaxVertices]; 
};
typedef Qnode *Queue;
//���Ҷ����Ӧ�±� 
int look(MTGraph &G,char v){
	int i;
	for(i=0;i<G->n;i++){
		if(G->vertex[i]==v){
			return i;
		}
	}
	return -1;
}

//����ͼ���ڽӾ���
//ʱ�临�Ӷ�O(n^2),�ռ临�Ӷ�O(n^2) 
void CreateMGragh(MTGraph &G){
	char v1,v2;
	int i,j,w;
	cout<<"������ͼ�Ķ������ͱ���"<<endl;
	cin>>G->n>>G->e;
	cout<<"����������ͼ�Ķ���"<<endl;
	for(int i=0;i<G->n;i++){
		cin>>G->vertex[i];  //���붥����Ϣ 
	}
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			G->edge[i][j]=0;  //��ʼ�� 
		}
	}
	cout<<"������ߵ����������Ȩֵ"<<endl;
	for(int k=0;k<G->e;k++){
		cin>>v1>>v2>>w;  //����������(v1,v2)�ͱߵ�Ȩֵ 
		i= look(G,v1),j=look(G,v2);
		G->edge[i][j]=w;
		G->edge[j][i]=w;
	}
} 
//����ͼ���ڽӱ�洢�ṹ
//ʱ�临�Ӷ�O(n+e),�ռ临�Ӷ�O(n+e) 
void CreatGraph(AdjGraph &G, MTGraph &M){
	char head,tail;
	int w;  //ͷ��β��Ȩ 
	cout<<"������ͼ�Ķ������ͱ���"<<endl;
	cin>>G->n>>G->e;
	M->n = G->n;
	M->e = G->e;
	cout<<"���������붥���ǩ"<<endl;
	for(int i=0;i<G->n;i++){
		cin>>G->vexlist[i].vertex;
		M->vertex[i] = G->vexlist[i].vertex;
		G->vexlist[i].firstedge=NULL; 
	}
	cout<<"����������ߵ����������Ȩֵ"<<endl;
	for(int k=0;k<G->e;k++){
		cin>>head>>tail>>w;
		int i = look(M, head);
		int j = look(M, tail);
		Node *p = new Node;  //�����߽�� 
		p->adjvex = j;
		p->cost = w;    
		p->next = G->vexlist[i].firstedge; //β�巨�������߱� 
		G->vexlist[i].firstedge=p;
		Node *q = new Node;
		q->adjvex = i;
		q->cost = w;    
		q->next = G->vexlist[j].firstedge; //β�巨�������߱� 
		G->vexlist[j].firstedge=q;
	}
}

//��ӡͼ�Ķ���ͱߣ��ڽӾ��󷨣� 
void PrintMGraph(MTGraph &G){
	cout<<"ͼ���ڽӾ���Ϊ��"<<endl;
	for(int i=0;i<G->n;i++){
		for(int j=0;j<G->n;j++){
			cout<<G->edge[i][j]<<"\t";
			if(j==(G->n)-1){
				cout<<endl;
			}
		}
	}
}
//��ӡͼ�Ķ���ıߣ��ڽӱ� 
void PrintGraph(AdjGraph &G){
	for(int i=0;i<G->n;i++){
		cout<<"����"<<G->vexlist[i].vertex<<"�����¼�������������";
		Node *q = new Node; //ָ��
		q=G->vexlist[i].firstedge;
		while(q){
			cout<<G->vexlist[q->adjvex].vertex<<"("<<q->cost<<")"<<" ";
			q=q->next; 
		} 
		cout<<endl;
	}
}

//�ڽӱ��ڽӾ���
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

//�ڽӾ����ڽӱ� 
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

//ͼ��������������㷨���ڽӱ� 
void DFSTraverse1(AdjGraph &G){
	count =1;
	void DFS1(AdjGraph &G,int i);//���� 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //��־�����ʼ�� 
	}
	for(int i=0;i<G->n;i++){  //�۲���û��δ���ʵĶ��㣬���Ƿ���ͨͼ����� 
		if(!visited[i]){  
			DFS1(G,i);  //�Ӷ���i������һ������ 
		}
	}
}
//��һ�����������������ȱ��� ���ڽӱ� 
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
//ͼ����������㷨���ڽӾ���
void DFSTraverse2(MTGraph &G){
	count =1;
	void DFS2(MTGraph &G,int i);//���� 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //��־�����ʼ�� 
	}
	for(int i=0;i<G->n;i++){  //�۲���û��δ���ʵĶ��㣬���Ƿ���ͨͼ����� 
		if(!visited[i]){  
			DFS2(G,i);  //�Ӷ���i������һ������ 
		}
	}
}
//��һ�����������������ȱ������ڽӾ��� 
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
//ͼ�Ĺ�������㷨���ڽӱ� 
void BFSTraverse1(AdjGraph &G){
	count =1;
	void BFS1(AdjGraph &G,int i);//���� 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //��־�����ʼ�� 
	}
	for(int i=0;i<G->n;i++){  //�۲���û��δ���ʵĶ��㣬���Ƿ���ͨͼ����� 
		if(!visited[i]){  
			BFS1(G,i);  //�Ӷ���i������һ������ 
		}
	}
}
//ͼ�Ĺ�������㷨���ڽӾ��� 
void BFSTraverse2(MTGraph &G){
	count = 1;
	void BFS2(MTGraph &G,int i);//���� 
	for(int i=0;i<G->n;i++){
		visited[i]=false;  //��־�����ʼ�� 
	}
	for(int i=0;i<G->n;i++){  //�۲���û��δ���ʵĶ��㣬���Ƿ���ͨͼ����� 
		if(!visited[i]){  
			BFS2(G,i);  //�Ӷ���i������һ������ 
		}
	}
}
//��һ����������Ĺ�����ȱ��� ���ڽӱ�
void BFS1(AdjGraph &G,int k){
	int i;
	Queue Q = new Qnode;
	EdgeNode p;
	Q->rear=0,Q->front=0; //��ʼ������
	cout<<G->vexlist[k].vertex<<" ";  //����ʼ������е�Ԫ�� 
	visited[k]=true;
	Q->data[Q->rear]=G->vexlist[k].vertex;  //��� 
	Q->rear=(Q->rear+1)%MaxVertices;
	while(Q->front!=Q->rear){  //�����鲻Ϊ��ʱ 
		i=Q->front; //����Ԫ�س��� 
		Q->front = (Q->front+1)%MaxVertices;
		p = G->vexlist[i].firstedge; //ȡ�߱��ͷָ��
		while(p){
			if(!visited[p->adjvex]){
				cout<<G->vexlist[p->adjvex].vertex<<" ";
				visited[p->adjvex]=true;
				Q->data[Q->rear] = G->vexlist[p->adjvex].vertex;//��� 
				Q->rear = (Q->rear+1)%MaxVertices;
			}
		    p=p->next;
		} 
		
	}
}
//��һ����������Ĺ�����ȱ��� ���ڽӾ���
void BFS2(MTGraph &G,int k){
	int i,j;
	Queue Q = new Qnode;
	Q->rear=0,Q->front=0; //��ʼ������
	cout<<G->vertex[k]<<" ";  //����ʼ������е�Ԫ�� 
	visited[k]=true;
	Q->data[Q->rear]=G->vertex[k];  //��� 
	Q->rear=(Q->rear+1)%MaxVertices;
	while(Q->front!=Q->rear){  //�����鲻Ϊ��ʱ 
		i=Q->front; //����Ԫ�س��� 
		Q->front = (Q->front+1)%MaxVertices;
		for(j=0;j<G->n;j++){
			if(!visited[j]&&G->edge[i][j]!=0){
				cout<<G->vertex[j]<<" ";
				visited[j]=true;
				Q->data[Q->rear] = G->vertex[j];//��� 
				Q->rear = (Q->rear+1)%MaxVertices;
			}
		} 
	}
}
//����ÿ������Ķ���
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
		cout<<"����"<<G->vexlist[i].vertex<<"�Ķ���Ϊ"<<count<<endl; 
	}
}
int main(){
	MTGraph G=new MGraph;
	AdjGraph AG=new Adjgraph;
	CreateMGragh(G);  //�����ڽӾ��� 
	PrintMGraph(G);
	CreatGraph(AG,G);  //�����ڽӱ� 
    PrintGraph(AG);
//    ListToMat(AG,G);   //�ڽӾ����ڽӱ� 
//    PrintMGraph(G);
//    MatToList(AG,G);  //�ڽӱ��ڽӾ��� 
//    PrintGraph(AG);
//    DFSTraverse1(AG);  //��������ڽӱ� 
//    DFSTraverse2(G);  //��������ڽӾ��� 
//    BFSTraverse1(AG);  //��������ڽӱ� 
//    BFSTraverse2(G);  //��������ڽӾ��� 
//    Calculate(AG);  //�󶥵���� 
    delete G;
    delete AG;
	return 0;
}
