#include<iostream>
#include<stdio.h>
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
        cout<<"�������"<<i<<"����:"<<endl;
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
void DFS(int v)//�ݹ������������
{
    printf("%d ",v);
    visit[v]=1;
    ArcNode *p=adj[v].first;
    while(p!=NULL)
    {
        if(!visit[p->adjvex])
            DFS(p->adjvex);
        p=p->next;
    }
}
void None_DFS(int v)//�ǵݹ������������
{
    int Queue[MAX];
    int front=1;
    Queue[front]=v;
    cout<<v<<" ";
    visit[v]=true;
    while(front>0)
    {
        ArcNode *p=adj[Queue[front]].first;
        if(p==NULL){front--;continue;}
        int flag=0;//�ж��Ƿ��ܼ���������
        while(p!=NULL)
        {
            if(!visit[p->adjvex])
            {
                cout<<p->adjvex<<" ";
                Queue[++front]=p->adjvex;
                visit[p->adjvex]=true;
                flag=1;
                break;
            }
            else
            p=p->next;
        }
        if(flag==0)front--;
    }
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
    int v;
    printf("�����ĸ����ͱߵĸ�����\n");
    scanf("%d%d",&n,&e);
    Create();
    printf("���ĸ��㿪ʼ������\n");
    while(scanf("%d",&v)!=EOF&&v)
    {
        memset(visit,false,sizeof(visit));
        BFS(v);
        cout<<endl<<"BFS has ended."<<endl;
        memset(visit,false,sizeof(visit));
        DFS(v);
        cout<<endl<<"DFS has ended."<<endl;
        memset(visit,false,sizeof(visit));
        None_DFS(v);
        cout<<endl<<"�ǵݹ�DFS has ended."<<endl;
        printf("���ĸ��㿪ʼ������\n");
    }
    return 0;
}
