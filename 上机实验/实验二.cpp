#include<stdio.h>
#define M 2 //停车场最大容量//
#include<string.h>
typedef struct
{
    char car[20];
}Car;
typedef struct
{
    Car CarNo[M];
    int CarTimein[M];
    int top;
}Sqstack;
typedef struct StackNode
{
    Car CarNo;
    int CarTimein;
    struct StackNode *next;
}Stacknode,*LinkStack;
void IniteStack(LinkStack &S)
{
    S=NULL;
}
void Push(LinkStack &S,Car e1,int e2)
{
    LinkStack p=new Stacknode;
    p->CarNo=e1;
    p->CarTimein=e2;
    p->next=S;
    S=p;
}
void Pop(LinkStack &S,Car &e1,int &e2)
{
    LinkStack q;
    q=S;
    e1=q->CarNo;
    e2=q->CarTimein;
    S=q->next;
    delete q;
}
typedef struct queueNode
{
   Car CarNo;
   int CarTime;
   struct queueNode *next;
}QueueNode,*Queue;
typedef struct
{
    Queue front;
    Queue rear;
}queue;
void IniteQueue(queue &Q)
{
    Q.front=Q.rear=new QueueNode;
    Q.front->next=NULL;
}
void EnQueue(queue &Q,Car e1,int e2)
{
    Queue p=new QueueNode;
    p->CarNo=e1;
    p->CarTime=e2;
    Q.rear->next=p;
    p->next=NULL;
    Q.rear=p;
}
void DeQueue(queue &Q,Car &e1,int &e2)
{
    Queue q=Q.front->next;
    e1=q->CarNo;
    e2=q->CarTime;
    Q.front->next=q->next;
    if(q==Q.rear) Q.rear=Q.front;
    delete q;
}
void outQueue(queue Q)
{
    Queue p=Q.front->next;
    while(p!=Q.rear)
    {
        printf("%s ",p->CarNo.car);
        p=p->next;
    }
    printf("%s ",p->CarNo.car);
}
void Traverqueue(queue Q,int &i)
{
    i=0;
    Queue p=Q.front->next;
    while(p!=NULL)
    {
        i++;
        p=p->next;
    }
}
void CreateStack(Sqstack *&S)
{
    S=new Sqstack[M];
    S->top=-1;
}
void PushStack(Sqstack *&S,Car e1,int e2)
{
    if(S->top>=1)return;
    S->top++;
    S->CarNo[S->top]=e1;
    S->CarTimein[S->top]=e2;
}
void outstack(Sqstack *&S)
{
    int p;
    p=S->top;
    if(p==-1){printf("0");return;}
    while(p>-1)
    {
        printf("%s ",S->CarNo[p].car);
        p--;
    }
}
void PopStack(Sqstack *&S,Car &e1,int &e2)
{
    if(S->top==-1)return;
    e1=S->CarNo[S->top];
    e2=S->CarTimein[S->top];
    S->top--;
}
int isnotEmpty(LinkStack S)
{
    if(S==NULL)return 0;
    else return 1;
}
void outStack(LinkStack S)
{
    LinkStack p=S;
    while(p)
    {
        printf("%s ",p->CarNo.car);
        p=p->next;
    }
}
void fee(Sqstack *&S,LinkStack &S2,queue &Q2,Car e1,int e2)
{
    int time,money,e4,e6,e8;
    Car e3,e5,e7;
    while(strcmp(S->CarNo[S->top].car,e1.car)!=0)
    {
       Push(S2,S->CarNo[S->top],S->CarTimein[S->top]);
       S->top--;
    }
    time=e2-(S->CarTimein[S->top]);
    money=2*time;
    PopStack(S,e7,e8);
    printf("%s车在停车场停了%d小时，收费%d元\n",e7.car,time,money);
    while(isnotEmpty(S2))
    {
        Pop(S2,e3,e4);
        PushStack(*&S,e3,e4);
    }

    while((S->top<1)&&(Q2.front!=Q2.rear))
    {
        DeQueue(Q2,e5,e6);
        PushStack(S,e5,e2);
    }

    printf("停车场还剩的车为\n");
    outstack(S);
    printf("\n");
}
void find(queue &Q,queue &Q2,Car e1,int e2)
{
    int e4,e6;
    Car e3,e5;
    while(strcmp(Q.front->next->CarNo.car,e1.car)!=0)
    {
        DeQueue(Q,e3,e4);
        EnQueue(Q2,e3,e4);
    }
    DeQueue(Q,e3,e4);
    while(Q2.front!=Q2.rear)
    {
        DeQueue(Q2,e5,e6);
        EnQueue(Q,e5,e6);
    }
    printf("%s车已从便道离开\n",e1.car);
    printf("便道里的车有:");
   //printf("便道第一辆车%d\n",Q.front->next->CarNo);
    outQueue(Q);
    printf("\n");
}
void link(Sqstack *&S,LinkStack &S2,queue &Q2,queue &Q3,Car e1,int e2)
{
    int flag=0;
    for(int i=0;i<=M-1;i++)
    {
        if(strcmp(S->CarNo[i].car,e1.car)==0)
        {
            flag=1;
            break;
        }
    }
    if(flag) fee(S,S2,Q2,e1,e2);
    else find(Q2,Q3,e1,e2);
}
void MainSystem(Sqstack *&S,LinkStack &S2,queue &Q2,queue &Q3)
{
    int e2,i=0;
    Car e1;
    char c,f;
    printf("请输入操作，车牌，时间 输入格式：(A,车牌,时间)A代表进入、D代表离开、E代表结束。时间单位为小时（不包括小数）\n");
    while(1)
    {
     scanf("%c,%s",&c,e1.car);
     scanf("%c",&f);
     int j;
     j=0;
     while(e1.car[j]!=',')
     {
         j++;
     }
     e2=e1.car[j+1];
     e1.car[j]='\0';
     e1.car[j+1]='\0';
     if(c=='A')
     {
         if(S->top<M-1)
         {
             PushStack(S,e1,e2);
             printf("停车完成\n");
             printf("停车场里的车辆有：");
             outstack(S);
             printf("\n");
             printf("请输入操作，车牌，时间\n");
         }
         else
         {
             EnQueue(Q2,e1,e2);
             Traverqueue(Q2,i);
             printf("停车场已满，该车现位于便道第%d号位\n",i);
             printf("便道里的车有：");
             outQueue(Q2);
             printf("\n");
             printf("请输入操作，车牌，时间\n");
         }
     }
     else if(c=='D')
     {
         link(S,S2,Q2,Q3,e1,e2);
     }
     else if(c=='E') break;
    }
    printf("退出");

}
int main()
{
    Sqstack *S;
    LinkStack S2;
    queue Q2,Q3;
    IniteStack(S2);
    IniteQueue(Q2);
    IniteQueue(Q3);
    CreateStack(S);
    MainSystem(S,S2,Q2,Q3);
    return 0;
}
