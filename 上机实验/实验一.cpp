#include<stdio.h>
#include<stdlib.h>
typedef struct listNode
{
    int data;
    int rank;
    struct listNode *next;
}listNode,*linklist;
void Createlist(linklist &L,int n)
{
    L=new listNode;
    L->next=L;
    linklist r=L;
    int i;
    for(i=0;i<n;i++)
    {
        linklist p=new listNode;
        p->rank=i+1;
        printf("输入第%d个人的密码",i+1);
        scanf("%d",&(p->data));
        p->next=L;
        r->next=p;
        r=p;
    }
    r->next=L->next;
}
void outlist(linklist L)
{
    linklist p=L->next;
    linklist r;
    r->next=p;
    do
    {
        printf("%d ",p->rank);
        p=p->next;
    }while(p!=L->next);
    for(int i=0;i<0;i++)
    {
        p=p->next;
    }
    linklist q=p;
    printf("%d ",q->rank);
}
void joeph(linklist &L,int n,int m)
{
    printf("出队序列为");
    linklist p=L->next;
    while(p!=L)
    {
        if(p->next==p)
        {
            printf("%d ",p->rank);
            linklist r=p;
            L->next=L;
            delete r;
            break;
        }
        for(int i=0;i<m+n-2;i++)
        {
            p=p->next;
        }
        linklist q=p->next;
        printf("%d ",(q->rank));
        p->next=q->next;
        m=q->data;
        --n;
        delete q;
       p=p->next;
      }
}
int main()
{
    linklist L;
    int n,m=20;
    printf("输入数据个数");
    scanf("%d",&n);
    Createlist(L,n);
    //outlist(L);
    printf("输入报数上限值");
    scanf("%d",&m);
    joeph(L,n,m);
    return 0;
}
