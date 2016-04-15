class dynamicarray {
public:
    struct node { // prior for heap ordering and data for bst ordering
        int prior, size;
        int val, maxim, s_maxim;
        node *l, *r;
        node() {
            maxim = 0;
            s_maxim = 0;
        }
    };
    typedef node* pnode;
    pnode ROOT;
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
        temp->l = temp->r = NULL;
        reset(temp);
        return temp;
    }
    int sz(pnode t)      { return t ? t->size: 0;                   }
    void upd_sz(pnode t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }
    void reset(pnode t)  {
        if(t) t->maxim = t->val, t->s_maxim = 0;
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
        upd_sz(t);
        if(!t)  return ;
        reset(t);
        combine(t, t->l, t->r);
    }
    void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
        if(!t)  return void(l = r = NULL);
        int curr_pos = add + sz(t->l);
        if(curr_pos <= pos) split(t->r, t->r, r, pos, curr_pos+1), l = t;
        else                split(t->l, l, t->l, pos, add), r = t;
        operation(t);
    }
    void merge(pnode &t, pnode l, pnode r) {
        if(!l || !r) t = l ? l: r;
        else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        operation(t);
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
    void insert(int idx, int val) {
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
        /* cout << "===============\n";
        preorder(t);
        cout << "===============\n"; */
        int res = t->maxim + t->s_maxim;
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
};

int arr[MAXN];
int main() {
    int n, q, a, b, t;
    char opt;
    int c;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)  scanf("%d", &arr[i]);
    dynamicarray tester(arr, arr + n);
    scanf("%d", &q);
    while(q--) {
        scanf("\n%c", &opt);
        scanf("%d %d", &a, &b);
        if(opt == 'Q') {
            printf("%d\n", tester.query(tester.ROOT, a-1, b-1));
        } else {
            tester.update(tester.ROOT, a-1, a-1, b);
        }
    }
    return 0;
}
