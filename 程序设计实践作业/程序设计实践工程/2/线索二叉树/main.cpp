#include <iostream>
#include <stack>
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

//ǰ��������
void PreOrderThreading(node* p)
{
    stack<node* >nodeTypeStack;
    node* a[1000];
    int b=0;
    node* current;
    current=p;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            cout<<current->data<<" ";
            a[b++]=current;
            nodeTypeStack.push(current);
            current=current->lchild;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            current=current->rchild;
        }
    }
    cout<<endl;
    if(a[0]->rchild==NULL)
    a[0]->rchild=a[1],a[0]->rtag=0;
    for(int i=1;i<b-1;i++)
    {
        if(a[i]->lchild==NULL)
        {
            a[i]->ltag=0,a[i]->lchild=a[i-1];
        }
        if(a[i]->rchild==NULL)
        {
            a[i]->rtag=0,a[i]->rchild=a[i+1];
        }
    }
}
//��ǰ����������������ǰ���̽��,ʱ�临�ӶȲ��������ĸ߶�h,��O(h)
node *PreorderSuccessor(node *p)
{
    //���������������ҽ��*p��������,��p�ǿ�
    node *q;
    if (p->rtag==0) //*p��������Ϊ��
        return p->rchild; //������������ָ��ǰ����
    else
    {
        if(p->ltag==1)
            return p->lchild;
        else
        {
            return p->rchild;
        }
    }
}
//����ǰ������������
void TraversePreorderThrTree(node* p)
{
    if(p) //���ǿ�
    {
        do
        {
            printf("%d ",p->data); //���ʽ��
            p=PreorderSuccessor(p); //��*p��ǰ����
        }
        while(p);
    }
    cout<<endl;
}
void Traverse(node* p)
{
    if(p) //���ǿ�
    {
            printf("%d ",p->data); //���ʽ��
           if(p->lchild)
           Traverse(p->lchild);
           if(p->rchild)
           Traverse(p->rchild);
    }
}

//����������
void PostOrderThreading(node* p)
{
    node* a[1000];
    int b=0;
    stack<node*>nodeTypeStack;
    stack<int> IntStack;
    node* current;
    current=p;
    int v=0;
    if(current!=NULL)
    {
        nodeTypeStack.push(current);
        IntStack.push(1);
        current=current->lchild;
        while(!nodeTypeStack.empty())
        {
            if(current!=NULL && v==0)
            {
                nodeTypeStack.push(current);
                IntStack.push(1);
                current=current->lchild;
            }
            else
            {
                current=nodeTypeStack.top();
                nodeTypeStack.pop();
                v=IntStack.top();
                IntStack.pop();
                if(v==1)
                {
                    nodeTypeStack.push(current);
                    IntStack.push(2);
                    current=current->rchild;
                    v=0;
                }
                else
                    a[b++]=current;
            }
        }
    }
    if(a[0]->rchild==NULL)
    a[0]->rchild=a[1],a[0]->rtag=0;
    for(int i=1;i<b-1;i++)
    {
        if(a[i]->lchild==NULL)
        {
            a[i]->ltag=0,a[i]->lchild=a[i-1];
        }
        if(a[i]->rchild==NULL)
        {
            a[i]->rtag=0,a[i]->rchild=a[i+1];
        }
    }
}
//�ں���������������������̽�㣺δ���
node *PostorderSuccessor(node *p)
{
    //���������������ҽ��*p�ĺ�����,��p�ǿ�
    node *q;
    if (p->rtag==0) //*p��������Ϊ��
        return p->rchild; //������������ָ�ĺ�����
    else//��������
    {
        if(p->ltag==1)
            return p->lchild;
        else
        {
            return p->rchild;
        }
    }
}
//������������������:�����
void TraversePostorderThrTree(node* p)
{
//    if(p) //���ǿ�
//    {
//        while(p->ltag==1)
//            p=p->lchild; //�Ӹ������������½��,���������еĿ�ʼ���
//        do
//        {
//            printf("%d ",p->data); //���ʽ��
//            p=InorderSuccessor(p); //��*p��������
//
//        }
//        while(p);
//    }
    if(p!=NULL)
    {
        if(p->ltag!=0)
        TraversePostorderThrTree(p->lchild);
        if(p->rtag!=0)
        TraversePostorderThrTree(p->rchild);
        cout<<p->data<<" ";
    }
    cout<<endl;
}
int main()
{
    node *T;
    cout<<"���������뽨����������"<<endl;
    T=CreatTree();
//    cout<<"��������������"<<endl;
//    Inordering(T);
//    cout<<"������������ϣ�"<<endl;
//    cout<<"���������������������"<<endl;
//    TraverseInorderThrTree(T);
//     cout<<endl;
//    cout<<"ǰ������������"<<endl;
//    PreOrderThreading(T);
//    cout<<"ǰ����������ϣ�"<<endl;
//    TraversePreorderThrTree(T);
cout<<"��������������"<<endl;
PostOrderThreading(T);
cout<<"������������ϣ�"<<endl;
TraversePostorderThrTree(T);//�������δ���
  return 0;
}
//
