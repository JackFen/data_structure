#include<stdio.h>
#define MAXNUM 7500
typedef struct
{
    char vexs[30];
    int arcs[30][30];
    int vexnum,arcnum;
}AMGraph;
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
    printf("输入点数和有向边数");
    scanf("%d,%d%c",&G.vexnum,&G.arcnum,&f);
   // G.vexnum=6;G.arcnum=8;
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
    i=Locate(G,v);
    j=Locate(G,w);
    G.arcs[i][j]=weight;
   // G.arcs[j][i]=weight;
}
void DeleteArc(AMGraph &G,char v,char w)
{
    int i,j;
    i=Locate(G,v);
    j=Locate(G,w);
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
void DFS_AMGraph(AMGraph G,char v,bool visited[])
{
    int j;
    printf("%c ",v);
    j=Locate(G,v);
    visited[j]=true;
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
        if(!visited[i]) DFS_AMGraph(G,G.vexs[i],visited);
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
void shortestpath(AMGraph G,char v1,LinkStack &T)
{
    int n=G.vexnum,i,v,w;
    bool S[n];
    int Path[n],D[n];
    i=Locate(G,v1);
    for(v=0;v<n;v++)
    {
        S[v]=false;
        D[v]=G.arcs[i][v];
        if(D[v]<MAXNUM) Path[v]=i;
        else Path[v]=-1;
    }
    S[i]=true;
    D[i]=0;
    v=i;
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
        for(int k=0;k<n;k++)
        {
            if(!S[k]&&(D[v]+G.arcs[v][k]<D[k]))
            {
                D[k]=D[v]+G.arcs[v][k];
                Path[k]=v;
            }
        }
    }
   for(int k=1;k<n;k++)
   {
       int i,j=0,e=-1,m;
       i=k;
       printf("%c到%c的最短路径为",v1,G.vexs[k]);
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
            printf("%c ",G.vexs[e]);
            j--;
        }
         printf("\n");
     }
   }
}
int main()
{
    AMGraph G;
    char v,e,g,a,b;//g用来吃输入时的回车
    int c;
    LinkStack T;
    bool visited[MAXNUM];
    for(int i=0;i<MAXNUM;i++)
    {
        visited[i]=false;
    }
    printf("初始化\n");
    IniteGraph(G);
    IniteStack(T);
    Text(G);
    printf("输入起始地");
    scanf("%c%c",&v,&g);
    printf("深度遍历后地点有");
    DFSTraverse(G,v,visited);
    printf("\n");
    printf("添加地点\n");
    scanf("%c%c",&v,&g);
    InsertVex(G,v);
    Text(G);
    printf("删除地点\n");
    scanf("%c%c",&v,&g);
    DeleteVex(G,v);
    Text(G);
    printf("添加道路及其权值(a,b,c)\n");
    scanf("%c,%c,%d%c",&a,&b,&c,&g);
    InsetArc(G,a,b,c);
    Text(G);
    printf("删除道路(a,b)\n");
    scanf("%c,%c%c",&a,&b,&g);
    DeleteArc(G,a,b);
    Text(G);
    printf("输入起始点，我们将为您规划从此点到各地点的最短路径");
    scanf("%c",&e);
    shortestpath(G,e,T);
//       {00,6,1,5,00,00} 1,2,6 1,3,1 1,4,5
//       {6,00,5,00,3,00} 2,3,5 2,5,3
//       {1, 5,00,5,6, 4} 3,4,5 3,5,6 3,6,4
//       {5,00,5,00,00,2} 4,6,2
//       {00,3,6,00,00,6} 5,6,6
//       {00,00,4,2,6,00}
//1,2,6 1,3,1 1,4,5 2,3,5 2,5,3 3,4,5 3,5,6 3,6,4 4,6,2 5,6,6
//1 2 3 4 5 6
//1,3,10 1,5,30,1,6,100 2,3,5 3,4,50 4,6,10 5,4,20 5,6,60
//1 6 5 4 3
//1 3 4 6 5
//1 oo oo 10 oo 30 100
//2 oo oo  5 oo oo oo
//3 oo oo oo 50 oo oo
//4 oo oo oo oo oo 10
//5 oo oo oo 20 oo 60
//6 oo oo oo oo oo oo
    return 0;
}
