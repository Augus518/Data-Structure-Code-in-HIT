#include <iostream>
using namespace std;
#include <cstdio>
//Prim
#define INF 99999999
const int maxn =101;
int n,ans;
int dist[maxn];
int map[maxn][maxn];
int pre[maxn];
//n���㣬dist[i]��ʾ�����������̱߳���map��¼ͼ��Ϣ��pre��¼ǰȥ�ڵ�;
void prim()
{
    ans=0;
	int i,j,k;
	int min;
	bool p[maxn];////��¼�õ��Ƿ�����v[A],��������v[B];
	//��ʼ��
	for(i=2;i<=n;i++)
	{
		p[i]=false;
		dist[i]=map[1][i];
		pre[i]=1;
	}
	dist[1]=0;
	cout<<"1"<<" ";
	p[1]=true;
	//ѭ��n-1�Σ�ÿ�μ���һ����
	for(i=1;i<=n-1;i++)
	{
		min=INF;
		k=0;
		for(j=1;j<=n;j++)
		{
			if(!p[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		}
        ans+=min;
		cout<<k<<" ";
		if(k==0)return ;//���û�е������չ����ͼ����ͨ������
		p[k]=true;//��k��v[b]�г�ȥ������v[a];
		for(j=1;j<=n;j++)
		{
			//����ÿ����k���ڵ���vb�еĽڵ�j,���µ�j��������ĵ㼰�����;
			if(!p[j]&&map[k][j]!=INF&&dist[j]>map[k][j])
			{
				dist[j]=map[k][j];
				pre[j]=k;
			}
		}
	}
}
int main()
{
    cout<<"�����붥�����:";
    cin>>n;
    cout<<"������������:"<<endl;
    int num;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        cin>>num;
        if(num==-1)num=INF;
        map[i][j]=num;
    }
    prim();
    cout<<ans;

}
