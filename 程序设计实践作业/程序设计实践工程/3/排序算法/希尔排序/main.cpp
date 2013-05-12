#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;
#define inf 1000000000
int A[100005];
int n;
void ShellSort()
{
    int i, j, d;
    for (d = n / 2; d >= 1; d = d / 2)
    {
        for (i = d + 1; i <= n; i++) //��A[i]���뵽��������������
        {
            A[0] = A[i]; //�ݴ�������¼
            j = i - d; //jָ�����������е����һ����¼
            while (j > 0 && A[0] < A[j])
            {
                A[j + d] = A[j]; //��¼����d��λ��
                j = j - d; //�Ƚ�ͬһ�����е�ǰһ����¼
            }
            A[j + d] = A[0];
        }
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    while (scanf("%d", &n) != EOF)
    {
        memset(A, 0, sizeof(A));
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        start = clock();
        ShellSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("ϣ��������ʱ %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", A[i]);
        puts("");
    }
}
