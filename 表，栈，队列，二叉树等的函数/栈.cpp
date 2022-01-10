#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef struct
{
    int *base;
    int *top;
    int stacksize;
}SqStack;
int IniteStack(SqStack &S)
{
    S.base=new int[MAXSIZE];
    if(!S.base)exit(-2);
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return 1;
}
int Push(SqStack &S,int e)
{
    if(S.top-S.base==S.stacksize){return -2;}
    *S.top++=e;
    return 1;
}
int Pop(SqStack &S,int &e)
{
    if(S.top==S.base)return -2;
    e=*--S.top;
    return 1;
}
int GetElem(SqStack S)
{
    if(S.top==S.base)return -2;
    return *(S.top-1);
}
void outstack(SqStack S)
{
    int i=1;
    while((S.top-i)>=S.base)
    {
        printf("%d ",*(S.top-i));
        ++i;
    }
}
int main()
{
    SqStack S;
    int e,x,y,g,f,h;
    h=IniteStack(S);
    printf("输入10个数字");
    for(int i=0;i<10;i++)
    {
        scanf("%d",&e);
        x=Push(S,e);
    }
         outstack(S);
        printf("\n");
        printf("获取栈顶元素%d",GetElem(S));
    printf("出栈");
    for(int j=0;j<10;j++)
    {
       y=Pop(S,g);
        printf("%d ",g);
    }
    return 0;
}
