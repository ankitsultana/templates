#include <bits/stdc++.h>
using namespace std;

template<int ALPHA>
struct aho {
    // Vars
    mutable function<int(char)> decode;
    struct node {
        int been, end;
        node *sufflink;
        node *nxt[ALPHA];
        node(int a = 0, int b = 0, node *c = NULL) : been(a), end(b), sufflink(c) {
            for(int i = 0; i < ALPHA; i++) nxt[i] = NULL;
        }
    };
    node* ROOT;
    // End Vars
    aho() : ROOT(NULL) { }
    vector<string> keys;
    void add_string(string &x) {
        keys.push_back(x);
        __insert(ROOT, x);
    }
    void build() {
        queue<node*> q;
        ROOT->sufflink = ROOT;
        q.push(ROOT);
        while(q.empty() == false) {
            node* f = q.front();
            q.pop();
            if(f == ROOT) {
                for(int i = 0; i < ALPHA; i++) {
                    if(f->nxt[i] != NULL) {
                        q.push(f->nxt[i]);
                    }
                }
            } else {
                for(int i = 0; i < ALPHA; i++) {
                    if(f->nxt[i] != NULL) {
                        node* temp = f->sufflink;
                        while(temp->nxt[i] == NULL and temp != ROOT) { // ERROR!!
                            temp = temp->sufflink;
                        }
                        f->nxt[i]->sufflink = (temp->nxt[i] == NULL ? ROOT : temp->nxt[i]);
                        if(temp->nxt[i])
                            f->nxt[i]->end += temp->nxt[i]->end;
                        q.push(f->nxt[i]);
                    }
                }
            }
        }
    }
    void __insert(node* &root, string &s, int d = 0) {
        if(!root) {
            root = new node(0, 0, ROOT);
        }
        root->been++;
        if(d == s.size()) {
            root->end++;
            return ;
        }
        __insert(root->nxt[decode(s[d])], s, d + 1);
    }
    int __query(node *root, string &p, int d = 0) {
        if(!root) { assert(false); }
        if(p.size() == d) return root->end;
        int x = decode(p[d]), res = root->end;
        if(root->nxt[x] == NULL) {
            while(root != ROOT and root->nxt[x] == NULL) {
                root = root->sufflink;
            }
            if(root->nxt[x] == NULL)
                return res + __query(ROOT, p, d + 1);
        }
        return res + __query(root->nxt[x], p, d + 1);
    }
    int query(string &p) { // Find count of occurences of words in AC in p
        if(ROOT == NULL) return 0;
        return __query(this->ROOT, p);
    }
    void clear() {
        __clear(ROOT);
        keys.clear();
        ROOT = NULL;
    }
    void __clear(node *root) {
        if(!root) {
            return ;
        }
        for(int i = 0; i < ALPHA; i++) {
            if(root->nxt[i])
                __clear(root->nxt[i]);
        }
        delete root;
    }
};
aho<26> pos[19], neg[19];

void add(aho<26> AC[], string &x) {
    int k = 0;
    vector<string*> to_add;
    to_add.push_back(&x);
    for(; k < 19; k++) {
        if(AC[k].keys.empty()) {
            break;
        }
        for(auto &elem: AC[k].keys) {
            to_add.push_back(&elem);
        }
    }
    for(auto &ptr: to_add) {
        AC[k].add_string(*ptr);
    }
    AC[k].build();
    for(int i = 0; i < k; i++) AC[i].clear();
}

int query(string &p) {
    int res = 0;
    for(int i = 0; i < 19; i++) {
        res += pos[i].query(p) - neg[i].query(p);
    }
    return res;
}

char buf[int(3e5)];

void solve() {
    for(int i = 0; i < 19; i++) {
        pos[i].decode = [=](char x) { return x - 'a'; };
        neg[i].decode = [=](char x) { return x - 'a'; };
    }
    int q, type;
    string temp;
    scanf("%d", &q);
    while(q--) {
        scanf("%d %s", &type, buf);
        temp = string(buf);
        if(type == 1) {
            add(pos, temp);
        } else if(type == 2) {
            add(neg, temp);
        } else {
            printf("%d\n", query(temp));
        }
        fflush(stdout);
    }
}

int main() {
    solve();
    return 0;
}
