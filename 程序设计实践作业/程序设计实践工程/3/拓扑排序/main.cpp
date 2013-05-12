//��������
#include<iostream>
using namespace std;
#include<cstring>
#include<cstdio>
#include<stdlib.h>
#define X 1001
int n=6;
int g[6][6]= {0,1,1,0,0,0,//�Խ����϶���0.
              0,0,0,1,0,0,
              0,0,0,1,1,0,
              0,0,0,0,0,1,
              0,0,0,0,0,1,
              0,0,0,0,0,0
             };

//void Topsort()
//{
//    int i,top=-1;
//    memset(count,0,sizeof(count));
//    for(int i=0; i<n; i++)
//    {
//        for(int j=0; j<n; j++)
//        {
//            if(g[i][j]!=0)
//                count[j]++;
//        }
//    }
//    for(i=0; i<n; i++)
//        if(count[i]==0)
//            top=i;
//    if(top==-1)
//    {
//        printf("0 degree stack is empty,there are cycles in graph\n");
//        return ;
//    }
//    for(i=0; i<n; i++)
//    {
//        int j=top;
//        top=count[j];
//        printf("%d",j+1);
//        if(i!=n-1)printf("->");
//        for(int k=0; k<n; k++)
//            if(g[j][k])
//            {
//                count[k]--;
//                if(count[k]==0)
//                {
//                    count[k]=top;
//                    top=k;
//                }
//            }
//    }
//}
void topsort()//����ʵ�֣�ֱ���������
{
    int count[X];
    memset(count,0,sizeof(count));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(g[i][j]!=0)
                count[j]++;
        }
    }
    int flag[X];
    int queue[X];  /*����*/
    int head=0,tail=0,v,k=0;
    memset(flag,0,sizeof(flag));
    for(int i=0; i<n; i++)  /*�Ƚ��������Ϊ0�Ķ������*/
        if(count[i]==0 && flag[i]==0)
        {
            queue[tail++]=i;
            flag[i]=1;
        }
    if(tail==0)
    {
        printf("0 degree stack is empty,there are cycles in graph\n");
        return ;
    }
    while (head<tail)             /*�����в���ʱ*/
    {
        v=queue[head++];  /*����Ԫ����*/
        printf("%d",v+1);
        k++;                  /*��������1*/
        if(k!=n)printf("-->");
        for(int i=0; i<n; i++)
        {
            if(g[v][i]&&!flag[i]&&--count[i]==0)
            {
                queue[tail++]=i;
                flag[i]=1;
            }
        }
    }
}
int main()
{
    topsort();
    return 0;
}
