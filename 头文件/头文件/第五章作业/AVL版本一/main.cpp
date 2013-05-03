#include <iostream>
using namespace std;
template<class T>
struct AVLNode
{
    T data;
    AVLNode *left,*right;
    int height;
};
template<class T>
class AVL
{
public:
    //Ĭ�Ϲ��캯��
    AVL();
    //���캯��
    AVL( T *arg, int & n);
    //��������
    ~AVL();
    //����
    void Insert(T &k);
    //�������
    void inOrder() ;
    //ǰ�����
    void preOrder() ;
    //����
    bool Search(T &k) ;
    //ɾ��
    bool Delete(T &k);
private:
    //���ڵ�
    AVLNode<T> *Root;
    //ʵ�ֲ���
    void Insert(AVLNode<T> *&p, T &k);
    //������
    void destroy(AVLNode<T> *p);
    //�������
    void inOrder( AVLNode<T> *p) ;
    //ǰ�����
    void preOrder( AVLNode<T> *p) ;
    //����
    bool Search( AVLNode<T> *p, T &k) ;
    //ɾ���ڵ�
    bool Delete(AVLNode<T> *&p, T &k);
    //����С�ڵ�
    T GetMin(AVLNode<T> *p) ;
    //����
    void leftRotate(AVLNode<T> *& p);
    //����
    void rightRotate(AVLNode<T> *& p);
    //������
    int Height( AVLNode<T> *p) ;
    //������
    void Double_LeftRotate(AVLNode<T> *& p);
    //������
    void Double_RightRotate(AVLNode<T> *& p);
    //ɾ��ʱ��ת����
    void DeleteRotate(AVLNode<T> *& p);
};

//Ĭ�Ϲ��캯��
template<class T>
AVL<T>::AVL()
{
    Root = NULL;
}
//���캯��
template<class T>
AVL<T>::AVL( T *arg, int &n)
{
    Root = NULL;
    for(int i = 0; i < n; ++i)
    {
        Insert(Root,arg[i]);
    }
}
//��������
template<class T>
AVL<T>::~AVL()
{
    destroy(Root);
}
//����
template<class T>
void AVL<T>::Insert(AVLNode<T> *&p, T &k)
{
    if(p == NULL)
    {
        p = new AVLNode<T>;
        p->data = k;
        p->left = p->right = NULL;
        p->height = 0;
        return;
    }
    else if(k < p->data)
    {
        Insert(p->left,k);
        if(Height(p->left) - Height(p->right)>=2)
        {
            if(k < p->left->data)
            {
                leftRotate(p);
            }
            else
            {
                Double_LeftRotate(p);
            }
        }
    }
    else if(k > p->data)
    {
        Insert(p->right,k);
        if(Height(p->right) - Height(p->left)>=2)
        {
            if(k < p->right->data)
            {
                Double_RightRotate(p);
            }
            else
            {
                rightRotate(p);
            }
        }
    }
    int a = Height(p->left);
    int b = Height(p->right);
    p->height = max(a,b)+1;
}
//ʵ������
template<class T>
void AVL<T>::destroy(AVLNode<T> *p)
{
    if(p == NULL) return;
    destroy(p->left);
    destroy(p->right);
    delete p;
}

//����
template<class T>
void AVL<T>::Insert( T &k)
{
    Insert(Root,k);
}
//����
template<class T>
bool AVL<T>::Search( T &k)
{
    return Search(Root,k);
}

//ʵ�ֲ���
template<class T>
bool AVL<T>::Search( AVLNode<T> *p, T &k)
{
    //�߽�����
    if(p == NULL) return false;
    if(p->data == k)
    {
        return true;
    }
    else if(k < p->data)
    {
        return Search(p->left,k);
    }
    else
    {
        return Search(p->right,k);
    }
}

