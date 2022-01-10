#include<stdio.h>
typedef struct LNode
{
    int data;
    struct LNode *next;
}Lnode,*linklist;
void InitList(linklist &L)
{
    L=new Lnode;
    L->next=NULL;
}
void FrontCreateList(linklist &L,int n)
{
    printf("输入数据");
    for(int i=0;i<n;i++)
    {
        linklist p=new Lnode;
        scanf("%d",&p->data);
        p->next=L->next;
        L->next=p;
    }
}
void RearCreatList(linklist &L,int n)
{
    linklist r=L;
    printf("输入数据");
    for(int i=0;i<n;i++)
    {
        linklist p=new Lnode;
        scanf("%d",&p->data);
        p->next=NULL;
        r->next=p;
        r=p;
    }
}
int GetElem(linklist &L,int i,int &e)
{
    linklist p=L->next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)return -2;
    e=p->data;
    return 1;
}
Lnode *LocateElem(linklist L,int e)
{
    linklist p=L->next;
    while(p&&(p->data!=e))
    {
        p=p->next;
    }
    return p;
}
void InsertElem(linklist &L,int i,int e)
{
    linklist p=L;
    int j=0;
    while(p&&j<i-1)
    {
        p=p->next;
        ++j;
    }
    linklist s=new Lnode;
    s->data=e;
    s->next=p->next;
    p->next=s;
}
int  DeleteElem(linklist &L,int i,int e)
{
    linklist p=L;
    int j=0;
    while(p&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(i<0||p->next==NULL)return -1;
    linklist q=p->next;
    p->next=q->next;
    delete q;
    return 1;
}
void outlist(linklist L)
{
    linklist p=L->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}
int main()
{
    linklist L;
    int n,e,j,f,g;
    InitList(L);
    printf("输入链表的长度");
    scanf("%d",&n);
    RearCreatList(L,n);
    outlist(L);
    printf("输入要读取数据的位置");
    scanf("%d",&j);
    g=GetElem(L,j,e);
    printf("%d\n",e);
    printf("输入要删除的位置及数据");
    scanf("%d %d",&j,&f);
    DeleteElem(L,j,f);
    outlist(L);
    return 0;
}
