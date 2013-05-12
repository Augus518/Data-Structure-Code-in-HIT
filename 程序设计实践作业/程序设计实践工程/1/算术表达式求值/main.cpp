//����������׺�ͺ�׺���ʽ�������Լ�ʵ�ֵĶ�ջ��ʵ�ִ���׺����׺��ת����
//���Դ���С���������ܴ�����
#include<iostream>
#include<cstdio>
#include"mystack.h"//�Լ�ʵ�ֵĶ�ջ��д��ͷ�ļ���������ջ�ĸ��ֲ�����
//����ADTģ����ʵ�֡�
using namespace std;
//����������ֵ
double Compute(double t1,double t2,char c)
{
    switch(c)
    {
    case'+':
        return t1+t2;
    case'-':
        return t1-t2;
    case'*':
        return t1*t2;
    case'/':
        return t1/t2;
    default:
        return 0;
    }
}
//�ж���ջ������������ȼ�
int priority_in(char c)
{
    switch(c)
    {
    case'+':
        return 1;
    case'-':
        return 1;
    case'*':
        return 2;
    case'/':
        return 2;
    case'(':
        return 0;
    case'#':
        return -1;
    default:
        exit(1);
    }
}
//�ж���ջ������������ȼ�
int priority_out(char c)
{
    switch(c)
    {
    case'+':
        return 1;
    case'-':
        return 1;
    case'*':
        return 2;
    case'/':
        return 2;
    case'(':
        return 3;
    default:
        exit(1);
    }
}
//��׺���ʽת��׺���ʽ����
void postfix(char *e1,char *e2)
{
    stackType<char> OPER;//char���͵Ĳ�����ջ
    char C,X;
    int i=0;//����e1
    int j=0;//����e2
    C=e1[i++];
    while(C!=0)
    {
        if((C>='0'&&  C<='9')||C=='.')  //����������ַ�,ֱ�Ӽ��뵽�������

        {
            e2[j++]=C;
            if((e1[i]<'0'||e1[i]>'9')&&e1[i]!='.')//��һ�����������ַ�
                e2[j++]=' ';    //�Կո�ָ�
        }
        else //�ǲ�����
        {
            if(C==')')
            {
                //������ջ��ֱ������'('
                while(!OPER.isEmptyStack()&&OPER.top()!='(')
                {
                    X=OPER.top();
                    OPER.pop();
                    cout<<"The  operator  in  the  stack  is:";OPER.display();
e2[j++]=X;
                    e2[j++]=' ';
                }
                if(!OPER.isEmptyStack())
                {
                X=OPER.top();
                OPER.pop();
                cout<<"The operator in the stack is:";OPER.display();
                }
            }
            else
            {
                //�Ƚ�ջ����������ַ�C�����ȼ�

while(!OPER.isEmptyStack()&&priority_in(OPER.top())>=priority_out(C))
                {
                    //���ջ�еĲ����������ȼ����ڻ�����µĲ�����
                    //��ջ�в�������ջ�����뵽�������e2��
                    X=OPER.top();
                    OPER.pop();
                    cout<<"The operator in the stack is:";OPER.display();
                    e2[j++]=X;
                    e2[j++]=' ';
                }
                OPER.push(C);//�����ջ
                cout<<"The operator in the stack is:";OPER.display();
            }
        }
        C=e1[i++];//���ʽ����һ���ַ�
    }
    while(!OPER.isEmptyStack())
    {
        //����ջ��ʣ����������
        X=OPER.top();
        OPER.pop();
        cout<<"The operator in the stack is:";OPER.display();
        e2[j++]=X;
        e2[j++]=' ';
    }
    e2[j++]='#';//�á�#�������Ƿ����ļ�β
}
//�Ժ�׺���ʽ���������
double Evaluate(char *e2)
{
    stackType<double> Double_stack;
    char C;
    int j=0;
    int n,m=0,length=0;
    C=e2[j++];
    while(C!='#')//��#'Ϊ������־
    {
        if(C>'0'&&C<='9')//��������
        {
            n=C-'0';//�����ַ���������ת��
            while(e2[j]!=' '&&e2[j]!='.') //�����λ��
                n=n*10+(e2[j++]-'0');
            if(e2[j]=='.')
            {
                j++;
                m=e2[j++]-'0';
                length++;
                while(e2[j]!=' ') //�����λ��
                {
                    m=m*10+(e2[j++]-'0');
                    length++;
                }
            }
            double a=(double)n;
            if(length!=0)
            a+=double(m)/(10.0*length);
            Double_stack.push(a);//����ѹջ
            length=0;m=0;
            if(!Double_stack.isEmptyStack())
            {cout<<"The stack is:";Double_stack.display();}
        }
        else//���������
        {
            double T2=Double_stack.top();
            Double_stack.pop();
            cout<<"The stack is:";Double_stack.display();
            double T1=Double_stack.top();
            Double_stack.pop();
            cout<<"The stack is:";Double_stack.display();
            double T=Compute(T1,T2,C);//��T1��T2������ֵ����
            Double_stack.push(T);//��ֵ���������ջ������һ��ʹ��
            cout<<"The stack is:";Double_stack.display();
        }
        C=e2[j++];
        if(C==' ')//�����ո�
            C=e2[j++];
    }
    double temp=Double_stack.top();
    Double_stack.pop();
    cout<<"The stack is:";Double_stack.display();
    return temp;
}
int main()
{
    char ex1[100];//�����׺���ʽ
    char ex2[100];//��ź�׺���ʽ
    cout<<"Please input the infix string:"<<endl;
    while(cin>>ex1)//ѭ������
    {
        postfix(ex1,ex2);//������׺����׺��ת��
        int i=0;

        cout<<"The postfix is:";
        while(ex2[i]!='#')
            cout<<ex2[i++];
        cout<<endl;

        double result=Evaluate(ex2);
        printf("The  result is:%lf\n",result);
        cout<<"Please input the infix string:"<<endl;
    }
    return 0;
}

