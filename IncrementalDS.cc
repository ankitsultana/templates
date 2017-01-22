// Warning: Untested
template<typename T>
struct IncrementalDS {
    static const int MAXN = 4e3 + 100;
    T data[MAXN], rootn;
    T leader[MAXN][2], cnt[MAXN][2], lazy[MAXN];
    IncrementalDS() : rootn(sqrt(MAXN)) { reset(); }
    void IncrementalUpdate(int l, int r, T val) { // Add val, val + 1, val + 2, ... to [l, r]
        if(l > r) return ;
        else if(l/rootn == r/rootn) {
            for(int i = l; i <= r; i++) {
                data[i] += val++;
            }
            return ;
        }
        int st_b = 1 + l/rootn, end_b = -1 + r/rootn;
        T temp = val + (st_b*rootn - l);
        for(int i = st_b; i <= end_b; i++) {
            leader[i][0] += temp, cnt[i][0]++;
            temp += rootn;
        }
        temp = val;
        for(int i = l; i < st_b*rootn; i++) data[i] += temp++;
        temp = val + (r - l);
        for(int i = r; i >= (end_b + 1)*rootn; i--) data[i] += temp--;
    }
    void DecrementalUpdate(int l, int r, T val) {
        if(l > r) return ;
        else if(l/rootn == r/rootn) {
            for(int i = l; i <= r; i++) {
                data[i] += val--;
            }
            return ;
        }
        int st_b = 1 + l/rootn, end_b = -1 + r/rootn;
        T temp = val - (st_b*rootn - l);
        for(int i = st_b; i <= end_b; i++) {
            leader[i][1] += temp, cnt[i][1]++;
            temp -= rootn;
        }
        temp = val;
        for(int i = l; i < st_b*rootn; i++) data[i] += temp--;
        temp = val - (r - l);
        for(int i = r; i >= (end_b + 1)*rootn; i--) data[i] += temp++;
    }
    void plainUpdate(int l, int r, T val) {
        if(l > r) return ;
        else if(l/rootn == r/rootn) {
            for(int i = l; i <= r; i++) {
                data[i] += val;
            }
            return ;
        }
        int st_b = 1 + l/rootn, end_b = -1 + r/rootn;
        for(int i = st_b; i <= end_b; i++) lazy[i] += val;
        for(int i = l; i < st_b*rootn; i++) data[i] += val;
        for(int i = r; i >= end_b*rootn; i--) data[i] += val;
    }
    void flattenBlock(int b_no) {
        T val[] = {leader[b_no][0], leader[b_no][1]};
        int upper = min(MAXN, (b_no + 1) * rootn);
        for(int i = b_no*rootn; i < upper; i++) {
            data[i] += val[0] + val[1] + lazy[b_no];
            val[0] += cnt[b_no][0], val[1] -= cnt[b_no][1];
        }
        cnt[b_no][0] = cnt[b_no][1] = 0;
        leader[b_no][0] = leader[b_no][1] = 0;
        lazy[b_no] = 0;
    }
    void flatten() {
        for(int i = 0; i < MAXN; i += rootn) { flattenBlock(i/rootn); }
    }
    T get(int idx) {
        flattenBlock(idx/rootn);
        return data[idx];
    }
    void reset() {
        memset(leader, 0, sizeof leader);
        memset(cnt, 0, sizeof cnt);
        memset(lazy, 0, sizeof lazy);
        memset(data, 0, sizeof data);
    }
};
