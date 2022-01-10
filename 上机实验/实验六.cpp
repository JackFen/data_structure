#include<stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)
using namespace std;

typedef struct
{
    int key;
    int data;
}Data;
typedef struct
{
    Data *r;
    int lenth;
}Sqlist;
void CreateList(Sqlist &L)
{
    printf("初始化随机数据（119个）\n");
    L.r=new Data[120];
    L.lenth=120;
    srand((int)time(0));
    for (int i = 1; i < 120; i++)
    {
        L.r[i].key=random(100);
        L.r[i].data=L.r[i].key;
        printf(" %d ",L.r[i].data);
    }
}
void BubbleMerge(Sqlist &L)
{
    printf("冒泡排序\n");
    int m=L.lenth-1,flag=1,cout1=0,cout2=0;
    while(flag&&m>0)
    {
        flag=0;
        for(int j=1;j<m;j++)
        {
            cout1++;
            if(L.r[j].key>L.r[j+1].key)
            {
                flag=1;
                Data t;
                t=L.r[j];
                L.r[j]=L.r[j+1];
                L.r[j+1]=t;
                cout2+=3;
            }
        }
        m--;
    }
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
void InsertSort(Sqlist &L)
{
    printf("直接插入排序\n");
    int cout1=0,cout2=0;
    int i;
    for(i=2;i<L.lenth;i++)
    {
        cout1++;
        if(L.r[i].key<L.r[i-1].key)
        {
           L.r[0]=L.r[i];
           L.r[i]=L.r[i-1];
           int j;
           for(j=i-2;L.r[0].key<L.r[j].key;--j)
             {
                L.r[j+1]=L.r[j];
                cout2++;
             }
           L.r[j+1]=L.r[0];
           cout2++;
        }
    }
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
void SimpleSelectSort(Sqlist &L)
{
    printf("简单选择排序排序\n");
    int cout1=0,cout2=0;
    for(int i=1;i<L.lenth-1;i++)
    {
        int k=i;
        for(int j=i+1;j<=L.lenth-1;j++)
        {
            cout1++;
            if(L.r[j].key<L.r[k].key)
            {
                k=j;
            }
        }
        if(k!=i)
        {
            cout2++;
            Data t;
            t=L.r[k];
            L.r[k]=L.r[i];
            L.r[i]=t;
        }
    }
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
int Partition(Sqlist &L,int low,int high,int &cout1,int &cout2)
{
    L.r[0]=L.r[low];
    int pivotkey=L.r[low].key;
    while(low<high)
    {
        while(low<high&&L.r[high].key>=pivotkey)
            {
                high--;
                cout1++;
            }
        L.r[low]=L.r[high];
        cout2++;
        while(low<high&&L.r[low].key<=pivotkey)
            {
                low++;
                cout1++;
            }
        L.r[high]=L.r[low];
        cout2++;
    }
    L.r[low]=L.r[0];
    return low;
}
void QSort(Sqlist &L,int low,int high,int &cout1,int &cout2)
{
    if(low<high)
    {
        int pivotloc;
        pivotloc=Partition(L,low,high,cout1,cout2);
        QSort(L,low,pivotloc-1,cout1,cout2);
        QSort(L,pivotloc+1,high,cout1,cout2);
    }
}
void QuickSort(Sqlist &L)
{
    printf("快速排序\n");
    int cout1=0,cout2=0;
    QSort(L,1,L.lenth-1,cout1,cout2);
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
void ShellInsert(Sqlist &L,int dk,int &cout1,int &cout2)
{
    for(int i=dk+1;i<L.lenth;i++)
    {
        cout1++;
        if(L.r[i].key<L.r[i-dk].key)
        {
            L.r[0]=L.r[i];
            int j;
            for(j=i-dk;j>0&&L.r[0].key<L.r[j].key;j-=dk)
                {
                   L.r[j+dk]=L.r[j];
                   cout2++;
                }
            L.r[j+dk]=L.r[0];
            cout2++;
        }
    }
}
void ShellSort(Sqlist &L,int dt[],int t)
{
    printf("希尔排序\n");
    int cout1=0,cout2=0;
    for(int k=0;k<t;k++)
    {
        ShellInsert(L,dt[k],cout1,cout2);
    }
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
void HeapAdjust(Sqlist &L,int s,int m,int &cout1,int &cout2)
{
    Data rc=L.r[s];
    for(int j=2*s;j<=m;j*=2)
    {
        if(j<m&&L.r[j].key<L.r[j+1].key)
        {
            j++;
            cout1++;
        }
        if(rc.key>=L.r[j].key)
        {
            cout1++;
            break;
        }
        L.r[s]=L.r[j];
        s=j;
        cout2++;
    }
    L.r[s]=rc;
    cout2++;
}
void CreateHeap(Sqlist &L,int &cout1,int &cout2)
{
    int n=L.lenth-1;
    for(int i=n/2;i>0;i--)
    {
        HeapAdjust(L,i,n,cout1,cout2);
    }
}
void HeapSort(Sqlist &L)
{
    printf("堆排序\n");
    int cout1=0,cout2=0;
    CreateHeap(L,cout1,cout2);
    for(int i=L.lenth-1;i>1;i--)
    {
        Data x=L.r[1];
        L.r[1]=L.r[i];
        L.r[i]=x;
        cout2+=3;
        HeapAdjust(L,1,i-1,cout1,cout2);
    }
    printf("关键字比较次数为%d,关键字移动次数为%d\n",cout1,cout2);
}
void text(Sqlist L)
{
    int m=1;
    while(m<=L.lenth-1)
    {
        printf(" %d ",L.r[m].data);
        m++;
    }
}
int main()
{
    Sqlist L;
    CreateList(L);
    int dt[3]={5,3,1},k=0;
    printf("\n");
    printf("选择排序算法（1、冒泡排序 2、直接插入排序 3、简单选择排序 4、快速排序 5、希尔排序 6、堆排序 0、不排序）\n");
    scanf("%d",&k);
    switch(k)
    {
        case 1:BubbleMerge(L);break;
        case 2:InsertSort(L);break;
        case 3:SimpleSelectSort(L);break;
        case 4:QuickSort(L);break;
        case 5:ShellSort(L,dt,3);break;
        case 6: HeapSort(L);break;
        default:printf("程序结束");return 0;
    }
     printf("排序结果为\n");
    text(L);
    return 0;
}
