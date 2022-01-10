#include<stdio.h>
typedef struct ArcNode
{
    int tailvex;
    int headvex;
    struct ArcNode *hlink;
    struct ArcNode *tlink;
    //othertype  *info;
}Arcnode;
typedef struct
{
    char data;
    Arcnode *firstin;
    Arcnode *firstout;
}VexNode,Vexnode[100];
typedef struct
{
    Vexnode vertices;
    int vexnum,arcnum;
}OList;
int Locate(OList G,char v)
{
    int i=0;
    while(G.vertices[i].data!=v&&i<G.vexnum) i++;
    return i;
}
void CreateOList(OList &O)
{
    char v1,v2,a,b,c,d;
    scanf("%d,%d",&O.vexnum,&O.arcnum);
    scanf("%c",&a);
    printf("输入的数据为%d %d\n",O.vexnum,O.arcnum);
//  O.vexnum=4;O.arcnum=7;
//  O.vertices[0].data='a';
//  O.vertices[1].data='b';
//  O.vertices[2].data='c';
//  O.vertices[3].data='d';
    for(int i=0;i<O.vexnum;i++)
    {
        scanf("%c%c",&O.vertices[i].data,&b);
        O.vertices[i].firstin=NULL;
        O.vertices[i].firstout=NULL;
    }
    for(int k=0;k<O.arcnum;k++)
    {
        int i,j;
        printf("输入有边的两个顶点（前为尾后为头）");
        scanf("%c,%c%c",&v1,&v2,&c);
        printf("输入的数据为%c,%c\n",v1,v2);
        i=Locate(O,v1);
        j=Locate(O,v2);
        //printf("%d %d\n",i,j);
        ArcNode *p=new ArcNode;
        p->headvex=j;
        p->tailvex=i;
        p->tlink=O.vertices[i].firstout;
        O.vertices[i].firstout=p;
        //printf("%d ",O.vertices[i].firstout->tailvex);
        p->hlink=O.vertices[j].firstin;
        O.vertices[j].firstin=p;
        //printf("%d ",O.vertices[j].firstin->headvex);
        //printf("%d %d\n",O.vertices[i].firstout->tailvex,O.vertices[j].firstin->headvex);
    }
   // printf("%d %d\n",O.vertices[2].firstout->tailvex,O.vertices[2].firstout->headvex);
}
void text(OList O)
{
    ArcNode* p;
    for(int i=0;i<O.vexnum;i++)
    {
       p=O.vertices[i].firstout;
       printf("%c ",O.vertices[i].data);
       while(p!=NULL)
       {
           printf("%d,%d ",p->tailvex,p->headvex);
           p=p->tlink;
       }
       printf("\n");
    }
}
int main()
{
    OList O;
    CreateOList(O);
    text(O);
    return 0;
}
