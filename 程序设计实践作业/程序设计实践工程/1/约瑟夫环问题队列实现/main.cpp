#include<iostream>
using namespace std;
#include"Queue.h"
//1.	�Ӷ���ͷ��ʼ����������1��m-1�����ȴӶ��׳��ӣ��ٴӶ�β����
//2.	��������m���˳��ӣ������ӡ�������һ���˿�ʼ���Ŵ�1��ʼ������
//3.	�����������̣�ֱ������Ϊ��Ϊֹ��

int main()
{
    int s,m,i;
	linkedQueueType<int> Q;

	cout<<"��������е���������";
	cin>>s;
	cout<<"���뱨������ֵ��";
	cin>>m;

	for (i=1;i<=s;i++)
		Q.addQueue(i);
	cout<<"���ڿ�ʼ�������У�";
	int Front;
	while(!Q.isEmptyQueue())
	{
		for(i=1;i<m;i++)
		{
		    Front=Q.front();
            Q.deleteQueue();
			Q.addQueue(Front);
		}
		Front=Q.front();
        Q.deleteQueue();
		cout<<Front<<" ";
	}
	cout<<"\n������ϣ�";
}
