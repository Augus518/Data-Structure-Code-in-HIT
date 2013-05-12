#include <iostream>
#include <cstdio>
using namespace std;
//һ��ʵ��
#define INF 99999999
const int maxn=10001;
int n,ans;
int dist[maxn];
int map[maxn][maxn];
int pre[maxn];
//n���㣬dist[i]��¼i��s����̾��룬map��¼ͼ��Ϣ��pre��¼ǰ�����;
void dijkstra(int s)
{
	int i,j,k;
	int min;
	bool p[maxn];//��¼�õ��Ƿ�����v[A],��������v[B];
	//��ʼ��
	for(i=1;i<=n;i++)
	{
		p[i]=false;
		if(i!=s)
		{
			dist[i]=map[s][i];
			pre[i]=s;
		}
	}
	dist[s]=0;
	p[s]=true;
	//ѭ��n-1����s�����������̾���
	for(i=1;i<=n-1;i++)
	{
		min=INF;
		k=0;
		for(j=1;j<=n;j++)//��v[B]�еĵ�ȡһs���������С�ĵ�k;
		{
			if(!p[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		}
		if(k==0)return ;//���û�е������չ����ʣ��ĵ㲻�ɴ����
		p[k]=true;//��k���뵽v[A]��
		for(j=1;j<=n;j++)
		{
			if(!p[j]&&map[k][j]!=INF&&dist[j]>dist[k]+map[k][j])
			{
				//����ÿ����k���ڵ���v[B]�еĵ�j;����s��j����̾���;
				dist[j]=dist[k]+map[k][j];
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
    dijkstra(1);
    for(int i=1;i<=n;i++)
    cout<<dist[i]<<" ";

}

























































