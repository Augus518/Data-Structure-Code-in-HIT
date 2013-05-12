#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[100005];
int n;

int RadixCountSort(int* npIndex, int nMax, int* a, int n)
{
    int* pnCount  = (int*)malloc(sizeof(int)* nMax);        //��������ĸ���
    for (int i = 0; i < nMax; ++i)
    {
        pnCount[i] = 0;
    }
    for (int i = 0; i < n; ++i)    //��ʼ����������
    {
        ++pnCount[npIndex[i]];
    }

    for (int i = 1; i < 10; ++i)  //ȷ�������ڸ�λ�õĸ�����
    {
        pnCount[i] += pnCount[i - 1];
    }

    int * pnSort  = (int*)malloc(sizeof(int) * n);    //�����ʱ����������

    //ע�⣺����i�Ǵ�n-1��0��˳������ģ���Ϊ��ʹ�����ȶ���
    for (int i = n - 1; i >= 0; --i)
    {
        --pnCount[npIndex[i]];
        pnSort[pnCount[npIndex[i]]] = a[i];
    }

    for (int i = 0; i < n; ++i)        //������ṹ���뵽���ص������С�
    {
        a[i] = pnSort[i];
    }
    free(pnSort);                        //�ǵ��ͷ���Դ��
    free(pnCount);
    return 1;
}

//��������
int RadixSort(int* a, int n)
{
    //�����Ż����Ŀռ�
    int* aRadix    = (int*)malloc(sizeof(int) * n);

    int nRadixBase = 1;    //��ʼ����������Ϊ1
    bool nIsOk = false; //�����������Ϊfalse
    while (!nIsOk)
    {
        nIsOk = true;
        nRadixBase *= 10;
        for (int i = 0; i < n; ++i)
        {
            aRadix[i] = a[i] % nRadixBase;
            aRadix[i] /= nRadixBase / 10;
            if (aRadix[i] > 0)
            {
                nIsOk = false;
            }
        }
        if (nIsOk) //������еĻ�����Ϊ0����Ϊ������ɣ������Ѿ��жϵ����λ�ˡ�
        {
            break;
        }
        RadixCountSort(aRadix, 10, a, n);
    }

    free(aRadix);

    return 1;
}

int main()
{
    //���Ի�������
    freopen("in.txt","r",stdin);
    clock_t start, finish;
    double duration;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    scanf("%d",&a[i]);
    start=clock();
    RadixSort(a, n);
    finish = clock();
    duration =(double)(finish - start) /CLOCKS_PER_SEC;
    printf("����������ʱ: %f seconds\n", duration );
//    for (int i = 0; i < n; ++i)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
    return 0;
}
