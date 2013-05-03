#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define X 20
int fac[X];
int permutation[X];
int n;
int CalcFac(int n)//����n!   0!=1;
{
    if (n == 0)
    return fac[0] = 1;
    else return fac[n] = CalcFac(n - 1) * n;
}
int Cantor()//���ظ������ǵڼ��󣬴�С������
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int t = 0;
        for (int j = i + 1; j <= n; ++j)
            if (permutation[j] < permutation[i])
                t++;
        ans += t * fac[n-i];
    }
    return ans + 1;
}
int main()
{
    ios::sync_with_stdio(false);//�ر�cin��������
    while(cin >> n)
    {
        CalcFac(n);
        for (int i = 1; i <= n; ++i)
            cin >> permutation[i];
        cout << Cantor() << endl;
    }
    return 0;
}

