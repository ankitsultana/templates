#include <iostream>
using namespace std;

struct suffix_array {
    const static int __MAXN = 1e5 + 1;
    int lcp[__MAXN], cnt[256], cls[2][__MAXN], pos[2][__MAXN], st[__MAXN], rnk[__MAXN], size;
    int arr[__MAXN];
    string s;
    suffix_array() : size(0) { }
    void clear() {
        for(int i = 0; i < size; i++)
            lcp[i] = cls[0][i] = cls[1][i] = pos[0][i] = pos[1][i] = st[i] = rnk[i] = 0;
        size = 0;
        s.clear();
    }
    void build(string &s) {
        if(size == 0)   clear();
        this->s = s;
        this->size = s.size();
        int i, j;
        fill(cnt, cnt + sizeof(cnt), 0);
        int n = s.size();
        for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
        for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
        for (i = 0; i < n; i++) pos[0][--cnt[cls[0][i]]] = i;
        int cur = 0;
        for (i = 0; (1 << i) < n; i++) {
            int clen = (1 << i);
            for (j = 0; j < n; j++) {
                if (j > 0 && pos[cur][j - 1] + clen < n && cls[cur][pos[cur][j]] == cls[cur][pos[cur][j - 1]] &&
                    cls[cur][pos[cur][j] + clen / 2] == cls[cur][pos[cur][j - 1] + clen / 2]
                   )
                    cls[1 - cur][pos[cur][j]] = cls[1 - cur][pos[cur][j - 1]];
                else cls[1 - cur][pos[cur][j]] = j;
            }
            for (j = 0; j < n; j++) { st[j] = j; pos[1 - cur][j] = pos[cur][j]; }
            for (j = 0; j < n; j++) {
                int cele = pos[cur][j] - clen;
                if (cele >= 0) pos[1 - cur][st[cls[1 - cur][cele]]++] = cele;
            }
            cur = 1 - cur;
        }
        for (i = 0; i < n; i++) { pos[0][i] = pos[cur][i]; rnk[pos[cur][i]] = i;}
        int x = 0;
        for (i = 0; i < n; i++) {
            if (rnk[i] < n - 1) {
                for (j = pos[cur][rnk[i] + 1]; __max(i, j) + x < n && s[i + x] == s[j + x]; x++);
                lcp[rnk[i] + 1] = x; if (x > 0) x--;
            }
        }
        for(int i = 0; i < n; i++) arr[i] = pos[1][i];
    }
    template<typename iter>
    int cmp(iter a1, iter a2, iter b1, iter b2) {
        int a_size = a2 - a1, b_size = b2 - b1;
        int minim = __min(a_size, b_size);
        for(int i = 0; i < minim; i++, a1++, b1++) {
            if(*a1 < *b1) {
                return -1;
            } else if(*a1 > *b1) {
                return 1;
            }
        }
        if(a_size == b_size)
            return 0;
        return a_size < b_size ? -1 : 1;
    }
    int search(string &x) { // return index where x is found
        if(x.size() > this->s.size())   return -1;
        int low = 0, high = size-1, mid, c;
        while(low < high) {
            mid = (low + high) >> 1;
            c = cmp(this->s.begin() + arr[mid], this->s.begin() + min(this->s.size(), arr[mid] + x.size()),
                    x.begin(), x.end());
            if(c < 0) { // s < x
                low = mid + 1;
            } else if(c > 0) { // s > x
                high = mid;
            } else {
                return arr[mid];
            }
        }
        c = cmp(this->s.begin() + arr[low], this->s.begin() + min(this->s.size(), arr[low] + x.size()),
                x.begin(), x.end());
        return c == 0 ? low : -1;
    }
private:
    inline int __max(int a, int b) { return a - ((a-b) & (a-b)>>31); }
    inline int __min(int a, int b) { return b + ((a-b) & (a-b)>>31); }
};

int main() {
    return 0;
}
