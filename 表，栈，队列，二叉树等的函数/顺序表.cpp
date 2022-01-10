#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef struct
{
    int *base;
    int lenth;
}Sqlist;
void Inite_list(Sqlist &L)
{
    L.base=new int[MAXSIZE];
    if(!L.base)exit(-1);
    L.lenth=0;
}
void CreateList(Sqlist &L,int n)
{
    int i=0;
    while(i<n)
    {
        printf("输入数据");
        scanf("%d",&L.base[i]);
        i++;
        ++L.lenth;
    }
}
int localelist(Sqlist L,int e)
{
    int i;
    for(i=0;i<L.lenth;i++)
    {
        if(L.base[i]==e)return i+1;
    }
    return -2;
}
int GetElem(Sqlist L,int i,int &e)
{
    if(i<1||i>L.lenth)return -1;
    e=L.base[i-1];
    return 1;
}
int ListInsert(Sqlist &L,int e,int i)
{
    int j;
    if(i<1||i>L.lenth)return -2;
    if(L.lenth==MAXSIZE)return -2;
    for(j=L.lenth-1;j>=i-1;j--)
    {
        L.base[j+1]=L.base[j];
    }
    L.base[i-1]=e;
    ++L.lenth;
    return 1;
}
int DeleteList(Sqlist &L,int e,int i)
{
    if(i<1||i>L.lenth)return -2;
    for(int j=i;j<=L.lenth-1;j++)
    {
        L.base[j-1]=L.base[j];
    }
    --L.lenth;
    return 1;
}
void outlist(Sqlist L)
{
    for(int i=0;i<L.lenth;i++)
    {
        printf("%d ",L.base[i]);
    }
}
int main()
{
    Sqlist L;
    int x,y,n=10,e,i,f,g;
    Inite_list(L);
    CreateList(L,n);
    printf("输入要查找的数字");
    scanf("%d",&x);
    y=localelist(L,x);
    printf("%d\n",y);
    outlist(L);
    printf("输入你要删除的数字及其位置");
    scanf("%d %d",&e,&i);
    DeleteList(L,e,i);
    outlist(L);
    printf("输入你要插入的数据及其位置");
    scanf("%d %d",&f,&g);
    ListInsert(L,f,g);
    outlist(L);
    return 0;
}
