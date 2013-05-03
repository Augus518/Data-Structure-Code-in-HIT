﻿#include<iostream>
using namespace std;
typedef int ElementType;
void MaxHeap(int A[], int i, int n)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest,temp;   //存储最大的下标
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
void BuildHeap(int A[], int n)
{
    int len = n; //len对堆的大小
    for(int i = n / 2; i > 0; --i)
        MaxHeap(A,i,n);
}
ElementType Max(ElementType*S)   //根即为最大元素
{
    return S[1];
}
//DeleteMax(S)：去掉S中具有最大关键字的元素。
int DeleteMax(int A[], int n)
{
    int len = n; //len对堆的大小
    int max;
    max = A[1];
    A[1] = A[n];
    len = len - 1;
    MaxHeap(A,1,len);
    return max;
}

//Update(S, x, key)：增大元素x的关键值为key.
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
//Insert(S,x)：插入x到集合S。
void Insert(int A[], int n, int key)
{
    int len = n; //len对堆的大小
    len = len+1;
    A[len] = 0;

    Update(A, len, key);
}
int main()
{

}
