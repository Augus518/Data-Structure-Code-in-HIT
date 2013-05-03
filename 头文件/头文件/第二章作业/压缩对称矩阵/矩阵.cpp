#include <iostream>
#include <cstdio>
using namespace std;
void compute(const int *A,const int *B,const int &n)
{
    cout<<"A��B����ĳ˻�Ϊ��"<<endl;
    int M1,M2,M3,M4,sum;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            sum=0;
            for(int k=1;k<=n;k++)
            {
                M1=max(i,k);
                M2=min(i,k);
                M3=max(j,k);
                M4=min(j,k);
                sum+=A[M1*(M1-1)/2+M2-1]*B[M3*(M3-1)/2+M4-1];
            }
            cout<<sum<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    int i,j,key;
    int n,len;
    int *A,*B;
    cout<<"����Գƾ����ά����";
    cin>>n;
    len=(1+n)*n/2;
    A=new int[len];
    B=new int[len];
    cout<<"����A�������ݣ���ʽ��ÿ��һ�����ݣ��ֱ�Ϊ�У��У�ֵ���磺2 3 4 ��ʾ��2�е�3�е�ֵ��3��";
    cout<<"����0 0 0�������"<<endl;
    cin>>i>>j>>key;
    while(i||j||key)
    {
        if(i>=j)
            A[i*(i-1)/2+j-1]=key;  //�����������ڵ����У��洢����Ӧ��һά����
        else
            A[j*(j-1)/2+i-1]=key;
        cin>>i>>j>>key;
    }
    cout<<"����B�������ݣ���ʽ��ÿ��һ�����ݣ��ֱ�Ϊ�У��У�ֵ���磺2 3 4 ��ʾ��2�е�3�е�ֵ��3��";
    cout<<"����0 0 0�������"<<endl;
    cin>>i>>j>>key;
    while(i||j||key)
    {
        if(i>=j)
            B[i*(i-1)/2+j-1]=key;  //�����������ڵ����У��洢����Ӧ��һά����
        else
            B[j*(j-1)/2+i-1]=key;
        cin>>i>>j>>key;
    }
    compute(A,B,n);
    return 0;
}
/*
1 2 3
2 1 1
3 1 1

1 1 1
1 2 2
1 3 3
2 2 1
2 3 1
3 3 1
0 0 0
*/
