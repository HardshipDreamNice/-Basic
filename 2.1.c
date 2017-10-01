#include<string.h>
#include<malloc.h> /* malloc()等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
#include<math.h> /* floor(),ceil(),abs() */

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
typedef int ElemType;
typedef int Status;
typedef int Boolean;
typedef struct
{
    ElemType *elem; /* 存储空间基址 */
    int length; /* 当前长度 */
    int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
} SqList;

Status InitList(SqList *L) /* 算法2.3 */
{
    /* 操作结果：构造一个空的顺序线性表 */
    (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW); /* 存储分配失败 */
    (*L).length=0; /* 空表长度为0 */
    (*L).listsize=LIST_INIT_SIZE; /* 初始存储容量 */
    return OK;
}

Status ListInsert(SqList *L,int i,ElemType e) /* 算法2.4 */
{
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
    /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
    ElemType *newbase,*q,*p;
    if(i<1||i>(*L).length+1) /* i值不合法 */
        return ERROR;
    if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
    {
        newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW); /* 存储分配失败 */
        (*L).elem=newbase; /* 新基址 */
        (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
    }
    q=(*L).elem+i-1; /* q为插入位置 */
    for(p=(*L).elem+(*L).length-1; p>=q; --p) /* 插入位置及之后的元素右移 */
        *(p+1)=*p;
    *q=e; /* 插入e */
    ++(*L).length; /* 表长增1 */
    return OK;
}

Status ListTraverse(SqList L,void(*vi)(ElemType*))
{
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
    /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
    ElemType *p;
    int i;
    p=L.elem;
    for(i=1; i<=L.length; i++)
    {
        if(i!=1)
            printf(" ");
        vi(p++);
    }
    printf("\n");
    return OK;
}

int ListLength(SqList L)
{
    /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
    return L.length;
}

Status GetElem(SqList L,int i,ElemType *e)
{
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
    /* 操作结果：用e返回L中第i个数据元素的值 */
    if(i<1||i>L.length)
        exit(ERROR);
    *e=*(L.elem+i-1);
    return OK;
}

void print(ElemType *c)
{
    printf("%d",*c);
}

void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.2 */
{
    /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
    /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
    int i=1,j=1,k=0;
    int La_len,Lb_len;
    ElemType ai,bj;
    InitList(Lc); /* 创建空表Lc */
    La_len=ListLength(La);
    Lb_len=ListLength(Lb);
    while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
    {
        GetElem(La,i,&ai);
        GetElem(Lb,j,&bj);
        if(ai<=bj)
        {
            ListInsert(Lc,++k,ai);
            ++i;
        }
        else
        {
            ListInsert(Lc,++k,bj);
            ++j;
        }
    }
    while(i<=La_len) /* 表La非空且表Lb空 */
    {
        GetElem(La,i++,&ai);
        ListInsert(Lc,++k,ai);
    }
    while(j<=Lb_len) /* 表Lb非空且表La空 */
    {
        GetElem(Lb,j++,&bj);
        ListInsert(Lc,++k,bj);
    }
}

int main()
{
    int n,m,a[105],b[105],j;
	SqList La,Lb,Lc;
    while(~scanf("%d",&n))
    {
        int j;
        for(j = 0; j<n; j++)
            scanf("%d",&a[j]);
        scanf("%d",&m);
        for(j = 0; j<m; j++)
            scanf("%d",&b[j]);
       
        InitList(&La); /* 创建空表La */
        for(j=1; j<=n; j++) /* 在表La中插入n个元素 */
            ListInsert(&La,j,a[j-1]);
        InitList(&Lb); /* 创建空表Lb */
        for(j=1; j<=m; j++) /* 在表Lb中插入m个元素 */
            ListInsert(&Lb,j,b[j-1]);
        MergeList(La,Lb,&Lc);
        /* 输出表Lc的内容 */
        ListTraverse(Lc,print);
    }
    return 0;
}
