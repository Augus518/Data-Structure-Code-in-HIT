#include<iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 12500
typedef struct
{
    int i,j;//�÷���Ԫ�����±�����±�
    int e;

} Triple;
typedef struct
{
    Triple data[MAXSIZE+1];//����Ԫ��Ԫ���data[0]δ��
    int mu,nu,tu;//����������������ͷ���Ԫ����

} TSMatrix;
void initTS(TSMatrix &X)
{
    cout<<"���������������������ͷ���Ԫ������"<<endl;
    cin>>X.mu>>X.nu>>X.tu;
    cout<<"���������Ԫ�أ�"<<endl;
    for(int p=1; p<=X.tu; p++)
    {
        cout<<"������� "<<p<<"������Ԫ�ص�����������������ֵ:";
        cin>>X.data[p].i;
        cin>>X.data[p].j;
        cin>>X.data[p].e;
        cout<<endl;
    }
}
void print(TSMatrix X)
{
    cout<<"���ڵľ���Ϊ��"<<endl;
    for(int k=1; k<=X.tu; k++)
    {
        cout<<X.data[k].i<<" "<<X.data[k].j<<" "<<X.data[k].e<<endl;
    }
}
void TransposeSM(TSMatrix X,TSMatrix &T)//һ��ת���㷨
{
    cout<<"���ڶԾ������ת�ã�"<<endl;
    T.mu=X.nu;
    T.nu=X.mu;
    T.tu=X.tu;
    if(T.tu)
    {
        int q=1;
        for(int col=1; col<=X.nu; ++col) //ע�ⲻ���˵���
            for(int p=1; p<=X.tu; ++p)
                if(X.data[p].j==col)
                {
                    T.data[q].i=X.data[p].j;
                    T.data[q].j=X.data[p].i;
                    T.data[q].e=X.data[p].e;
                    ++q;
                }
    }
}
//���ô��㷨ʱ����������������num[],cpot[],
//num[col]��ʾ����M�е�col���з���Ԫ�ĸ�����
//cpot[col]ָʾM�е�col�еĵ�һ������Ԫ��b.data�е�ǡ��λ�á�
//����ָM��ÿһ�еĵ�һ������Ԫ��B�б�ʾΪ�ڼ�������Ԫ��
void FastTransposeSMatrix(TSMatrix M,TSMatrix &T)   //����ת���㷨
{
    int p,q,t,col,*num,*cpot;
    num=(int*)malloc((M.nu+1)*sizeof(int));
    cpot=(int*)malloc((M.nu+1)*sizeof(int));
    T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
    if(T.tu)
    {
        for(col=1;col<=M.nu;++col)
            num[col]=0;
        for(t=1;t<=M.tu;++t)
            ++num[M.data[t].j];
        cpot[1]=1;
        for(col=2;col<=M.nu;++col)
            cpot[col]=cpot[col-1]+num[col-1];
                for(p=1;p<=M.tu;++p)
                {
                    col=M.data[p].j;
                    q=cpot[col];
                    T.data[q].i=M.data[p].j;
                    T.data[q].j=M.data[p].i;
                    T.data[q].e=M.data[p].e;
                    ++cpot[col];
                }
    }
    free(num);free(cpot);
}

int main()
{
    TSMatrix X,T;
    initTS(X);
    print(X);
    TransposeSM(X,T);
    cout<<"����X��ת�þ���Ϊ��"<<endl;
    print(T);
    return 0;
}
