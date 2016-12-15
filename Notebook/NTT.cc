template<typename T>
struct NTT {
    T pr, omega, p, omega_inv;
    NTT() { }
    NTT(T pr, T omega, T p) : pr(pr), omega(omega), p(p) { }
    void bit_reverse(vector<T> &A) const {
        int n = A.size();
        for(int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for(; j >= bit; bit >>= 1) {
                j -= bit;
            }
            j += bit;
            if(i < j) swap(A[i], A[j]);
        }
    }
    vector<T> ntt(const vector<T> &a, bool invert) const { // compute dft in Zp*
        vector<T> A = a;
        int n = A.size();
        vector<T> pows(n);
        bit_reverse(A);
        for(int len = 2; len <= n; len *= 2) { // find a len-th root of unity
            T wn = invert ? omega_inv.pow(n/len) : omega.pow(n/len), temp, w, temp_2;
            int half = len/2;
            pows[0] = 1;
            for(int i = 1; i < half; i++) pows[i] = pows[i-1] * wn;
            for(int i = 0; i < n; i += len) {
                for(int j = 0; j < half; j++) {
                    temp = A[i + j], temp_2 = pows[j] * A[i + j + half];
                    A[i + j] = temp + temp_2;
                    A[i + j + half] = temp - temp_2;
                }
            }
        }
        if(invert)
            for(int i = 0; i < n; i++)
                A[i] /= n;
        return A;
    }
    vector<T> multiply(const vector<T> &a, const vector<T> &b) const {
        int n = max(a.size(), b.size()), p = 1;
        while(p < n) p <<= 1;
        p <<= 1;
        vector<T> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        fa.resize(p), fb.resize(p);
        fa = fft(fa, false);
        fb = fft(fb, false);
        vector<T> fc(p);
        for(int i = 0; i < p; i++) {
            fc[i] = fa[i] * fb[i];
        }
        fc = fft(fa, true);
        return fc;
    }
};
