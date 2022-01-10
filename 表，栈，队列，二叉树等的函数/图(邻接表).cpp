#include<stdio.h>
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;

}arcnode;
typedef struct VexNode
{
    char data;
    arcnode *firstarc;
}VNode[100];
typedef struct
{
    VNode vertices;
    int vexnum,arcnum;
}ALGraph;
int Locate(ALGraph G,char v)
{
    int i=0;
    while(G.vertices[i].data!=v&&i<G.vexnum) i++;
    return i;
}
void CreateGraph(ALGraph &G)
{
    char c,d,f;
    printf("输入顶点数和边数:");
    scanf("%d,%d",&G.vexnum,&G.arcnum);
    scanf("%c",&c);
    printf("vexnum=%d arcnum=%d\n",G.vexnum,G.arcnum);
//    G.arcnum=4;
//    G.vexnum=4;
    printf("输入数据:");
    for(int i=0;i<G.vexnum;i++)
    {
        scanf("%c%c",&G.vertices[i].data,&d);
        G.vertices[i].firstarc=NULL;
        printf("输入的数据为%c ",G.vertices[i].data);
    }
    G.vertices[0].data='a';
    G.vertices[1].data='b';
    G.vertices[2].data='c';
    G.vertices[3].data='d';
    char v1,v2;
    int i,j;
    for(int k=0;k<G.arcnum;k++)
    {
        printf("输入有边的两个顶点\n");
        scanf("%c,%c",&v1,&v2);
        scanf("%c",&f);
        printf("输入的为%c %c\n",v1,v2);
        i=Locate(G,v1);
        j=Locate(G,v2);
       // printf("%d %d",i,j);
        ArcNode* p=new ArcNode;
        p->adjvex=j;
        p->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p;
        ArcNode* p2=new ArcNode;
        p2->adjvex=i;
        p2->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p2;
     //   printf("%d",G.vertices[i].firstarc->adjvex);
    }
}
void text(ALGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        printf("%c ",G.vertices[i].data+1);
        ArcNode* p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
            printf("%d ",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
}
void InsertVex(ALGraph &G,char v)
{
    G.vertices[G.vexnum].data=v;
    G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
}
void DeleteVex(ALGraph &G,char v)
{
   int j;
   j=Locate(G,v);
   void DeleteArc(ALGraph &G,char v,char w);
   for(int i=0;i<j;i++)
   {
       DeleteArc(G,G.vertices[i].data,v);
   }
   for(int i=j+1;i<G.vexnum;i++)
   {
       DeleteArc(G,G.vertices[i].data,v);
   }
   for(int k=j+1;k<G.vexnum;k++)
   {
       ArcNode* p=G.vertices[k].firstarc;
       while(p!=NULL)
       {
           if(p->adjvex>j) p->adjvex--;
           p=p->nextarc;
       }
   }
   for(int k=j;k<G.vexnum-1;k++)
   {
       G.vertices[k].data=G.vertices[k+1].data;
       G.vertices[k].firstarc=G.vertices[k+1].firstarc;
   }
   G.vertices[G.vexnum-1].data=' ';
   G.vertices[G.vexnum-1].firstarc=NULL;
   G.vexnum--;
}
void InsertArc(ALGraph &G,char v,char w)
{
    int i,j;
    i=Locate(G,v);
    j=Locate(G,w);
    ArcNode* p= new ArcNode;
    p->adjvex=j;
    p->nextarc=G.vertices[i].firstarc;
    G.vertices[i].firstarc=p;
    ArcNode* p2=new ArcNode;
    p2->adjvex=i;
    p2->nextarc=G.vertices[j].firstarc;
    G.vertices[j].firstarc=p2;
}
void DeleteArc(ALGraph &G,char v,char w)
{
    int i,j,flag=0;
    i=Locate(G,v);
    j=Locate(G,w);
    ArcNode* r=G.vertices[i].firstarc;
    while(r!=NULL)
     {
        if(r->adjvex==j){flag=1;break;}
        r=r->nextarc;
     }
     if(flag)
     {
    //printf("%d %d",i,j);
    ArcNode* q=G.vertices[i].firstarc;
    if(q->adjvex==j)
    {
        G.vertices[i].firstarc=q->nextarc;
        delete q;
    }
    else
    {
    while(q->nextarc->adjvex!=j)
    {
        q=q->nextarc;
    }
    ArcNode* p=q->nextarc;
    q->nextarc=p->nextarc;
    delete p;
    }
    ArcNode* q2=G.vertices[j].firstarc;
    if(q2->adjvex==i)
    {
        G.vertices[j].firstarc=q2->nextarc;
        delete q2;
    }
    else
    {
    while(q2->nextarc->adjvex!=i)
    {
        q2=q2->nextarc;
    }
    ArcNode* p2=q2->nextarc;
    q2->nextarc=p2->nextarc;
    delete p2;
    }
    G.arcnum--;
    }
}
int main()
{
    ALGraph G;
    char a,b,c;
    CreateGraph(G);
    printf("\n");
    text(G);
//    printf("插入边");
//    scanf("%c,%c",&a,&b);
//    InsertArc(G,a,b);
//    text(G);
//    printf("\n");
//    printf("删除边");
//    scanf("%c,%c",&a,&b);
//    DeleteArc(G,a,b);
//    text(G);
//    printf("\n");
    printf("删除顶点");
    scanf("%c",&c);
//    InsertVex(G,c);
     DeleteVex(G,c);
     text(G);
    return 0;
}
