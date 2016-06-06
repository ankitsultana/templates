/*
 * Author:     Ankit Sultana
 * DS:         Wavelet Tree
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct wavelet_tree {
    struct node {
        node *left, *right;
        int low, high;
        vector<int> C;
        inline int mapLeft(int i)  { return C[i];     }
        inline int mapRight(int i) { return i - C[i]; }
    };
    node* ROOT;
    wavelet_tree() : ROOT(NULL) {
    }
    // C[root][i] should tell number of zero bits till i
    template<typename iter> // [a, b)
    void build(iter a, iter b, int u, int v, node* &root) {
        if(a == b || u == v)  return ;
        int mid = (u + v)/2;
        root = new node();
        root->C.reserve(b - a + 1);
        root->C.push_back(0);
        for(auto temp = a; temp != b; temp++) {
            root->C.push_back(root->C.back() + (*temp <= mid));
        }
        auto bound = stable_partition(a, b, [&](int &x) { return x <= mid; });
        build(a, bound, u, mid, root->left);
        build(bound, b, mid+1, v, root->right);
    }
    template<typename iter>
    void build2(iter a, iter b, int u, int v, node* &root) {
        if(u == v)  return ;
        int mid = u + (v - u)/2;
        root = new node();
        root->low = u, root->high = v;
        root->C.reserve(b - a + 1);
        root->C.push_back(0);
        for(auto temp = a; temp != b; temp++)   root->C.push_back(root->C.back() + (*temp <= mid));
        auto bound = stable_partition(a, b, [&](int &x) { return x <= mid; });
        // Find greatest value less than equal to mid, and smallest value greater than mid
        // Essentially, first is greatest value in [a, bound) and second is [bound, b)
        int w;
        if(a != bound) {
            w = *max_element(a, bound);
            build2(a, bound, u, w, root->left);
        }
        if(bound != b) {
            w = *min_element(bound, b);
            build2(bound, b, w, v, root->right);
        }
    }
    // Count occurrences of q till index i of sequence S
    int Rank(node *S, int u, int v, int q, int i) const {
        if(!S)  return i;
        int m = (u + v) >> 1;
        if(m >= q) return Rank(S->left, u, m, q, S->mapLeft(i));
        return Rank(S->right, m+1, v, q, S->mapRight(i));
    }
    // k-th smallest element in sequence i..j
    int RangeQuantile(node *S, int u, int v, int i, int j, int k) {
        if(!S)  return u;
        int c = S->mapLeft(j) - S->mapLeft(i-1);
        //cout << u << ' ' << v << endl;
        if(c >= k) {
            return RangeQuantile(S->left, u, (u + v)/2, 1 + S->mapLeft(i-1), S->mapLeft(j), k);
        }
        return RangeQuantile(S->right, 1 + (u + v)/2, v, 1 + S->mapRight(i-1), S->mapRight(j), k - c);
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
    vector<int> arr = {11, 3, 1, 1, 1, 5, 6, 5, 11, 4, 9};
    wavelet_tree tester;
    int minim = 1, maxim = 14;
    tester.build(arr.begin(), arr.end(), minim, maxim, tester.ROOT);
    cout << tester.RangeCount(tester.ROOT, minim, maxim, 1, 3, 2, 8) << endl;
    return 0;
}
