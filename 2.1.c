#include<string.h>
#include<malloc.h> /* malloc()�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<stdlib.h> /* atoi() */
#include<math.h> /* floor(),ceil(),abs() */

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
typedef int ElemType;
typedef int Status;
typedef int Boolean;
typedef struct
{
    ElemType *elem; /* �洢�ռ��ַ */
    int length; /* ��ǰ���� */
    int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
} SqList;

Status InitList(SqList *L) /* �㷨2.3 */
{
    /* �������������һ���յ�˳�����Ա� */
    (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW); /* �洢����ʧ�� */
    (*L).length=0; /* �ձ���Ϊ0 */
    (*L).listsize=LIST_INIT_SIZE; /* ��ʼ�洢���� */
    return OK;
}

Status ListInsert(SqList *L,int i,ElemType e) /* �㷨2.4 */
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
    /* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
    ElemType *newbase,*q,*p;
    if(i<1||i>(*L).length+1) /* iֵ���Ϸ� */
        return ERROR;
    if((*L).length>=(*L).listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
    {
        newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW); /* �洢����ʧ�� */
        (*L).elem=newbase; /* �»�ַ */
        (*L).listsize+=LISTINCREMENT; /* ���Ӵ洢���� */
    }
    q=(*L).elem+i-1; /* qΪ����λ�� */
    for(p=(*L).elem+(*L).length-1; p>=q; --p) /* ����λ�ü�֮���Ԫ������ */
        *(p+1)=*p;
    *q=e; /* ����e */
    ++(*L).length; /* ����1 */
    return OK;
}

Status ListTraverse(SqList L,void(*vi)(ElemType*))
{
    /* ��ʼ������˳�����Ա�L�Ѵ��� */
    /* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
    /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
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
    /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
    return L.length;
}

Status GetElem(SqList L,int i,ElemType *e)
{
    /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
    /* �����������e����L�е�i������Ԫ�ص�ֵ */
    if(i<1||i>L.length)
        exit(ERROR);
    *e=*(L.elem+i-1);
    return OK;
}

void print(ElemType *c)
{
    printf("%d",*c);
}

void MergeList(SqList La,SqList Lb,SqList *Lc) /* �㷨2.2 */
{
    /* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С� */
    /* �鲢La��Lb�õ��µ����Ա�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ����� */
    int i=1,j=1,k=0;
    int La_len,Lb_len;
    ElemType ai,bj;
    InitList(Lc); /* �����ձ�Lc */
    La_len=ListLength(La);
    Lb_len=ListLength(Lb);
    while(i<=La_len&&j<=Lb_len) /* ��La�ͱ�Lb���ǿ� */
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
    while(i<=La_len) /* ��La�ǿ��ұ�Lb�� */
    {
        GetElem(La,i++,&ai);
        ListInsert(Lc,++k,ai);
    }
    while(j<=Lb_len) /* ��Lb�ǿ��ұ�La�� */
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
       
        InitList(&La); /* �����ձ�La */
        for(j=1; j<=n; j++) /* �ڱ�La�в���n��Ԫ�� */
            ListInsert(&La,j,a[j-1]);
        InitList(&Lb); /* �����ձ�Lb */
        for(j=1; j<=m; j++) /* �ڱ�Lb�в���m��Ԫ�� */
            ListInsert(&Lb,j,b[j-1]);
        MergeList(La,Lb,&Lc);
        /* �����Lc������ */
        ListTraverse(Lc,print);
    }
    return 0;
}
