#include <iostream>
#include<cstdio>
#include<string.h>
using namespace std;
#define X 105
#define INF 1000000
int d[X][X];     /* ��������*/
int p[X][X];    /* ·������*/
int g[X][X];
int n,num,sum;
void floyd()
{
    int i,j,k;
    for (i=0; i<n; i++)       /*��ʼ��*/
        for (j=0; j<n; j++)
        {
            d[i][j]=g[i][j];
            if (i!=j && d[i][j]<INF) p[i][j]=i;
            else p[i][j]=-1;
        }
            for (i=0; i<n; i++)
            for (j=0; j<n; j++) /*�������ÿһ�Զ�������̾���*/
            for (k=0; k<n; k++)
                if (d[i][j]>(g[i][k]+g[k][j]))
                {
                    d[i][j]=g[i][k]+g[k][j];
                    p[i][j]=k;
                }
            for (i=0; i<n; i++)
            for (j=0; j<n; j++) /*�������ÿһ�Զ�������̾���*/
            for (k=0; k<n; k++)
                if (d[i][j]>(d[i][k]+d[k][j]))
                {
                    d[i][j]=d[i][k]+d[k][j];
                }
}
int main()
{
    cout<<"���붥�������";
    while(scanf("%d",&n)!=EOF,n)
    {
        cout<<"����������:"<<endl;
        memset(g,0,sizeof(g));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                cin>>num;
                if(num==-1)num=INF;
                g[i][j]=num;
            }
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        floyd();
        for (int i=0; i<n; i++)       /*��ʼ��*/
        {
            for (int j=0; j<n; j++)
            {
                cout<<d[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}
