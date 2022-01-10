#include<stdio.h>
#define MAXNUM 7500
typedef struct QNode
{
    char data;
    struct QNode *next;
}Qnode,*Queue;
typedef struct
{
    Queue front;
    Queue rear;
}LinkQueue;
void InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;
    Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,char e)
{
    Queue p=new QNode;
    p->data=e;
    Q.rear->next=p;
    p->next=NULL;
    Q.rear=p;
}
void DeQueue(LinkQueue &Q,char &e)
{
    Queue q=Q.front->next;
    e=q->data;
    Q.front->next=q->next;
    if(q==Q.rear) Q.rear=Q.front;
    delete q;
}
int QueueEmpty(LinkQueue Q)
{
    if(Q.front==Q.rear)return 1;
    else return 0;
}
typedef struct
{
    char vexs[30];
    int arcs[30][30];
    int vexnum,arcnum;
}AMGraph;
typedef struct
{
    char adjvex;
    int lowcost;
}closeedge[30];
int Locate(AMGraph G,char v)
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vexs[i])return i;
    }
    return -1;
}
void IniteGraph(AMGraph &G)
{
    char e,v1,v2,f;
    int weight;
    printf("输入点数和边数");
   // scanf("%d,%d%c",&G.vexnum,&G.arcnum,&f);
   G.vexnum=8;G.arcnum=7;
    printf("vexnum=%d,arcnum=%d\n",G.vexnum,G.arcnum);
    if(G.vexnum>30) return;
    else
    {
        for(int j=0;j<G.vexnum;j++)
      {
        for(int k=0;k<G.vexnum;k++)
        {
            G.arcs[j][k]=MAXNUM;
        }
      }
      for(int i=0;i<G.vexnum;i++)
      {
        printf("输入第%d个元素\n",i+1);
        scanf("%c%c",&e,&f);
        G.vexs[i]=e;
        printf("输入的第%d个元素为%c\n",i+1,G.vexs[i]);
      }
       int i,j;
        for(int k=0;k<G.arcnum;k++)
      {
        printf("输入有向边及其权值 v,u,weight\n");
        scanf("%c,%c,%d%c",&v1,&v2,&weight,&f);
        i=Locate(G,v1);
        j=Locate(G,v2);
        G.arcs[i][j]=weight;
       // G.arcs[j][i]=weight;
      }
    }
}
void InsertVex(AMGraph &G,char v)
{
    if(G.vexnum>=30)return;
    else
    {
     G.vexs[G.vexnum]=v;
     G.vexnum++;
     for(int i=0;i<G.vexnum;i++)
     {
        G.arcs[G.vexnum-1][i]=MAXNUM;
     }
     for(int j=0;j<G.vexnum;j++)
     {
        G.arcs[j][G.vexnum-1]=MAXNUM;
     }
    }
}
void InsetArc(AMGraph &G,char v,char w,int weight)
{
    int i,j;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v)break;
    }
    for(j=0;j<G.vexnum;j++)
    {
        if(G.vexs[j]==w)break;
    }
    G.arcs[i][j]=weight;
   // G.arcs[j][i]=weight;
}
void DeleteArc(AMGraph &G,int v,int w)
{
    int i,j;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v)break;
    }
    for(j=0;j<G.vexnum;j++)
    {
        if(G.vexs[j]==w)break;
    }
    G.arcs[i][j]=MAXNUM;
   // G.arcs[j][i]=MAXNUM;
}
void DeleteVex(AMGraph &G,char v)
{
    int i,j,k;
    k=Locate(G,v);
    for(i=k-1;i<G.vexnum-1;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j]=G.arcs[i+1][j];
        }
    }
    for(i=0;i<G.vexnum;i++) G.arcs[G.vexnum-1][i]=MAXNUM;
    for(i=k-1;i<G.vexnum-1;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j]=G.arcs[i][j+1];
        }
    }
    for(i=0;i<G.vexnum;i++) G.arcs[i][G.vexnum-1]=MAXNUM;
    for(int m=k;m<G.vexnum-1;m++)
    {
        G.vexs[m]=G.vexs[m+1];
    }
    G.vexs[G.vexnum-1]='0';
    G.vexnum--;
}
void IniteVisited(AMGraph G,bool visited[])
{
    for(int i=0;i<G.vexnum;i++)
    {
        visited[i]=true;
    }
    for(int i=0;i<G.vexnum;i++)
    {
        printf("%d ",visited[i]);
    }
}
void DFS_AMGraph(AMGraph G,char v,bool visited[])
{
    int j;
    printf("%c ",v);
    j=Locate(G,v);
    visited[j]=true;
//    for(int i=0;i<G.vexnum;i++)
//    {
//        printf("%d",)
//    }
    for(int k=0;k<G.vexnum;k++)
    {
        if((G.arcs[j][k]!=MAXNUM)&&(!visited[k]))
            DFS_AMGraph(G,G.vexs[k],visited);
    }
}
void DFSTraverse(AMGraph G,char v,bool visited[])
{
    DFS_AMGraph(G,v,visited);
    for(int i=0;i<G.vexnum;i++)
    {
        if(visited[i]==false) DFS_AMGraph(G,G.vexs[i],visited);
    }

}
int Firstadjvex(AMGraph G,char u)
{
    int i=Locate(G,u);
    for(int j=0;j<G.vexnum;j++)
    {
        if(G.arcs[i][j]<MAXNUM)return j;
    }
    return -1;
}
int Nextadjvex(AMGraph G,char u,int w)
{
    int i=Locate(G,u);
    for(int j=w+1;j<G.vexnum;j++)
    {
        if(G.arcs[i][j]<MAXNUM)return j;
    }
    return -1;
}
void BFS_AMGraph(AMGraph G,char v,bool visited[])
{
    printf("%c ",v);
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q,v);
    char u;
    while(!QueueEmpty(Q))
    {
        DeQueue(Q,u);
        for(int w=Firstadjvex(G,u);w>=0;w=Nextadjvex(G,u,w))
        {
            if(!visited[w])
            {
                printf("%c ",G.vexs[w]);
                visited[w]=true;
                EnQueue(Q,G.vexs[w]);
            }
        }
    }
}
void BFSTraverse(AMGraph G,char v,bool visited[])
{
    BFS_AMGraph(G,v,visited);
    for(int i=0;i<G.vexnum;i++)
    {
        if(!visited[i])BFS_AMGraph(G,G.vexs[i],visited);
    }
}
void Text(AMGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        printf("%c ",G.vexs[i]);
        for(int j=0;j<G.vexnum;j++)
        {
            if(G.arcs[i][j]==MAXNUM)printf("oo ");
            else printf("%2d ",G.arcs[i][j]);
        }
        printf("\n");
    }
}
int Min(closeedge C,AMGraph G)
{
    int j,k;
    for(j=0;j<G.vexnum;j++)
    {
        if(C[j].lowcost!=0)break;
    }
    for(k=1;k<G.vexnum;k++)
    {
        if(C[k].lowcost<C[j].lowcost&&C[k].lowcost!=0)
            j=k;
    }
    return j;
}
void MIniSpanTree(AMGraph G,char u,closeedge &C)
{
    int k;
    k=Locate(G,u);
    for(int j=0;j<G.vexnum;j++)
        if(j!=k)
        {
            C[j].adjvex=u;
            C[j].lowcost=G.arcs[k][j];
        }
        C[k].lowcost=0;
       // printf("%d\n",k);
//         for(int j=0;j<G.vexnum;j++)
//         {
//             printf("%d ",C[j].lowcost);
//         }
        for(int i=0;i<G.vexnum-1;i++)
        {
            k=Min(C,G);
            //printf("%d",k);
            char u0,v0;
            u0=C[k].adjvex;
            v0=G.vexs[k];
            printf("<%c,%c>",u0,v0);
            C[k].lowcost=0;
            for(int j=0;j<G.vexnum;j++)
            {
                if(G.arcs[k][j]<C[j].lowcost)
                {
                  C[j].adjvex=G.vexs[k];
                  C[j].lowcost=G.arcs[k][j];
                }
            }
//          for(int j=0;j<G.vexnum;j++)
//         {
//             printf("%d ",C[j].lowcost);
//         }

        }
}
int main()
{
    AMGraph G;
    char v,g,a,b;
    int c;
    closeedge C;
     bool visited[MAXNUM];
    for(int i=0;i<MAXNUM;i++)
    {
        visited[i]=false;
    }
    //printf("flag");
    IniteGraph(G);
    Text(G);
//    IniteVisited(G,visited);
//    printf("删除点\n");
//    scanf("%c%c",&v,&g);
//    DeleteVex(G,v);
    //printf("flag2");
//    printf("删除边\n");
//    scanf("%c,%c,%d",&a,&b,&c);
//    DeleteArc(G,a,b);
//    Text(G);
   scanf("%c",&v);
//   DFS_AMGraph(G,v,visited);
   BFS_AMGraph(G,v,visited);
//
//
//       {00,6,1,5,00,00} 1,2,6 1,3,1 1,4,5
//       {6,00,5,00,3,00} 2,3,5 2,5,3
//       {1, 5,00,5,6, 4} 3,4,5 3,5,6 3,6,4
//       {5,00,5,00,00,2} 4,6,2
//       {00,3,6,00,00,6} 5,6,6
//       {00,00,4,2,6,00}
//
//1,2,6 1,3,1 1,4,5 2,3,5 2,5,3 3,4,5 3,5,6 3,6,4 4,6,2 5,6,6
//1 2 3 4 5 6
   // MIniSpanTree(G,v,C);
    return 0;
}
