#include<iostream>
#include<cstring>
#include "array_list.h"
using namespace std;
struct rate
{
    char name[30];//��������
    double current_rate;//��������
};
int main()
{
    List<rate>R;
    struct rate x;
    char na[30];
    int N;
    printf("1--����\n2--ɾ��\n3--��ѯ\n4--��ӡ\n0--�˳�\n");
    while(cin >> N)
    {
        switch(N)
        {
        case 1:
            int m;
            cin >> m;//�������
            for(int i=1; i<=m; i++)
            {
                cin >> x.name >> x.current_rate;
                R.Insert(i,x);
            }//�����ʱ��һֱ�ں������
            break;
        case 2:
            cin >> x.name;
            for(int i=1; i<=R.End()-1; i++)
                if(strcmp(R.Retrieve(i).name,x.name)==0)  R.Delete(i);
            break;
        case 3:
            cin >> x.name;
            for(int i=1; i<R.End(); i++)
            {
                if(strcmp(R.Retrieve(i).name,x.name)==0)
                    cout << R.Retrieve(i).current_rate << endl;
            }
            break;
        case 4:
            for(int i=1; i<R.End(); i++)
                cout << R.Retrieve(i).name << "---" <<  R.Retrieve(i).current_rate << endl;
                break;
        case 0:
            return 0;
        }
       printf("1--����\n2--ɾ��\n3--��ѯ\n4--��ӡ\n0--�˳�\n");
    }
    return 0;
}
