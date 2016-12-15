template<typename T>
T garner(vector<T> &a, vector<T> &p, vector<vector<T> > &r) {
    assert(a.size() == p.size());
    T M = 1;
    for(auto &elem: p) M *= elem;
    vector<T> x(a.size());
    for(int i = 0; i < x.size(); i++) {
        x[i] = a[i];
        for(int j = 0; j < i; j++) {
            x[i] = r[j][i] * (x[i] - x[j]);
            x[i] = x[i] % p[i];
            if(x[i] < 0) x[i] += p[i];
        }
    }
    T res = 0, prod = 1;
    for(int i = 0; i < x.size(); i++) {
        res = (res + x[i] * prod) % M;
        prod = (prod * p[i]) % M;
    }
    return res;
}
