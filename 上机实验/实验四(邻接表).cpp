#include<stdio.h>
#define MAXNUM 7500
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    int weight;
}Arcnode;
typedef struct
{
    char data;
    Arcnode *firstarc;
}VexNode,Vexnode[30];
typedef struct
{
    Vexnode vertices;
    int vexnum,arcnum;
}ALGraph;
typedef struct StackNode
{
    int data;
    struct StackNode *next;
}Stacknode,*LinkStack;
void IniteStack(LinkStack &S)
{
    S=NULL;
}
void Push(LinkStack &S,int e)
{
    LinkStack p=new StackNode;
    p->data=e;
    p->next=S;
    S=p;
}
void Pop(LinkStack &S,int &e)
{
    if(S==NULL)return;
    e=S->data;
    LinkStack q=S;
    S=S->next;
    delete q;
}
int Locate(ALGraph G,char v)
{
    int i=0;
    while(G.vertices[i].data!=v&&i<G.vexnum) i++;
    return i;
}
void CreateALGraph(ALGraph &O)
{
    char v1,v2,a,b,c,d;
    printf("输入点数和有向边数(a,b)");
    scanf("%d,%d",&O.vexnum,&O.arcnum);
    scanf("%c",&a);
    printf("vexnum=%d,arcnum=%d\n",O.vexnum,O.arcnum);
//  O.vexnum=6;O.arcnum=8;
//  O.vertices[0].data='0';
//  O.vertices[1].data='1';
//  O.vertices[2].data='2';
//  O.vertices[3].data='3';
    printf("输入顶点数据");
    for(int i=0;i<O.vexnum;i++)
    {
        scanf("%c%c",&O.vertices[i].data,&b);
        O.vertices[i].firstarc=NULL;
    }
    for(int k=0;k<O.arcnum;k++)
    {
        int i,j,w;
        printf("输入有边的两个顶点（前为尾后为头）及其权值(a,b,c)");
        scanf("%c,%c,%d%c",&v1,&v2,&w,&c);
        printf("输入的数据为%c,%c,%d\n",v1,v2,w);
        i=Locate(O,v1);
        j=Locate(O,v2);
        //printf("%d %d\n",i,j);
        ArcNode *p=new ArcNode;
        p->weight=w;
        p->adjvex=j;
        p->nextarc=O.vertices[i].firstarc;
        O.vertices[i].firstarc=p;
    }
   // printf("%d %d\n",O.vertices[2].firstout->tailvex,O.vertices[2].firstout->headvex);
}
void InsertVex(ALGraph &O,char v)
{
    O.vertices[O.vexnum].data=v;
    O.vertices[O.vexnum].firstarc=NULL;
    O.vexnum++;
}
void InsertArc(ALGraph &O,char v,char w,int w1)
{
    int i,j;
    i=Locate(O,v);
    j=Locate(O,w);
    ArcNode *p=new ArcNode;
    p->weight=w1;
    p->adjvex=j;
    p->nextarc=O.vertices[i].firstarc;
    O.vertices[i].firstarc=p;
    O.arcnum++;
}
void DeleteArc(ALGraph &O,char v,char w)
{
    int i,j,flag=0;
    i=Locate(O,v);
    j=Locate(O,w);
   // printf("||%d,%d||",i,j);
    ArcNode* n=O.vertices[i].firstarc;
    while(n!=NULL)
     {
        if(n->adjvex==j){flag=1;break;}
        n=n->nextarc;
     }
     if(flag)
     {
       ArcNode *q=O.vertices[i].firstarc;
       if(q->adjvex==j)
      {
        O.vertices[i].firstarc=q->nextarc;
        delete q;
      }
      else
      {
          //printf("flag2");
       while(q->nextarc->adjvex!=j)
       {
         q=q->nextarc;
       }
       ArcNode *t=q->nextarc;
       q->nextarc=t->nextarc;
       delete t;
      }
       O.arcnum--;
     }
}
void DeleteVex(ALGraph &O,char v)
{
   int j;
   j=Locate(O,v);
   void DeleteArc(ALGraph &O,char v,char w);
   for(int i=0;i<j;i++)
   {
       DeleteArc(O,O.vertices[i].data,v);
   }
   for(int i=j+1;i<O.vexnum;i++)
   {
       DeleteArc(O,O.vertices[i].data,v);
   }
   for(int k=j+1;k<O.vexnum;k++)
   {
       ArcNode* p=O.vertices[k].firstarc;
       while(p!=NULL)
       {
           if(p->adjvex>j) p->adjvex--;
           p=p->nextarc;
       }
   }
   for(int k=j;k<O.vexnum-1;k++)
   {
       O.vertices[k].data=O.vertices[k+1].data;
       O.vertices[k].firstarc=O.vertices[k+1].firstarc;
   }
   O.vertices[O.vexnum-1].data=' ';
   O.vertices[O.vexnum-1].firstarc=NULL;
   O.vexnum--;
}
void IniteVisited(ALGraph O,bool visited[])
{
    for(int i=0;i<O.vexnum;i++)
    {
        visited[i]=true;
    }
}
void DFS_ALGraph(ALGraph O,char v,bool visited[])
{
     int j;
    printf("%c ",v);
    j=Locate(O,v);
    visited[j]=true;
    ArcNode *p=O.vertices[j].firstarc;
    while(p!=NULL)
    {
        int w;
        w=p->adjvex;
        if(!visited[w]) DFS_ALGraph(O,O.vertices[w].data,visited);
        p=p->nextarc;
    }
}
void DFSTraverse(ALGraph G,char v,bool visited[])
{
    DFS_ALGraph(G,v,visited);
    for(int i=0;i<G.vexnum;i++)
    {
        if(!visited[i]) DFS_ALGraph(G,G.vertices[i].data,visited);
    }
}
void shortestpath(ALGraph G,char v1,LinkStack &T)
{
    int n=G.vexnum,i,v,w;
    bool S[n];
    int Path[n],D[n];
    i=Locate(G,v1);
    ArcNode *p=G.vertices[i].firstarc;
    for(v=0;v<n;v++)
    {
        S[v]=false;
        D[v]=MAXNUM;
        Path[v]=-1;
    }
    while(p!=NULL)
    {
        D[p->adjvex]=p->weight;
        Path[p->adjvex]=i;
        p=p->nextarc;
//        printf("||%d||",Path[p->adjvex]);
    }
    S[i]=true;
    D[i]=0;
    v=i;
//    for(int i=0;i<G.vexnum;i++)
//    {
//        printf("||%d||",D[i]);
//    }
     for(int j=1;j<n;j++)
    {
         int min=MAXNUM;
        for(w=0;w<n;w++)
        {
            if(!S[w]&&D[w]<min)
            {
                v=w;
                min=D[w];
            }
        }
            S[v]=true;
            ArcNode *q;
            q=G.vertices[v].firstarc;
            while(q!=NULL)
            {
               if(D[v]+q->weight<D[q->adjvex]&&!S[q->adjvex])
               {
                   D[q->adjvex]=D[v]+q->weight;
                   Path[q->adjvex]=v;
               }
               q=q->nextarc;
            }
        }
//       for(int i=0;i<G.vexnum;i++)
//    {
//        printf("||%d||",Path[i]);
//    }
    for(int k=1;k<n;k++)
   {
       int i,j=0,e=-1,m;
       i=k;
       printf("%c到%c的最短路径为",v1,G.vertices[k].data);
       if(Path[k]==-1) printf("无法到达\n");
       else
       {

           Push(T,k);
          while(Path[i]>=0)
         {
            Push(T,Path[i]);
             i=Path[i];
            j++;
         }
         while(j>=0)
        {
            Pop(T,e);
            printf("%c ",G.vertices[e].data);
            j--;
        }
         printf("\n");
     }
   }
}
void text(ALGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        printf("%c ",G.vertices[i].data);
        ArcNode* p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
            printf("%d(%d) ",p->adjvex,p->weight);
            p=p->nextarc;
        }
        printf("\n");
    }
}
int main()
{
    ALGraph G;
    char v,e,g,a,b;//g用来吃输入时的回车
    int c;
    LinkStack T;
    bool visited[30];
    for(int i=0;i<30;i++)
    {
        visited[i]=false;
    }
    printf("初始化\n");
    IniteStack(T);
    CreateALGraph(G);
    text(G);
    printf("输入起始地");
    scanf("%c%c",&v,&g);
    printf("深度遍历后地点有");
    DFSTraverse(G,v,visited);
    printf("\n");
    printf("添加地点\n");
    scanf("%c%c",&v,&g);
    InsertVex(G,v);
    text(G);
    printf("删除地点\n");
    scanf("%c%c",&v,&g);
    DeleteVex(G,v);
    text(G);
    printf("添加道路及其权值(a,b,c)\n");
    scanf("%c,%c,%d%c",&a,&b,&c,&g);
    InsertArc(G,a,b,c);
    text(G);
    printf("删除道路(a,b)\n");
    scanf("%c,%c%c",&a,&b,&g);
    DeleteArc(G,a,b);
    text(G);
    printf("输入起始点，我们将为您规划从此点到各地点的最短路径");
    scanf("%c",&e);
    shortestpath(G,e,T);
    //1 2 3 4 5 6
    //1,3,10 1,5,30,1,6,100 2,3,5 3,4,50 4,6,10 5,4,20 5,6,60
    return 0;
}

