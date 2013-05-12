// �����������ת���㷨
#include<iostream>
#include<stdio.h>
#include<stack>
#define MAX 100
using namespace std;
int n,e;//�������ͱ���
bool visit[MAX];//�Ƿ����
struct ArcNode//�ڽӵ㶨��
{
    int adjvex;
    ArcNode *next;
};
struct VNode//�����㶨��
{
    int v;
    ArcNode *first;
};
VNode adj[MAX];//�ڽӱ�

struct node
{
    int data;
    node *lchild,*rchild;
};//�������Ľ������
void Create()//��������ͼ
{
    int i;
    cout<<"�����Ŵ�1��"<<n<<"."<<endl;
    for(i=1; i<=n; i++)
    {
        adj[i].v=i;
        adj[i].first=NULL;
    }
    for(i=1; i<=e; i++)
    {
        int a,b;
        //cout<<"�������"<<i<<"����:"<<endl;
        cin>>a>>b;
        if(adj[a].first==NULL)
        {
            ArcNode *p=new ArcNode;
            p->adjvex=b;
            p->next=NULL;
            adj[a].first=p;
        }
        else
        {
            ArcNode *p=adj[a].first;
            while(p->next!=NULL)
            {
                p=p->next;
            }
            ArcNode *q=new ArcNode;
            q->adjvex=b;
            q->next=NULL;
            p->next=q;
        }
    }
}
node* search(node* T,int v)
{
    stack<node* >nodeTypeStack;
    node* current;
    current=T;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            nodeTypeStack.push(current);
            current=current->lchild;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            if(current->data==v)return current;
            current=current->rchild;
        }
    }
}
void preorder(node *T)
{
    if(T)
    {
        cout<<T->data<<" ";
        preorder(T->lchild);
        preorder(T->rchild);
    }
}
node* ToBtree()//�ڽӱ�ת��Ϊ������
{
    node* T=NULL;
    for(int i=1;i<=n;i++)
    {
        if(!T)
        {
            T=new node;
            T->lchild=NULL;
            T->rchild=NULL;
            T->data=adj[i].v;
            if(adj[i].first)
            {
                node *now=new node;
                now->lchild=NULL;
                now->rchild=NULL;
                now->data=adj[i].first->adjvex;
                T->lchild=now;
                ArcNode *p=adj[i].first->next;
                while(p)
                {
                    node *current=new node;
                    current->lchild=NULL;
                    current->rchild=NULL;
                    current->data=p->adjvex;
                    now->rchild=current;
                    now=now->rchild;
                    p=p->next;
                }
            }
            continue;
        }
        else
        {
            if(adj[i].first)
            {
                //preorder(T);
                node *t=search(T,i);
                node *now=new node;
                now->lchild=NULL;
                now->rchild=NULL;
                now->data=adj[i].first->adjvex;
                t->lchild=now;
                ArcNode *p=adj[i].first->next;
                while(p)
                {
                    node *current=new node;
                    current->lchild=NULL;
                    current->rchild=NULL;
                    current->data=p->adjvex;
                    now->rchild=current;
                    now=now->rchild;
                    p=p->next;
                }
            }
        }
    }
    return T;
}
void BFS(int v)//�����������
{
    int Queue[MAX];
    int front=1;
    int tail=1;
    Queue[front++]=v;
    cout<<v<<" ";
    visit[v]=true;
    while(tail<front)
    {
        ArcNode *p=adj[Queue[tail]].first;
        while(p!=NULL)
        {
            if(!visit[p->adjvex])
            {
                cout<<p->adjvex<<" ";
                Queue[front++]=p->adjvex;
                visit[p->adjvex]=true;
                p=p->next;
            }
            else
            p=p->next;
        }
        tail++;
    }
}

int main()
{
    printf("�����ĸ����ͱߵĸ�����\n");
    scanf("%d%d",&n,&e);
    Create();//�����ڽӱ��ʾ����

    memset(visit,false,sizeof(visit));
    BFS(1);
    cout<<endl<<"BFS has ended."<<endl;

    node* T=NULL;
    T=ToBtree();
    preorder(T);
}
/*
13 12
1 2
1 3
1 4
1 5
2 6
2 7
2 8
3 9
3 10
5 11
5 12
5 13
*/

