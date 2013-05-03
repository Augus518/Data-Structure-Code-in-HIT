#include<iostream>
#include<stdio.h>
#define MAX 100
using namespace std;

//�����ڽӾ���
int edge[5][5]=
{
    {0,1,1,0,0},
    {0,0,0,1,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};
int n=5;//������
bool visit[MAX];//�Ƿ����
//�ǵݹ������������
bool DFS_judge(int vi,int vj)
{
    memset(visit,false,sizeof(visit));
    int top = 0,v;
    int Stack[100];
    visit[vi] = true ;
    Stack[top] = vi ;
    while ( top != -1)
    {
        v = Stack[top];
        int i;
        int flag=0;
        for (i = 0 ; i <n ; i++)
        {
            if (edge[v][i] == 1 &&!visit[i])
            {
                if(i==vj)
                return true;
                visit[i]=true;
                Stack[++top] =i;
                flag=1;
                break ;
            }
        }
        if(i==n)top--;
    }
    return false;
}
int main()
{
    int vi,vj;
    cout<<"������VI��VJ��"<<endl;
    while(cin>>vi>>vj)
    {
        if(DFS_judge(vi,vj))
            cout<<vi<<"�ɴ�"<<vj<<endl;
        else
            cout<<vi<<"���ɴ�"<<vj<<endl;
        cout<<"������VI��VJ��"<<endl;
    }
    return 0;
}
