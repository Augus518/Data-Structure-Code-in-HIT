#include <cstdio>
#include <iostream>
using namespace std;
int a[100010];
int n;

void SelectSort()
{
    int lowkey; //��ǰ��С�ؼ���
    int i, j,lowindex; //��ǰ��С�ؼ��ֵ��±�
    for (i = 1; i < n; i++) //��A[i��n]��ѡ����С�Ĺؼ��֣���A[i]����
    {
        lowindex = i ;
        lowkey = a[i];
        for ( j = i + 1; j <= n; j++)
            if (a[j] < lowkey) //�õ�ǰ��С�ؼ�����ÿ���ؼ��ֱȽ�
            {
                lowkey = a[j] ;
                lowindex = j ;
            }
        swap(a[i], a[lowindex]) ;
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    while (scanf("%d", &n) != EOF)
    {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        start = clock();
        SelectSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("ѡ��������ʱ %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", a[i]);
        puts("");
    }
}
