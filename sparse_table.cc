#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

template<typename T, typename Compare = std::less<T> >
struct sparse_table {
    int n;
    Compare cmp;
    vector<vector<T> > dp;
    template<typename iter>
    void build(iter a, iter b) {
        iter temp = a;
        int size = b - a, i, j, upper;
        dp.resize(size);
        int l = __log2(size);
        for(i = 0; i < size; i++) dp[i].resize(l+1);
        for(i = 0; i < size; i++, temp++) dp[i][0] = *temp;
        for(i = 1; i <= l; i++) {
            upper = size - (1<<(i-1));
            for(j = 0; j < upper; j++)
                dp[j][i] = cmp(dp[j][i-1], dp[j + (1<<(i-1))][i-1]) ? dp[j][i-1] : dp[j + (1<<(i-1))][i-1];
            for(; j < size; j++)    dp[j][i] = dp[j][i-1];
        }
    }
    T query(int i, int j) { // return min/max in range i..j (0 based)
        if(i == j)  return dp[i][0];
        int l = __log2(j - i);
        return cmp(dp[i][l], dp[j - (1<<l) + 1][l]) ? dp[i][l] : dp[j - (1<<l) + 1][l];;
    }
private:
    const int tab32[32] = {0,9,1,10,13,21,2,29,11,14,16,18,22,25,3,30,8,12,20,28,15,17,24,7,19,27,23,6,26,5,4,31};
    int __log2(int x) { return x |= x >> 1, x |= x >> 2, x |= x >> 4, x |= x >> 8, x |= x >> 16, tab32[(uint32_t)(x*0x07C4ACDD) >> 27]; }
};
