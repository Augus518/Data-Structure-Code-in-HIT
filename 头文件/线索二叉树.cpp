#include <iostream>
using namespace std;
#include <cstdio>
typedef struct node
{
    int data;
    int ltag,rtag; //���ұ�־
    node *lchild,*rchild;
};//�����������Ľ������
node *pre=NULL; //ȫ����
node *CreatTree() //���������뽨��������
{
    node *T;
    int e;
    cin>>e;
    if(e==0)
    {
        T=NULL;
    }
    else
    {
        T=new node;
        T->data=e;
        T->ltag=1;          //��ʼ��ʱָ���־��Ϊ0
        T->rtag=1;
        T->lchild=CreatTree();
        T->rchild=CreatTree();
    }
    return T;
}

//�����������������������㷨
void Inordering(node* p)
{
    //��������p����������
    if(p)  //p�ǿ�ʱ,��ǰ���ʽ����*p
    {
        Inordering(p->lchild); //������������
        //����ֱ��������������֮ǰ�൱�ڱ����㷨�з��ʽ��Ĳ���
        p->ltag=(p->lchild)?1:0; //��ָ��ǿ�ʱ���־Ϊ1
        //(��0),����Ϊ0(��1)
        p->rtag=(p->rchild)?1:0;
        if(pre)  //��*p��ǰ��*pre����
        {
            if(pre->rtag==0) //��*p��ǰ���ұ�־Ϊ����
                pre->rchild=p; //��*pre��������ָ��������
            if(p->ltag==0) //*p�����־Ϊ����
                p->lchild=pre; //��*p��������ָ������ǰ��
        } // ��ɴ���*pre������
        pre=p; //��pre����һ���ʽ�������ǰ��
        Inordering(p->rchild); //������������
    }
}
//�������������������������̽��,ʱ�临�ӶȲ��������ĸ߶�h,��O(h)
node *InorderSuccessor(node *p)
{
    //���������������ҽ��*p��������,��p�ǿ�
    node *q;
    if (p->rtag==0) //*p��������Ϊ��
        return p->rchild; //������������ָ��������
    else
    {
        q=p->rchild; //��*p���Һ��ӿ�ʼ����
        while (q->ltag==1)
            q=q->lchild; //�������ǿ�ʱ,���������²���
        return q; //��q��������Ϊ��ʱ,�����������½��
    } //end if
}

//����������������������ǰ�����,ʱ�临�ӶȲ��������ĸ߶�h,��O(h)
node *Inorderpre(node *p)
{
    //���������������ҽ��*p������ǰ��,��p�ǿ�
    node *q;
    if (p->ltag==0) //*p��������Ϊ��
        return p->lchild; //������������ָ������ǰ��
    else
    {
        q=p->lchild; //��*p�����ӿ�ʼ����
        while (q->rtag==1)
            q=q->rchild; //�������ǿ�ʱ,���������²���
        return q; //��q��������Ϊ��ʱ,�����������½��
    }
}

//������������������
void TraverseInorderThrTree(node* p)
{
    if(p) //���ǿ�
    {
        while(p->ltag==1)
            p=p->lchild; //�Ӹ������������½��,���������еĿ�ʼ���
        do
        {
            printf("%d ",p->data); //���ʽ��
            p=InorderSuccessor(p); //��*p��������

        }
        while(p);
    }
    cout<<endl;
}
int main()
{
    node *T;
    cout<<"���������뽨����������"<<endl;
    T=CreatTree();
    cout<<"��������������"<<endl;
    Inordering(T);
    cout<<"������������ϣ�"<<endl;
    cout<<"���������������������"<<endl;
    TraverseInorderThrTree(T);
    return 0;
}
