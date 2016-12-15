class dynamicarray {
public:
    struct node { // prior for heap ordering and data for bst ordering
        int prior, size;
        int val, maxim;
        bool lazy;
        node *l, *r;
        node() : maxim(0), lazy(false) {
        }
    };
    typedef node* pnode;
    pnode ROOT;
    dynamicarray() { }
    template<typename iter>
    dynamicarray(iter st, iter e) : ROOT(NULL) {
        iter temp;
        for(temp = st; temp != e; temp++) {
            pnode x = get_new_node(*temp);
            merge(ROOT, ROOT, x);
        }
    }
    pnode get_new_node(int val) {
        pnode temp = new node();
        temp->val = val;
        temp->prior = rand(), temp->size = 1;
        temp->lazy = false;
        temp->l = temp->r = NULL;
        reset(temp);
        return temp;
    }
    int sz(pnode t)      { return t ? t->size: 0;                   }
    void upd_sz(pnode t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }
    void reset(pnode t)  { // What if t is leaf
        if(t) t->maxim = t->val;
    }
    void propagate(pnode t) {
        if(!t || !t->lazy)  return ;
        // Perform some opreation like < swap(t->l, t->r) >
        if(t->l)    t->l->lazy ^= true;
        if(t->r)    t->r->lazy ^= true;
        t->lazy = false;
    }
    void combine(pnode t, pnode l, pnode r) {
        if(l and r) {
        } else if(!l and r) {
        } else if(l and !r) {
        } else {
            reset(t);
        }
    }
    void operation(pnode t) {
        if(!t)  return ;
        upd_sz(t);
        reset(t);
        combine(t, t->l, t->r);
    }
    void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
        if(!t)  return void(l = r = NULL);
        propagate(t);
        int curr_pos = add + sz(t->l);
        if(curr_pos <= pos) split(t->r, t->r, r, pos, curr_pos+1), l = t;
        else                split(t->l, l, t->l, pos, add), r = t;
        operation(t);
    }
    void merge(pnode &t, pnode l, pnode r) {
        propagate(l), propagate(r);
        if(!l || !r) t = l ? l: r;
        else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        operation(t);
    }
    void erase(int idx) {
        pnode temp, l, r;
        split(ROOT, l, r, idx);
        if(idx == 0) {
            ROOT = r;
            delete l;
            return;
        }
        split(l, l, temp, idx-1);
        merge(ROOT, l, r);
        delete temp;
    }
    void insert(int idx, int val) { // Insert val before idx (zero based)
        pnode temp = get_new_node(val);
        if(idx == 0) {
            merge(ROOT, temp, ROOT);
        } else {
            pnode l, r;
            split(ROOT, l, r, idx-1);
            merge(l, l, temp);
            merge(ROOT, l, r);
        }
    }
    int query(pnode t, int l, int r) {
        pnode L, mid, R;
        split(t, L, mid, l - 1);
        split(mid, t, R, r - l);
        int res = t->maxim;
        merge(mid, L, t);
        merge(t, mid, R);
        return res;
    }
    void update(pnode t, int l, int r, int val) {
        pnode L, mid, R;
        split(t, L, mid, l - 1);
        split(mid, t, R, r - l);
        t->val = val;
        reset(t);
        merge(mid, L, t);
        merge(t, mid, R);
    }
    void preorder(pnode t) {
        if(!t) return ;
        preorder(t->l);
        preorder(t->r);
    }
    void reversal(int a, int b) {
        pnode l, r, mid;
        l = r = mid = NULL;
        split(ROOT, l, r, b);
        if(a == 0) { // l contains the shit
            l->lazy ^= true;
            merge(ROOT, l, r);
        } else {
            split(l, l, mid, a-1);
            mid->lazy ^= true;
            merge(l, l, mid);
            merge(ROOT, l, r);
        }
    }
};
