#include<stdio.h>
#include<string.h>
typedef struct Edge
{
    char data[30];
    struct Edge *next;
}edge;
typedef struct vex
{
    edge *first;
}vex;
typedef struct HashTable
{
    vex table[35];
    int lenth;
}Hashtable;
void Hash(Hashtable &H,char str[])
{
    int i;
    edge *p=new edge;
    strcpy(p->data,str);
//    printf("||%s ||",str);
//    printf("//%s //",p->data);
    i=str[0]%30;
//    printf("|%d |",i);
    p->next=H.table[i].first;
    H.table[i].first=p;
//    printf("*%s *%s\n",H.table[i].first->data,H.table[i].first->next->data);
}
void CreateHashTable(Hashtable &H)
{
    char str[30],g;
    printf("输入名字的个数\n");
    scanf("%d%c",&H.lenth,&g);
    printf("lenth=%d\n",H.lenth);
    for(int i=0;i<30;i++)
    {
        H.table[i].first=NULL;
    }
    printf("输入名字\n");
    for(int i=0;i<H.lenth;i++)
    {
        scanf("%s",str);
        scanf("%c",&g);
        printf("输入的名字为%s\n",str);
        Hash(H,str);
    }
}
int FindKey(HashTable H)
{
    char str[30];
    int i,j;
    printf("输入要查找的名字\n");
    scanf("%s",str);
    i=str[0]%30;
    edge *p=H.table[i].first;
    j=strcmp(str,p->data);
    if(j==0)return i;
    while(j!=0)
    {
        p=p->next;
        j=strcmp(str,p->data);
        if(j==0)return i;
        if(p==NULL) break;
    }
    return -1;
}
void text(Hashtable H)
{
    for(int i=0;i<30;i++)
    {
        edge *p=H.table[i].first;
        printf("%d ",i);
        while(p!=NULL)
        {
            printf("%s ",p->data);
            p=p->next;
        }
        printf("\n");
    }
}
int main()
{
    Hashtable H;
    int i;
    CreateHashTable(H);
    text(H);
    i=FindKey(H);
    if(i==-1)
    {
        printf("can't find this name\n");
    }
    else printf("%d",i);
    return 0;
}
