#include <algorithm>
#include <cassert>
using namespace std;
template<typename T, typename Compare = std::less<T> >
struct splay_tree {
    struct node {
        T val;
        node *l, *r, *p;
        node() : l(NULL), r(NULL), p(NULL) { }
        node(T x, node* l, node* r, node* p) : val(x), l(l), r(r), p(p) { }
        ~node() {
        }
    };
    splay_tree() {
        cmp = Compare(), sz = 0;
    }
    void erase(T val) {
        __erase(val, this->ROOT), sz--;
    }
    void erase(node *r) {
        __erase(r->val, r), sz--;
    }
    void insert(T val)  {
        sz++;
        splay(__insert(val, this->ROOT, NULL));
    }
    node* search(T val) {
        node* temp = __search(val, this->ROOT);
        splay(temp);
        return temp;
    }
    node* begin() {
        node* x = this->ROOT;
        while(x and x->l) { x = x->l; }
        splay(x);
        return x;
    }
    node* end() {
        node*x = this->ROOT;
        while(x and x->r) { x = x->r; }
        splay(x);
        return x;
    }
    inline size_t size() { return sz; }
    inline bool empty()  { return sz == 0; }
private:
    size_t sz;
    Compare cmp;
    node *ROOT;
    node* __insert(const T &val, node* &r, node *p) {
        if(r == NULL) {
            return (r = new node(val, NULL, NULL, p));
        } else if(cmp(r->val, val)) {
            return __insert(val, r->r, r);
        } else {
            return __insert(val, r->l, r);
        }
    }
    node* __search(const T &val, node *r) {
        if(r == NULL || r->val == val) return NULL;
        else if(cmp(r->val, val)) return __search(val, r->r);
        return __search(val, r->l);
    }
    void __erase(const T &val, node *r) {
        if(r == NULL) return void(assert(false));
        else if(r->val == val) {
            if(!r->l and !r->r) {
                if(r->p) r->p->l == r ? r->p->l = NULL : r->p->r = NULL;
                else this->ROOT = NULL;
            } else if(r->l and !r->r) {
                if(r->p) {
                    r->p->l == r ? r->p->l = r->l : r->p->r = r->l;
                    r->l->p = r->p;
                } else {
                    r->l->p = NULL;
                    this->ROOT = r->l;
                }
            } else if(!r->l and r->r) {
                if(r->p) {
                    r->p->l == r ? r->p->l = r->r : r->p->r = r->r;
                    r->r->p = r->p;
                } else {
                    r->r->p = NULL;
                    this->ROOT = r->r;
                }
            } else {
                node* minim = __get_min(r->r);
                if(minim->r) {
                    if(minim->p->l == minim) {
                        minim->p->l = minim->r;
                    } else {
                        minim->p->r = minim->r;
                    }
                    minim->r->p = minim->p;
                }
                minim->r = r->r, minim->l = r->l;
                minim->p = r->p;
                if(!minim->p) this->ROOT = minim;
            }
            delete r;
        } else if(cmp(r->val, val)) {
            __erase(val, r->r);
        } else {
            __erase(val, r->l);
        }
    }
    node* __get_min(node *r) {
        while(r->l) r = r->l;
        return r;
    }
    void rotate_right(node *b) {
        node *a = b->l;
        b->l = a->r;
        a->r = b;
        if(b->l) b->l->p = b;
        a->p = b->p;
        b->p = a;
        if(a->p == NULL) {
            ROOT = a;
        } else if(a->p->l == b) {
            a->p->l = a;
        } else {
            a->p->r = a;
        }
    }
    void rotate_left(node *x) {
        node *y = x->r;
        x->r = y->l;
        if(x->r != NULL) x->r->p = x;
        y->p = x->p;
        if(y->p == NULL) {
            ROOT = y;
        } else if(x->p->l == x) {
            x->p->l = y;
        } else {
            x->p->r = y;
        }
        y->l = x;
        x->p = y;
    }
    void zig(node *r) {
        if(r->p->l == r) rotate_right(r->p);
        else             rotate_left(r->p);
    }
    void zig_zag(node *r) {
        if(r->p->r == r) {
            rotate_left(r->p);
            rotate_right(r->p);
        } else {
            rotate_right(r->p);
            rotate_left(r->p);
        }
    }
    void zig_zig(node *r) {
        if(r->p->l == r) {
            rotate_right(r->p->p);
            rotate_right(r->p);
        } else {
            rotate_left(r->p->p);
            rotate_left(r->p);
        }
    }
    void splay(node *r)   {
        if(r == NULL) return ;
        while(r->p) {
            if(r->p->p == NULL) {
                zig(r);
            } else if((r->p->r == r and r->p->p->r == r->p) or (r->p->l == r and r->p->p->l == r->p)) {
                zig_zig(r);
            } else {
                zig_zag(r);
            }
        }
    }
};
