#include<stdio.h>
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
int GetTop(LinkStack &S)
{
    if(S) return S->data;
}
void outStack(LinkStack S)
{
    LinkStack p=S;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}
void TraverseStack(LinkStack &S)
{
    if(S==NULL)return;
    printf("%d ",S->data);
    TraverseStack(S->next);
}
int main()
{
    LinkStack S;
    int e,q,f=0,g;
    IniteStack(S);
    printf("����������");
    for(int i=0;i<3;i++)
    {
        scanf("%d",&e);
        Push(S,e);
    }
    outStack(S);
    printf("����");
    TraverseStack(S);
    printf("��ջ");
    Pop(S,f);
    printf("%d",f);
    printf("\n");
    outStack(S);
    return 0;
}
