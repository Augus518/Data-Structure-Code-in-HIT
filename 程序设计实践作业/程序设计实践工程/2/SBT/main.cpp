// BST�洢�ṹ������㷨��ʵ��
// ��̬/ ��̬��������/ ���棩����
// �����㷨��ʵ�֣�ǰ�����򡢺���
// �����㷨�ĵݹ�ͷǵݹ��㷨��ʵ�֣�
// ��������㷨��ʵ��

#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
template <class elemType>
struct nodeType
{
    elemType info;
    nodeType<elemType> *llink;
    nodeType<elemType> *rlink;
};

template <class elemType>
class bSearchTreeType
{
public:
    //Ĭ�Ϲ��캯��
    bSearchTreeType();
    //���ƹ��캯��
    bSearchTreeType(const bSearchTreeType<elemType>& otherTree);
    //��������
    ~bSearchTreeType();
    //���ظ�ֵ�����
    const bSearchTreeType<elemType>& operator=(const bSearchTreeType<elemType>&);
    bool isEmpty();
    //����һ��Ԫ���Ƿ�����
    bool search(const elemType& searchItem);
    //����һ��Ԫ��
    void insert(const elemType& insertItem);
    //ɾ��һ��Ԫ��
    void deleteNode(const elemType& deleteItem);
    //��������������������
    void bfs();
    //�������
    void inorderTraversal();
    //ǰ�����
    void preorderTraversal();
    //�������
    void postorderTraversal();
    //�ǵݹ��������
    void nonRecursiveInTraversal();
    //�ǵݹ�ǰ�����
    void nonRecursivePreTraversal();
    //�ǵݹ�������
    void nonRecursivePostTraversal();
    //�������ĸ߶�
    int treeHeight();
    //���ؽڵ����
    int treeNodeCount();
    //����Ҷ������
    int treeLeavesCount();
    //������
    void destroyTree();
private:
    //���ڵ㶨��
    nodeType<elemType>* root;
    //ʵ�ָ���һ����
    void copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot);
    //ʵ��ɾ��
    void deleteFromTree(nodeType<elemType>* &p);
    //����
    void destroy(nodeType<elemType>* &p);
    //�������
    void BFS(nodeType<elemType>* p);
    //ʵ���������
    void inorder(nodeType<elemType>* p);
    //ʵ��ǰ�����
    void preorder(nodeType<elemType>* p);
    //ʵ�ֺ������
    void postorder(nodeType<elemType>* p);
    //������
    int height(nodeType<elemType>* p);
    //��ڵ���
    int nodeCount(nodeType<elemType>* p);
    //��Ҷ�ڵ���
    void leavesCount(nodeType<elemType>* p,int &Count);
};
//Ĭ�Ϲ��캯��
template <class elemType>
bSearchTreeType<elemType>::bSearchTreeType()
{
    root=NULL;
}
//�п�
template <class elemType>
bool bSearchTreeType<elemType>::isEmpty()
{
    return (root==NULL);
}
//���Һ���
template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType&searchItem)
{
    nodeType<elemType>* current;
    bool found=false;
    if(root==NULL)
    {
        cerr<<"Cannot search an empty tree"<<endl;
    }
    else
    {
        current=root;
        while(current!=NULL&&!found)
        {
            if(current->info==searchItem)
                found=true;
            else if (current->info>searchItem)
            {
                current=current->llink;
            }
            else
            {
                current=current->rlink;
            }
        }
        return found;
    }

}
//���뺯��
template<class elemType>
void bSearchTreeType<elemType>::insert(const elemType&insertItem)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    nodeType<elemType>* newNode;
    newNode=new nodeType<elemType>;
    assert(newNode!=NULL);
    newNode->info=insertItem;
    newNode->llink=NULL;
    newNode->rlink=NULL;
    if(root==NULL)
        root=newNode;
    else
    {
        current=root;
        while(current!=NULL)
        {
            trailCurrent=current;
            if(current->info==insertItem)
            {
                cerr<<"The insertItem is already in the tree"<<endl;
                return ;
            }
            else
            {
                if(current->info>insertItem)
                    current=current->llink;
                else
                    current=current->rlink;
            }
        }
        if(trailCurrent->info>insertItem)
            trailCurrent->llink=newNode;
        else
            trailCurrent->rlink=newNode;
    }
}
//ɾ���ڵ�
template<class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType>* &p)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    nodeType<elemType>* temp;
    if(p==NULL)
        cerr<<"Error!The node to be deleted is NULL!"<<endl;
    else if(p->llink==NULL&&p->rlink==NULL)
    {
        temp=p;
        p=NULL;
        delete temp;
    }
    else if(p->llink==NULL)
    {
        temp=p;
        p=temp->rlink;
        delete temp;
    }
    else if(p->rlink==NULL)
    {
        temp=p;
        p=temp->llink;
        delete temp;
    }
    else
    {
        current=p->llink;
        trailCurrent=NULL;
        while(current->rlink!=NULL)
        {
            trailCurrent=current;
            current=current->rlink;
        }
        p->info=current->info;
        if(trailCurrent==NULL)
            p->llink=current->llink;
        else
            trailCurrent->rlink=current->llink;
        delete current;
    }
}
//ɾ���ض�Ԫ��
template<class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    bool found= false;
    if(root==NULL)
    {
        cerr<<"Cannot delete from the empty tree!"<<endl;
    }
    else
    {
        current=root;
        trailCurrent=root;
        while(current!=NULL&&!found)
        {
            if(current->info==deleteItem)
            {
                found=true;
                cout<<current->info<<endl;
            }
            else
            {
                trailCurrent=current;
                if(current->info > deleteItem)
                {
                    current=current->llink;
                }
                else
                    current=current->rlink;
            }
        }
        if(current=NULL)
            cerr<<"The deleteItem is not in the vector!"<<endl;
        else
        {
            if(found)
            {
                if(current==root)
                {
                    deleteFromTree(root);
                }
                else
                {
                    if(trailCurrent->info>deleteItem)
                        deleteFromTree(trailCurrent->llink);
                    else
                        deleteFromTree(trailCurrent->rlink);
                }
            }
        }
    }
}
//�������
template <class elemType>
void bSearchTreeType<elemType>::inorderTraversal()
{
    inorder(root);
    cout<<endl;
}
//ǰ�����
template <class elemType>
void bSearchTreeType<elemType>::preorderTraversal()
{
    preorder(root);
    cout<<endl;
}
//�������
template <class elemType>
void bSearchTreeType<elemType>::postorderTraversal()
{
    postorder(root);
    cout<<endl;
}
//������
template <class elemType>
int bSearchTreeType<elemType>::treeHeight()
{
    return height(root);
}
//��ڵ���
template <class elemType>
int bSearchTreeType<elemType>::treeNodeCount()
{
    return nodeCount(root);
}
template <class elemType>

