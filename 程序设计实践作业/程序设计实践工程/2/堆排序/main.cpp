// ����洢�ṹ�������㷨��ʵ��

#include<iostream>
using namespace std;
typedef int ElementType;
#define maxn 10000
void MaxHeap(int A[], int i, int n)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest,temp;   //�洢�����±�
    if(left <= n && A[left] > A[i])
        largest = left;
    else
        largest = i;
    if(right <= n && A[right] > A[largest])
        largest = right;
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        MaxHeap(A,largest,n);
    }
}
void BuildHeap(int *A, int n)
{
    int len = n; //len�ԶѵĴ�С
    for(int i = n / 2; i > 0; --i)
        MaxHeap(A,i,n);
}
ElementType Max(ElementType*A)   //����Ϊ���Ԫ��
{
    return A[1];
}
//DeleteMax(S)��ȥ��S�о������ؼ��ֵ�Ԫ�ء�
int DeleteMax(int *A, int n)
{
    int len = n; //len�ԶѵĴ�С
    int max;
    max = A[1];
    A[1] = A[n];
    len = len - 1;
    MaxHeap(A,1,len);
    return max;
}

//Update(a, i, key)���ı��±�i�Ĺؼ�ֵΪkey.
void Update(int A[], int i, int key)
{
    A[i] = key;
    int parent = i/2;
    int temp;
    while(i>1 && A[parent]<A[i])
    {
        temp = A[i];
        A[i] = A[parent];
        A[parent] = temp;
        i = i/2;
    }
}
//Insert(S,x)������x������S��
void Insert(int A[], int n, int key)
{
    int len = n; //len�ԶѵĴ�С
    len = len+1;
    A[len] = 0;

    Update(A, len, key);
}
int main()
{
    int n,a[maxn];
    cout<<"input the number of elements:";
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    BuildHeap(a,n);
    for(int i=n;i>=1;i--)
        cout<<DeleteMax(a,i)<<" ";
    cout<<endl;
}
//����������
//8
//44 22 1 7 33 99 45 31
