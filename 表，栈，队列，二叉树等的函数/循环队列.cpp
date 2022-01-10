#include<stdio.h>
#define MAXSIZE 10
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;
void Initequeue(SqQueue &Q)
{
    Q.base=new int[MAXSIZE];
    if(!Q.base)return;
    Q.front=Q.rear=0;
}
void EnQueue(SqQueue &Q,int e)
{
    if((Q.rear+1)%MAXSIZE==Q.front)return;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXSIZE;
}
void DeQueue(SqQueue &Q,int &e)
{
    if(Q.front==Q.rear)return;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXSIZE;
}
int GetHead(SqQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.base[Q.front];

}
void outQueue(SqQueue Q)
{
    int i=Q.front;
    while(i!=Q.rear)
    {
        printf("%d ",Q.base[i]);
        i++;
    }
}
int main()
{
    SqQueue Q;
    int e,f;
    Initequeue(Q);
    printf("输入三个数");
    for(int i=0;i<3;i++)
    {
        scanf("%d",&e);
        EnQueue(Q,e);
    }
    outQueue(Q);
    printf("出队");
    DeQueue(Q,f);
    printf("%d",f);
    return 0;
}
