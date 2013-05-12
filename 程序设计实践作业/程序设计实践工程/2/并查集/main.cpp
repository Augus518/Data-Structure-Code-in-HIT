// ���鼯�ı�ʾ��ȼ۷���
#include<iostream>
#include<algorithm>
using namespace std;
int rank[101];
int v[101];
void make_set(int x)//��ʼ��
{
    v[x]=x;
    rank[x]=0;
}
int find_set(int x)//·��ѹ��
{
    if(v[x]!=x) v[x]=find_set(v[x]);
    return v[x];
}
void Union(int x,int y)//����rank�ϲ�������
{
    if(rank[x]>rank[y])
        v[y]=x;
    else if(rank[x]<rank[y])
        v[x]=y;
    else if(rank[x]==rank[y])
    {
        v[x]=y;
        rank[y]++;
    }
}
struct Edge//�߶���
{
    int x,y,w;
} e[1001];
bool cmp(Edge e1,Edge e2)
{
    if(e1.w<e2.w) return true;
    else return false;
}
int main()
{
    int n,m,s1,s2;
    int i,j,ans;//ansΪ��СȨֵ��
    cout<<"�����붥�����ͱ���:"<<endl;
    cin>>n>>m;//���붥�����ͱ���
    for(i=0; i<m; i++)
    {
        cout<<"������m���ߵ�����յ��Ȩֵ:"<<endl;
        cin>>e[i].x>>e[i].y>>e[i].w;//����m���ߣ�����Ȩֵ
    }
    sort(e,e+m,cmp);//����Ȩ��С��������
    for(i=1; i<=n; i++)//��ʼ��
    make_set(i);

    ans=0;//������
    for(i=0; i<m; i++)
    {
        s1=find_set(e[i].x);
        s2=find_set(e[i].y);
        if(s1!=s2)
        {
            ans+=e[i].w;
            Union(s1,s2);
        }
    }
    cout<<"��СȨΪ:"<<ans<<endl;
    return 0;
}
