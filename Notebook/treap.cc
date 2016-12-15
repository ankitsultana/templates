/* Author: Ankit Sultana
 * DS: Treap
 * * * * * * * * * * * * */
#include <stdio.h>
#include <cassert>
#include <random>
#define MAXN 200003

using namespace std;


struct treap {
    struct node {  // val is bst ordered, prior is heap ordered
        int val, prior, size;
        node *l, *r;
    };
    typedef node* pnode;
    pnode ROOT;
    template<typename iter>
    treap(iter f, iter e) : ROOT(NULL) {
        while(f != e) {
            pnode temp = get_new_node(*f);
            _insert(ROOT, temp);
            f++;
        }
    }
    treap() : ROOT(NULL) {
    }
    int sz(pnode t) {
        return t ? t->size: 0;
    }
    void upd_sz(pnode t) {
        if(t) t->size = sz(t->l) + 1 + sz(t->r);
    }
    void split(pnode t, pnode &l, pnode &r, int key) {
        if(!t) l = r = NULL;
        else if(t->val <= key)  split(t->r, t->r, r, key), l = t; // going right
        else split(t->l, l, t->l, key), r = t;                    // going left
        upd_sz(t);
    }
    void merge(pnode &t, pnode l, pnode r) {
        if(!l || !r) t = l ? l: r;
        else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        upd_sz(t);
    }
    void _insert(pnode &t, pnode it) {
        if(!t)  t = it;
        else if(it->prior > t->prior) split(t, it->l, it->r, it->val), t = it;
        else _insert(t->val <= it->val ? t->r: t->l, it);
        upd_sz(t);
    }
    void insert(int val) { _insert(this->ROOT, get_new_node(val)); }
    void erase(pnode &t, int key) {
        if(!t)  return ;
        else if(t->val == key) { pnode temp=t; merge(t, t->l, t->r); free(temp); }
        else erase(t->val < key ? t->r: t->l, key);
        upd_sz(t);
    }
    bool search(pnode root, int x) {
        if(!root)   return false;
        if(root->val == x) return true;
        else if(root->val > x)  return search(root->l, x);
        else return search(root->r, x);
    }
    pnode kth(pnode root, int k) {
        if(!root->l and !root->r)   return root;
        else if(!root->l || !root->r) {
            if(!root->l) {
                if(k == 1)  return root;
                return kth(root->r, k-1);
            } else {
                if(root->l->size + 1 == k)  return root;
                return kth(root->l, k);
            }
        } else if(root->l->size < k) {
            k -= root->l->size + 1;
            if(k == 0)  return root;
            return kth(root->r, k);
        } else {
            return kth(root->l, k);
        }
        return NULL;
    }
    int less_than(pnode root, int x) {
        if(!root) return 0;
        else if(root->val < x) {
            return (root->l?root->l->size: 0) + 1 + less_than(root->r, x);
        } else {
            return less_than(root->l, x);
        }
        return 0;
    }
    pnode get_new_node(int val) {
        pnode temp = new node();
        temp->val = val;
        temp->size = 1;
        temp->l = temp->r = NULL;
        temp->prior = rand();
        return temp;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    return 0;
}
