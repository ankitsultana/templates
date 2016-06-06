/*
 * Author:     Ankit Sultana
 * DS:         Wavelet Tree
 */
#include <stdio.h>
#include <algorithm>
#include <vector>
#define gc getchar_unlocked

const int MAXN = 1e5 + 2;

using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

bool is_active[MAXN];

struct wavelet_tree {
    struct node {
        node *left, *right;
        int low, high;
        vector<int> C;
        inline int mapLeft(int i)  { return C[i];     }
        inline int mapRight(int i) { return i - C[i]; }
        // For update operations
        vector<int> bit_left, bit_right;
        void update_bit(vector<int> &bit, int idx, int val) {
            while(idx < bit.size()) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }
        int prefix_sum(vector<int> &bit, int idx) {
            int res = 0;
            while(idx) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
        inline int activeLeft(int i)  { return prefix_sum(bit_left, i);  }
        inline int activeRight(int i) { return prefix_sum(bit_right, i); }
    };
    node* ROOT;
    wavelet_tree() : ROOT(NULL) { }
    template<typename iter>
    void build(iter a, iter b, int u, int v, node* &root) {
        int mid = u + (v - u)/2;
        root = new node();
        root->low = u, root->high = v;
        root->C.reserve(b - a + 1);
        root->C.push_back(0);
        // Update operations
        root->bit_left.resize(b - a + 1), root->bit_right.resize(b - a + 1);
        for(auto temp = a; temp != b; temp++) {
            if(*temp <= mid) {
                root->update_bit(root->bit_left, temp - a + 1, 1);
            } else {
                root->update_bit(root->bit_right, temp - a + 1, 1);
            }
        }
        // End Update crap
        for(auto temp = a; temp != b; temp++)   root->C.push_back(root->C.back() + (*temp <= mid));
        if(u == v)  return ;
        auto bound = stable_partition(a, b, [&](int &x) { return x <= mid; });
        int w;
        w = *max_element(a, bound);
        build(a, bound, u, w, root->left);
        w = *min_element(bound, b);
        build(bound, b, w, v, root->right);
    }
    // Count occurrences of q till index i of sequence S
    int Rank(node *S, int q, int i) const {
        if(S->low == S->high)  return (S->low == q) * S->activeLeft(i);
        if(S->left->high >= q) return Rank(S->left, q, S->mapLeft(i));
        return Rank(S->right, q, S->mapRight(i));
    }
    // k-th smallest element in sequence i..j
    int RangeQuantile(node *S, int i, int j, int k) {
        if(S->low == S->high)  return S->low;
        int c = S->activeLeft(j) - S->activeLeft(i-1);
        if(c >= k) {
            return RangeQuantile(S->left, 1 + S->mapLeft(i-1), S->mapLeft(j), k);
        }
        return RangeQuantile(S->right, 1 + S->mapRight(i-1), S->mapRight(j), k - c);
    }
    // Return count of values in range [x, y] in range [i, j] of sequence
    int RangeCount(node *S, int u, int v, int x, int y, int i, int j) {
        if(!S || u > y || v < x)  return 0;
        else if(u >= x && v <= y)   return S->activeLeft(j) + S->activeRight(j) - S->activeLeft(i) - S->activeRight(i);
        int one = RangeCount(S->left, u, (v + u)>>1, x, y, S->mapLeft(i), S->mapLeft(j));
        int two = RangeCount(S->right, 1 + (v + u)/2, v, x, y, S->mapRight(i), S->mapRight(j));
        return one + two;
    }
    // Toggle state of element at position i
    void toggle(node *root, int idx, int val) {
        if(root->low == root->high) {
            root->update_bit(root->bit_left, idx, val);
            return ;
        }
        if(root->C[idx] - root->C[idx-1]) {
            root->update_bit(root->bit_left, idx, val);
            toggle(root->left, root->mapLeft(idx), val);
        } else {
            root->update_bit(root->bit_right, idx, val);
            toggle(root->right, root->mapRight(idx), val);
        }
    }
};
int arr[MAXN], n, q, opt;
wavelet_tree tester;

int main() {
    int a, b, c;
    scanint(n), scanint(q);
    for(int i = 0; i < n; i++) scanint(arr[i]), is_active[i] = true;
    tester.build(arr, arr + n, *min_element(arr, arr + n),
                               *max_element(arr, arr + n),
                               tester.ROOT);
    while(q--) {
        scanint(opt);
        if(opt) {
            scanint(a);
            tester.toggle(tester.ROOT, a+1, is_active[a] ? -1 : 1);
            is_active[a] ^= true;
        } else {
            scanint(a), scanint(b), scanint(c);
            a++, b++;
            printf("%d\n", tester.Rank(tester.ROOT, c, b) - tester.Rank(tester.ROOT, c, a-1));
        }
    }
    return 0;
}
