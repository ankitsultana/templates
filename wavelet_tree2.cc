/*
 * Author:     Ankit Sultana
 * DS:         Wavelet Tree
 */
#include <iostream>
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

struct wavelet_tree {
    struct node {
        node *left, *right;
        int low, high;
        vector<int> C;
        inline int mapLeft(int i)  { return C[i];     }
        inline int mapRight(int i) { return i - C[i]; }
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
        if(S->low == S->high)  return cout << S->low << endl, (S->low == q) * i;
        if(S->left->high >= q) return Rank(S->left, q, S->mapLeft(i));
        return Rank(S->right, q, S->mapRight(i));
    }
    // k-th smallest element in sequence i..j
    int RangeQuantile(node *S, int i, int j, int k) {
        if(S->low == S->high)  return S->low;
        int c = S->mapLeft(j) - S->mapLeft(i-1);
        if(c >= k) {
            return RangeQuantile(S->left, 1 + S->mapLeft(i-1), S->mapLeft(j), k);
        }
        return RangeQuantile(S->right, 1 + S->mapRight(i-1), S->mapRight(j), k - c);
    }
    // Return count of values in range [x, y] in range [i, j] of sequence
    int RangeCount(node *S, int u, int v, int x, int y, int i, int j) {
        if(!S || u > y || v < x)  return 0;
        else if(u >= x && v <= y)   return j - i + 1;
        int one = RangeCount(S->left, u, (v + u)>>1, x, y, S->mapLeft(i), S->mapLeft(j));
        int two = RangeCount(S->right, 1 + (v + u)/2, v, x, y, S->mapRight(i), S->mapRight(j));
        return one + two;
    }
};


int main() {
    vector<int> arr = {1, 2, 3, 4, 1, 1000, 3};
    wavelet_tree tester;
    tester.build(arr.begin(), arr.end(), *min_element(arr.begin(), arr.end()),
                                         *max_element(arr.begin(), arr.end()),
                                         tester.ROOT);
    cout << tester.Rank(tester.ROOT, 5, 7) << '\n';
    return 0;
}