//�������
template<class T>
void AVL<T>::inOrder()
{
    inOrder(Root);
}
//ʵ���������
template<class T>
void AVL<T>::inOrder( AVLNode<T>  *p)
{
    if(p!=NULL)
    {
        inOrder(p->left);
        cout<<p->data<<" ";
        inOrder(p->right);
    }
}
//ǰ�����
template<class T>
void AVL<T>::preOrder()
{
    preOrder(Root);
}
//ʵ��ǰ�����
template<class T>
void AVL<T>::preOrder( AVLNode<T> *p)
{
    if(p!=NULL)
    {
        cout<<p->data<<" ";
        preOrder(p->left);
        preOrder(p->right);
    }
}
//ɾ���ڵ�
template<class T>
bool AVL<T>::Delete( T &k)
{
    if(Root!=NULL)  return Delete(Root,k);
    return false;
}

//�ݹ�ʵ��ɾ���ڵ�
template<class T>
bool AVL<T>::Delete(AVLNode<T> * &p, T &k)
{
    if(p == NULL) return false;
    if(p->data > k) Delete(p->left,k);
    else if(p->data < k) Delete(p->right,k);
    else if(p->left != NULL && p->right != NULL)
    {
        p->data = GetMin(p->right);
        Delete(p->right,p->data);
    }
    else
    {
        AVLNode<T> *old = p;
        p = (p->left != NULL)?p->left:p->right;
        delete old;
        return true;
    }
    //���½ڵ�߶�
    int a = Height(p->left);
    int b = Height(p->right);
    p->height=max(a,b)+1;
    //if need to be rotated
    DeleteRotate(p);
    return true;
}

//������pΪ������С�ڵ�
template<class T>
T AVL<T>::GetMin(AVLNode<T> *p)
{
    if(p == NULL) return 0;
    AVLNode<T> *newp = p;
    while(newp->left != NULL)
    {
        newp = newp->left;
    }
    return newp->data;
}
//������
template<class T>
int AVL<T>::Height( AVLNode<T> *p)
{
    return p == NULL ? -1:p->height;
}
//����
template<class T>
void AVL<T>::leftRotate(AVLNode<T> *&p)
{
    AVLNode<T> *leftchild = p->left;
    p->left = leftchild->right;
    leftchild->right = p;
    //the order is important!
    //the next two statement can not be switched!
    int a,b;
    a = Height(p->left);
    b = Height(p->right);
    p->height = max(a,b)+1;
    a = Height(leftchild->left);
    b = Height(leftchild->right);
    leftchild->height = max(a,b)+1;
    //the final statement is also important,it makes the p point
    //to the right node
    p = leftchild;
}

//����
template<class T>
void AVL<T>::rightRotate(AVLNode<T> *& p)
{
    AVLNode<T> *rightchild = p->right;
    p->right = rightchild->left;
    rightchild->left = p;
    //the order is important!
    //the next two statement can not be switched!
    int a,b;
    a = Height(p->left);
    b = Height(p->right);
    p->height = max(a,b)+1;
    a = Height(rightchild->left);
    b = Height(rightchild->right);
    rightchild->height = max(a,b)+1;
    //the final statement is also important,it makes the p point
    //to the right node
    p = rightchild;
}

//������
template<class T>
void AVL<T>::Double_LeftRotate(AVLNode<T> *& p)
{
    rightRotate(p->left);
    leftRotate(p);
}
//������
template<class T>
void AVL<T>::Double_RightRotate(AVLNode<T> *& p)
{
    leftRotate(p->right);
    rightRotate(p);
}
//ɾ����ת����
template<class T>
void AVL<T>::DeleteRotate(AVLNode<T> *& p)
{
    if(Height(p->left)-Height(p->right)>=2)
    {
        if(p->left->left == NULL)
        {
            Double_LeftRotate(p);
        }
        else
        {
            leftRotate(p);
        }
    }
    else if (Height(p->right)-Height(p->left)>=2)
    {
        if(p->right->right==NULL)
        {
            Double_RightRotate(p);
        }
        else
        {
            rightRotate(p);
        }
    }
}
int main()
{
    return 0;
}
