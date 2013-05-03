#include <iostream>
#include<cstdio>
#include<string.h>
using namespace std;
#define X 105
#define INF 1000000
/*          Floyd ���ж�������·���㷨      */
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
    for (k=0; k<n; k++) /*�������ÿһ�Զ�������̾���*/
    {
        for (i=0; i<n; i++)
            for (j=0; j<n; j++)
                if (d[i][j]>(d[i][k]+d[k][j]))
                {
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=k;
                }
    }
}
int main()
{
    while(scanf("%d",&n),n)
    {
        memset(g,0,sizeof(g));
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            scanf("%d",&num);
            if(num==-1)num=INF;
            g[i][j]=g[j][i]=num;
        }
        memset(d,0,sizeof(g));
        memset(p,0,sizeof(g));
        floyd();
        num=d[0][n-1];
        int sum=2;
        for(int k=1;k<n-1;k++)
        {
            if(num==d[0][k]+d[k][n-1]);
            sum++;
        }
        printf("%d\n",sum);
    }
}
