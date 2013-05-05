#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

template <typename T>
class AVL
{
private:
    class node
    {
    public:
        node *l,*r;
        int h,size;
        T dat;
        node() : l(0) ,r(0), h(1),size(0) {};
        node(T tdat) : dat(tdat),l(0),r(0), h(1),size(1) {};
        int geth()
        {
            if(!this) return 0;
            else return h;
        }
        int getsize()
        {
            if(!this) return 0;
            else return size;
        }
        void update()
        {
            if(this)
            {
                h = max(l->geth() ,r->geth()) + 1;
                size = l->getsize() + r->getsize() + 1;
            }
        }
    }*root;
    void Lrotate(node * &p)
    {
        node * t = p->r->l;
        p->r->l = p;
        p= p->r;
        p->l->r =t;
        p->l->update();
        p->update();
    }
    void Rrotate(node * &p)
    {
        node * t = p->l->r;
        p->l->r = p;
        p= p->l;
        p->r->l = t;
        p->r->update();
        p->update();
    }
    void maintain(node * &p)
    {
        int lh ,rh;
        if(p->l->geth() > p->r->geth() + 1) // To balance the left tree
        {
            lh = p->l->l->geth();
            rh = p->l->r->geth();
            if(lh >= rh)
                Rrotate(p);
            else
            {
                Lrotate(p->l);
                Rrotate(p);
            }
        }
        if(p->r->geth() > p->l->geth() + 1 ) // To balance the right tree
        {
            lh = p->r->l->geth();
            rh = p->r->r->geth();
            if(rh >= lh)
                Lrotate(p);
            else
            {
                Rrotate(p->r);
                Lrotate(p);
            }
        }
    }
    void insert(node  * & p, T dat)
    {
        if(!p)
        {
            p = new node(dat);
            return;
        }
        if(dat <= p->dat)
            insert(p->l,dat);
        else
            insert(p->r,dat);
        maintain(p);
        p->update();
    }
    void erase(node * & p, T dat)
    {
        if(!p) return;
        if(p ->dat == dat)
        {
            if(p->l && p->r)
            {
                node * t = p->r;
                while(t->l)
                    t = t->l;
                p->dat = t->dat;
                erase(p->r,t->dat);
                maintain(p);
            }
            else if(p->l)
            {
                p->dat = p->l->dat;
                p->l = 0;
            }
            else if(p->r)
            {
                p->dat = p->r->dat;
                p->r = 0;
            }
            else p = 0;
            p->update();
            return;
        }
        else if(dat < p->dat)
            erase(p->l,dat);
        else
            erase(p->r,dat);
        maintain(p);
        p->update();
    }
    T findk(node * p, int k)
    {
        if(k == p->l->getsize() + 1)
            return p->dat;
        else if(k <= p->l->getsize())
            return findk(p->l,k);
        else if(k > p->getsize() - p->r-> getsize())
            return findk(p->r, k- p->getsize() + p->r->getsize());
    }
public:
    AVL() : root(0) {};
    void insert(T dat)
    {
        insert(root, dat);
    }
    void erase(T dat)
    {
        erase(root, dat);
    }
    T findk(int k)
    {
        if( k <= 0) return -1;
        return findk(root, k);
    }
    void clear(node * p)
    {
        if(!p)
            return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
    bool empty()
    {
        return (root->getsize() == 0);
    }
    int size()
    {
        return root->getsize();
    }
    node* getroot()
    {
        return root;
    }
    /* void print()
     {
         queue <node *> Q;
         Q.push(root);
         while(!Q.empty())
         {
             node * t = Q.front();
             Q.pop();
             cout << (t->dat) << endl;
             if(t->l) Q.push(t->l);
             if(t->r) Q.push(t->r);
         }
     }*/
};

int main()
{
    int n,mindat,dat,delta,cnt;
    char cmd;
    while(scanf("%d %d",&n,&mindat) == 2)
    {
        AVL <int> avl;
        cnt = 0 ,delta = 0;
        while(n--)
        {
            scanf(" %c %d",&cmd,&dat);
            if(cmd == 'I')
            {
                if(dat < mindat)
                    continue;
                avl.insert(dat - delta);
            }
            else if(cmd == 'F')
            {
                int tmp = avl.findk(avl.size() - dat + 1);
                printf("%d\n", tmp == -1 ? -1 : tmp + delta);
            }
            else if(cmd == 'A')
                delta += dat;
            else if(cmd == 'S')
            {
                delta -= dat;
                while(!avl.empty())
                {
                    int tmp = avl.findk(1);
                    if(tmp + delta < mindat)
                    {
                        avl.erase(tmp);
                        cnt++;
                    }
                    else break;
                }
            }
        }
        printf("%d\n",cnt);
        avl.clear(avl.getroot());
    }
    return 0;
}
