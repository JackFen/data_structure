#include<stdio.h>
#define MAX_NUM 20//临界多重表适用与无向图
typedef enum{unvisited,visited} VisitIf;
typedef struct Ebox
{
    VisitIf mark;
    int ivex,jvex;
    struct Ebox *ilink,*jlink;
    //infotype *info;
}ebox;
typedef struct VexBox
{
    char data;
    Ebox *firstedge;
}Vexbox;
typedef struct
{
    Vexbox adjmulist[MAX_NUM];
    int vexnum,edgenum;
}AMLGraph;
int Locate(AMLGraph G,char v)
{
    int k;
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.adjmulist[i].data==v)
        {
            return i;
        }
    }
    return -1;
}
void CreateAMLGraph(AMLGraph &G)
{
    char g,v,u;
    int i,j;
    printf("输入点数和边数\n");
    scanf("%d,%d%c",&G.vexnum,&G.edgenum,&g);
    printf("vexnum=%d,edgenum=%d\n",G.vexnum,G.edgenum);
    printf("输入数据\n");
    for(int i=0;i<G.vexnum;i++)
    {
        scanf("%c%c",&G.adjmulist[i].data,&g);
        G.adjmulist[i].firstedge=NULL;
        printf("输入数据为%c\n",G.adjmulist[i].data);
    }
    printf("输入边(a,b)\n");
    for(int k=0;k<G.edgenum;k++)
    {
        scanf("%c,%c%c",&v,&u,&g);
        printf("输入的边为%c,%c\n",v,u);
        i=Locate(G,v);
        j=Locate(G,u);
        Ebox *p=new Ebox;
        p->ivex=i;
        p->jvex=j;
        p->ilink=G.adjmulist[i].firstedge;
        G.adjmulist[i].firstedge=p;
        p->jlink=G.adjmulist[j].firstedge;
        G.adjmulist[j].firstedge=p;
    }
}
void text(AMLGraph G)
{
    Ebox *p,*r;
    for(int i=0;i<G.vexnum;i++)
    {
        int j;
        j=Locate(G,G.adjmulist[i].data);
       p=G.adjmulist[i].firstedge;
       printf("%c ",G.adjmulist[i].data);
       while(p!=NULL)
       {
           printf("%d,%d ",p->ivex,p->jvex);
           if(j==p->ivex) p=p->ilink;
           else p=p->jlink;
       }
       printf("\n");
    }
}
int main()
{
    AMLGraph G;
    CreateAMLGraph(G);
    text(G);
    return 0;
}
