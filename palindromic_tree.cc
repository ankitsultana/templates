template<int ALPHA>
struct palin_tree {
    bool add_char(int pos) {
        int let = decode(s[pos]), curr = last;
        while(true) {
            if(pos - tree[curr].len - 1 >= 0 and s[pos - tree[curr].len - 1] == s[pos]) {
                break;
            }
            curr = tree[curr].sufflink;
        }
        if(tree[curr].nxt[let]) {
            return false;
        }
        num_nodes++;
        last = num_nodes;
        tree[num_nodes].len = tree[curr].len + 2;
        tree[curr].nxt[let] = num_nodes;
        if(tree[num_nodes].len == 1) {
            tree[num_nodes].sufflink = 2;
            tree[num_nodes].depth = 1;
            return true;
        }
        while(true) {
            curr = tree[curr].sufflink;
            if(pos - tree[curr].len - 1 >= 0 and s[pos - tree[curr].len - 1] == s[pos]) {
                tree[num_nodes].sufflink = tree[curr].nxt[let];
                break;
            }
        }
        tree[num_nodes].depth = 1 + tree[tree[num_nodes].sufflink].depth;
        return true;
    }
    void init_tree() {
        num_nodes = 2;
        tree[1].len = -1, tree[2].len = 0;
        tree[1].sufflink = 1, tree[2].sufflink = 1;
        last = 2;
        for(int i = 0; i < s.size(); i++) {
            add_char(i);
        }
    }
    palin_tree() : num_nodes(0) { }
    palin_tree(const string &s) : s(s), num_nodes(0), last(0) {
        tree = vector<node<ALPHA> > (s.size() + 1);
        init_tree();
    }
    int decode(char x) {
        if(x >= 'a' and x <= 'z') return x - 'a';
        else if(x >= 'A' and x <= 'Z') return x - 'A' + 26;
        else return x - '0' + 52;
    }
    int num_palins() { // number of distinct palindromes
        return num_nodes - 2;
    }
    int get_answer() {
        int answer = 0;
        for(int i = 3; i <= num_nodes; i++) answer += tree[i].depth;
        return answer;
    }
private:
    template<int N>
    struct node {
        int nxt[N];
        int sufflink;
        int len;
        int depth;
    };
    vector<node<ALPHA> > tree;
    ///////////////////
    int num_nodes;
    string s;
    int last;
};
