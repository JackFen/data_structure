#include<stdio.h>
typedef struct QNode
{
    int data;
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
void EnQueue(LinkQueue &Q,int e)
{
    Queue p=new QNode;
    p->data=e;
    Q.rear->next=p;
    p->next=NULL;
    Q.rear=p;
}
void DeQueue(LinkQueue &Q,int &e)
{
    Queue q=Q.front->next;
    e=q->data;
    Q.front->next=q->next;
    if(q==Q.rear) Q.rear=Q.front;
    delete q;
}
void GetHead(LinkQueue Q,int &e)
{
    if(Q.front==Q.rear) return;
    e=Q.front->next->data;
}
void outQueue(LinkQueue Q)
{
    Queue p=Q.front->next;
    while(p!=Q.rear)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("%d ",p->data);
}
int main()
{
    LinkQueue Q;
    int e,f,g,h;
    InitQueue(Q);
    printf("输入三个数");
    for(int i=0;i<3;i++)
    {
        scanf("%d",&e);
        EnQueue(Q,e);
    }
    outQueue(Q);
    GetHead(Q,h);
    printf("%d",h);
    printf("出队");
    DeQueue(Q,f);
    DeQueue(Q,g);
    printf("%d ",f);
    printf("%d",g);
    return 0;
}
