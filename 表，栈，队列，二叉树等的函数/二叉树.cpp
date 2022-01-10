#include<stdio.h>
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTnode,*BiTree;
typedef struct BiThrNode
{
    int data;
    struct BiThrNode *lchild,*rchild;
    int LTag,RTag;
}BiThrnode,*BiThrTree;
void FrontCreateTree(BiTree &T)
{
    char e;
    scanf("%c",&e);
    if(e=='#') T=NULL;
    else
    {
        T=new BiTNode;
        T->data=e;
        FrontCreateTree(T->lchild);
        FrontCreateTree(T->rchild);
    }
}
void FrontCreateThrTree(BiThrTree &T)
{
    char e;
    scanf("%c",&e);
    if(e=='#') T=NULL;
    else
    {
        T=new BiThrNode;
        T->data=e;
        FrontCreateThrTree(T->lchild);
        FrontCreateThrTree(T->rchild);
    }
}
void InorderTraverse(BiTree T)
{
    if(T)
    {
    InorderTraverse(T->lchild);
    printf("%c ",T->data);
    InorderTraverse(T->rchild);
    }
}
void InorderThrTraverseText(BiThrTree T)
{
    if(T)
    {
    InorderThrTraverseText(T->lchild);
    printf("%c ",T->data);
    InorderThrTraverseText(T->rchild);
    }
}
void FrontTraverse(BiTree T)
{
    if(T)
    {
    printf("%c ",T->data);
    FrontTraverse(T->lchild);
    FrontTraverse(T->rchild);
    }
}
void InorderThrTraverse(BiThrTree T)
{
   BiThrTree p=T->lchild;
   while(p!=T)
   {
       while(p->LTag==0) p=p->lchild;
       printf("%c ",p->data);
       while(p->RTag==1&&p->rchild!=T)
       {
           p=p->rchild;
           printf("%c ",p->data);
       }
       p=p->rchild;
   }
}
void RearTraverse(BiTree T)
{
    if(T)
    {
    RearTraverse(T->lchild);
    RearTraverse(T->rchild);
    printf("%c ",T->data);
    }
}
void Frontcopy(BiTree T,BiTree &NewT)
{
    if(T==NULL)
    {
        NewT=NULL;
        return;
    }
    else
    {
        NewT=new BiTnode;
        NewT->data=T->data;
        Frontcopy(T->lchild,NewT->lchild);
        Frontcopy(T->rchild,NewT->rchild);
    }
}
int Depth(BiTree T)
{
    int m,n;
    if(T==NULL) return 0;
    else
    {
       m=Depth(T->lchild);
       n=Depth(T->rchild);
       return m>n? m+1:n+1;
    }

}
int CountNode(BiTree T)
{
    if(T==NULL) return 0;
    else return CountNode(T->lchild)+CountNode(T->rchild)+1;
}
void InThreading(BiThrTree &p,BiThrTree &pre)//不带头结点的线索化，不过要先找到全局变量pre
{
    if(p)
    {
       InThreading(p->lchild,pre);
       if(!p->lchild)
       {
           p->LTag=1;
           p->lchild=pre;
       }
       else p->LTag=0;
       if(!pre->rchild)
       {
           pre->RTag=1;
           pre->rchild=p;
       }
       else pre->RTag=0;
       pre=p;
       InThreading(p->rchild,pre);
     }
}
void InorderThreading(BiThrTree &ThrT,BiThrTree &T)//带头结点的线索化
{
    void InThreading(BiThrTree &p,BiThrTree &pre);
    ThrT=new BiThrnode;
    BiThrTree pre;
    ThrT->LTag=1;
    ThrT->RTag=0;
    ThrT->rchild=ThrT;
    if(!T) ThrT->lchild=ThrT;
    else
    {
      ThrT->lchild=T;
      pre=ThrT;
      InThreading(T,pre);
      pre->rchild=ThrT;
      pre->RTag=1;
      ThrT->rchild=pre;
    }
}
int main()
{
    BiTree T;
    BiThrTree T1,T2;
    int a,b;
    FrontCreateThrTree(T2);
   InorderThrTraverseText(T2);
   printf("\n");
    InorderThreading(T1,T2);
//    printf("%c ",T1->lchild->data);
    InorderThrTraverse(T1);
//    printf("%c ",T1->lchild->data);
//    InorderThrTraverse(T1);
//    a=Depth(T);
//    b=CountNode(T);
//    printf("\n");
//    printf("%d ",a);
//    printf("%d",b);
    return 0;
}