//��Ҷ�ӽڵ���
int bSearchTreeType<elemType>::treeLeavesCount()
{
    int Count=0;
    leavesCount(root,Count);
    return Count;
}
//��α���
template <class elemType>
void bSearchTreeType<elemType>::bfs()
{
    BFS(root);
}

//��α����ľ���ʵ��
template <class elemType>
void bSearchTreeType<elemType>::BFS(nodeType<elemType>* p)
{
    nodeType<elemType>* a[300];
    int head=0,tail=0;
    if(p)
    {
        a[head++]=p;
        while(tail!=head)
        {
            if(a[tail]->llink!=NULL)
            {
                a[head++]=a[tail]->llink;
            }
            if(a[tail]->rlink!=NULL)
            {
                a[head++]=a[tail]->rlink;
            }
            cout<<a[tail++]->info<<" ";
        }
        cout<<endl;
    }
}
//�������ʵ��
template <class elemType>
void bSearchTreeType<elemType>::inorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {
        inorder(p->llink);
        cout<<p->info<<" ";
        inorder(p->rlink);
    }
}
//ǰ�����ʵ��
template <class elemType>
void bSearchTreeType<elemType>::preorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {
        cout<<p->info<<" ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}
//�������ʵ��
template <class elemType>
void bSearchTreeType<elemType>::postorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {

        postorder(p->llink);
        postorder(p->rlink);
        cout<<p->info<<" ";
    }
}
//ʵ��������
template<class elemType>
int bSearchTreeType<elemType>::height(nodeType<elemType>* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return 1+max(height(p->llink),height(p->rlink));
    }
}
//ʵ�ַǵݹ��������
template <class elemType>
void bSearchTreeType<elemType>::nonRecursiveInTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    nodeType<elemType>* current;
    current=root;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            nodeTypeStack.push(current);
            current=current->llink;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            cout<<current->info<<" ";
            current=current->rlink;
        }
    }
    cout<<endl;
}
//ʵ�ַǵݹ�ǰ�����
template <class elemType>
void bSearchTreeType<elemType>::nonRecursivePreTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    nodeType<elemType>* current;
    current=root;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            cout<<current->info<<" ";
            nodeTypeStack.push(current);
            current=current->llink;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            current=current->rlink;
        }
    }
    cout<<endl;
}
//ʵ�ַǵݹ�������
template <class elemType>
void bSearchTreeType<elemType>::nonRecursivePostTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    stack<int> IntStack;
    nodeType<elemType>* current;
    current=root;
    int v=0;
    if(current!=NULL)
    {
        nodeTypeStack.push(current);
        IntStack.push(1);
        current=current->llink;
        while(!nodeTypeStack.empty())
        {
            if(current!=NULL && v==0)
            {
                nodeTypeStack.push(current);
                IntStack.push(1);
                current=current->llink;
            }
            else
            {
                current=nodeTypeStack.top();
                nodeTypeStack.pop();
                v=IntStack.top();
                IntStack.pop();
                if(v==1)
                {
                    nodeTypeStack.push(current);
                    IntStack.push(2);
                    current=current->rlink;
                    v=0;
                }
                else
                    cout<<current->info<<" ";
            }
        }
    }
}
//ʵ����ڵ���
template<class elemType>
int bSearchTreeType<elemType>::nodeCount(nodeType<elemType>* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return 1+nodeCount(p->llink)+nodeCount(p->rlink);
    }
}
//ʵ����Ҷ�ӽڵ���
template<class elemType>
void bSearchTreeType<elemType>::leavesCount(nodeType<elemType>* p,int &Count)
{
    if(p)
    {
        if(p->llink==NULL&&p->rlink==NULL)
            Count++;
        leavesCount(p->llink,Count);
        leavesCount(p->rlink,Count);
    }
}
//����һ����
template<class elemType>
void bSearchTreeType<elemType>::copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot)
{
    if(otherTreeRoot==NULL)
        copiedTreeRoot=NULL;
    else
    {
        copiedTreeRoot=new nodeType<elemType>;
        copiedTreeRoot->info=otherTreeRoot->info;
        copyTree(copiedTreeRoot->llink,otherTreeRoot->llink);
        copyTree(copiedTreeRoot->rlink,otherTreeRoot->rlink);
    }
}
//ʵ��������
template<class elemType>
void bSearchTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
    if(p!=NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p=NULL;
    }
}
//������
template<class elemType>
void bSearchTreeType<elemType>::destroyTree()
{
    destroy(root);
}
//���ƹ��캯��
template<class elemType>
bSearchTreeType<elemType>::bSearchTreeType(const bSearchTreeType<elemType>& otherTree)
{
    if(otherTree.root==NULL)
    {
        root=NULL;
    }
    else
    {
        copyTree(root,otherTree.root);
    }
}
//��������
template<class elemType>
bSearchTreeType<elemType>::~bSearchTreeType()
{
    destroy(root);
}
//���ظ�ֵ�����
template<class elemType>
const bSearchTreeType<elemType>& bSearchTreeType<elemType>::operator=(const bSearchTreeType<elemType>& otherTree)
{
    if(this!=&otherTree)
    {
        if(root!=NULL)
        {
            destroy(root);
        }
        if(otherTree.root==NULL)
        {
            root=NULL;
        }
        else
        {
            copyTree(root,otherTree.root);
        }
    }
    return *this;
}

int main()
{
    bSearchTreeType<int> A;
    A.insert(10);
    A.insert(6);
    A.insert(14);
    A.insert(3);
    A.insert(8);
    A.insert(12);
    A.insert(16);
    cout<<"������Ϊ��"<<endl;
    cout<<"               10"<<endl;
    cout<<"            6     14"<<endl;
    cout<<"          3  8  12  16"<<endl<<endl;
    bSearchTreeType<int> B(A);
    bSearchTreeType<int> C=A;
    cout<<"����Ϊ��";
    cout<<C.treeHeight()<<endl;
    cout<<"�ڵ���Ϊ:";
    cout<<C.treeNodeCount()<<endl;
    cout<<"Ҷ�ӽڵ���Ϊ:";
    cout<<C.treeLeavesCount()<<endl;
    cout<<"ǰ�������";
    C.preorderTraversal();
    cout<<"���������";
    C.inorderTraversal();
    cout<<"���������";
    C.postorderTraversal();
    cout<<"�ǵݹ���������";
    C.nonRecursivePreTraversal();
    cout<<"��α�����";
    C.bfs();
    return 0;
}
