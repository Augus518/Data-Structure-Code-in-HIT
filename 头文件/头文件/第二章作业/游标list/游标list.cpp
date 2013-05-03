#include <iostream>
using namespace std;
#define maxsize 100
#define ElemType int
struct spacestr
{
    ElemType data;
    int  next;
} ;  /*�������*/
spacestr  SPACE[maxsize];/*�洢��*/
typedef  int  position,Cursor;
Cursor  avail;
position head;
void Initialize()
{
    int j;
    /*  �������ӳ��н��*/
    for (j=0; j<maxsize-1; j++ )
        SPACE[j].next=j+1;
    /*  ���һ�����ָ����Ϊ��*/
    SPACE[j].next=-1;
    /*  ��ʶ���Ա�*/
    avail=0;
    head=0;
}
//���ÿռ�ķ������
Cursor GetNode() //q=new spacestr;
{
    Cursor p;
    if (SPACE[avail].next ==-1)
        p=-1;
    else
    {
        p= SPACE[avail].next;
        SPACE[avail].next =SPACE[ p ].next;
    }
    return p;
}
//���ÿռ�Ļ��ղ���
void FreeNode(Cursor q)
{
    SPACE [q].next =SPACE[avail].next ;
    SPACE[avail].next=q ;
}
//�������
void  Insert(ElemType x,position p,spacestr *SPACE)
{
    position  q;
    q=GetNode();
    SPACE[q].data=x;
    SPACE[q].next=SPACE[p].next;
    SPACE[p].next=q;
}
//ɾ������
void Delete(position p,spacestr *SPACE)
{
    position q;
    if(SPACE[p].next !=-1)
    {
        q = SPACE[p].next;
        SPACE[p].next = SPACE[q].next ;
        FreeNode(q);
    }
}
int main()
{
    Initialize();
    for(int i=0;i<20;i++)
    Insert(i,19-i,SPACE);
    return 0;
}
