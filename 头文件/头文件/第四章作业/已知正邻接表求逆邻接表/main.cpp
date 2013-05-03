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
VNode adj[MAX];//���ڽӱ�
VNode adv[MAX];//���ڽӱ�

void Create()//��������ͼ�����ڽӱ�
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
//1 2
//2 3
//3 1

void Change()//���ڽӱ�ת���ڽӱ�
{
    cout<<"fdfdf"<<endl;
    int i;
    for(i=1; i<=n; i++)
    {
        adv[i].v=i;
        adv[i].first=NULL;
    }
    for(i=1; i<=n; i++)
    {
        ArcNode *now=adj[i].first;
        while(now!=NULL)
        {
            if(adv[now->adjvex].first==NULL)
            {
                ArcNode *p=new ArcNode;
                p->adjvex=i;
                p->next=NULL;
                adv[now->adjvex].first=p;
            }
            else
            {
                ArcNode *p=adv[now->adjvex].first;
                while(p->next!=NULL)
                {
                    p=p->next;
                }
                ArcNode *q=new ArcNode;
                q->adjvex=i;
                q->next=NULL;
                p->next=q;
            }
            cout<<i<<" "<<now->adjvex<<endl;
            now=now->next;
        }
    }
}
void DFS(int v)//�ݹ������������
{
    printf("%d ",v);
    visit[v]=1;
    ArcNode *p=adv[v].first;
    while(p!=NULL)
    {
        if(!visit[p->adjvex])
            DFS(p->adjvex);
        p=p->next;
    }
}
int main()
{
    int v;
    printf("�����ĸ����ͱߵĸ�����\n");
    scanf("%d%d",&n,&e);
    Create();
    Change();//���ڽӱ�ת���ڽӱ�
    printf("���ĸ��㿪ʼ������\n");
    while(scanf("%d",&v)!=EOF&&v)
    {
        memset(visit,false,sizeof(visit));
        DFS(v);
        cout<<endl<<"DFS has ended."<<endl;
        printf("���ĸ��㿪ʼ������\n");
    }
    return 0;
}
