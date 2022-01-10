#include<stdio.h>
#include<string.h>
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
void destroyStack(LinkStack &S)
{
    while(S)
    {
        if(S==NULL)return;
        printf("%d ",S->data);
        LinkStack q=S;
        S=S->next;
        delete q;
    }
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
typedef struct
{
char data;
float weight;
int parent;
int lchild;
int rchild;
}huffnode,*huffmantree;
void Select(huffmantree HT,int &s1,int &s2,int m)
{
    for(int i=1;i<=m;i++)
    {
        if(HT[i].parent==0)
        {
            s1=i;break;
        }
    }
    for(int i=s1+1;i<=m;i++)
    {
        if(HT[i].parent==0)
        {
            s2=i;break;
        }
    }
    for(int k=s1+1;k<=m;++k)
    {
        if(HT[k].weight<HT[s1].weight)
            {
                if(HT[k].parent==0)
                s1=k;
            }

    }
    for(int k=1;k<=m;++k)
    {
        if(s1==s2)s2--;
        if(s1==k)k++;
        if(HT[k].weight<HT[s2].weight)
        {
            if(HT[k].parent==0)
                s2=k;
              //  printf("flag\n");
        }
    }
  // printf("返回S1,S2为%d %d\n",s1,s2);
}
void CreateHuffmanTree(huffmantree &HT,int n)
{
    if(n<=1)return;
    int i,j,m,s1,s2;
    char c;
    m=2*n-1;
    HT=new huffnode[m+1];
    for(i=1;i<=m;++i)
    {
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=1;i<=n;i++)
    {
        printf("请输入数据及其概率(a,b)(不得大于等于1)\n");
        scanf("%c,%f%c",&HT[i].data,&HT[i].weight,&c);
        printf("输入的数据为%c,%0.3f\n",HT[i].data,HT[i].weight);
    }
     for(j=n+1;j<=m;j++)
    {
        Select(HT,s1,s2,(j-1));
        HT[s1].parent=j;
        HT[s2].parent=j;
        HT[j].lchild=s1;
        HT[j].rchild=s2;
        HT[j].weight=HT[s1].weight+HT[s2].weight;
    }
//    for(int k=1;k<=m;k++)
//    {
//        printf("%f\t",HT[k].weight);
//    }
}
void CreateCode(huffmantree HT,LinkStack &S,int n)
{
    char c;
    int i=1;
    for(int j=1;j<=n;j++)
    {
        i=j;
      printf("%c的哈夫曼编码为",HT[i].data);
      while(HT[i].parent!=0)
      {
        if(HT[HT[i].parent].lchild==i)Push(S,0);
        else Push(S,1);
        i=HT[i].parent;
     }
      destroyStack(S);
      printf("\n");
    }
}
void translatecode(huffmantree HT,int n)
{
    char str[20];
    int m=2*n-1;
    int k=m;
    printf("输入哈夫曼码");
    scanf("%s",str);
//    printf("输入的哈夫曼码首位为%d %d %d\n",str[0],str[1],str[2]);
    for(int j=0;j<strlen(str);j++)
    {
        if(str[j]-48==0) k=HT[k].lchild;
        else if(str[j]-48==1) k=HT[k].rchild;
    }
    printf("该哈夫曼码对应为%c",HT[k].data);
}
int main()
{
    huffmantree HT;
    LinkStack S;
    int n;
    char t;
    IniteStack(S);
    printf("输入要编码的字母个数:");
    scanf("%d",&n);
    scanf("%c",&t);
    CreateHuffmanTree(HT,n);
    CreateCode(HT,S,n);
    translatecode(HT,n);
    return 0;
}
