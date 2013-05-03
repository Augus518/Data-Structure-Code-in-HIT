#include<iostream>
#include <stack>
using namespace std;
void generate(int &a,int &k)
{
    stack<int> int_stack;
    while(a/k)
    {
        int_stack.push(a%k);
        a/=k;
    }
    int_stack.push(a%k);
    cout<<"ת�������Ϊ:";
    while(!int_stack.empty())
    {
        cout<<int_stack.top();
        int_stack.pop();
    }
    cout<<endl;
}
int main()
{
    int a,k;
    cout<<"����Ҫת����ʮ��������";
    while(cin>>a)
    {
        cout<<"����Ҫת���Ľ��ƣ�";
        cin>>k;
        generate(a,k);
        cout<<"����Ҫת����ʮ��������";
    }
    return 0;
}
