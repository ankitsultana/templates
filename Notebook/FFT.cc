namespace FFT {
    // End cmplx
    typedef complex<double> base;
    const double PI = acos(-1);
    template<typename T>
    void bit_reverse(vector<T> &A) {
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
    void fft(vector<base> &A, bool invert) { // Compute DFT of vector A
        int n = A.size();
        bit_reverse(A);
        for(int len = 2; len <= n; len *= 2) {
            double ang = PI * 2.0l / len;
            base wn(cos(ang), sin(ang) * (invert ? -1 : 1)), w(1, 0), temp;
            for(int i = 0; i < n; i += len) {
                w = base(1, 0);
                for(int j = 0; j < len/2; j++) {
                    temp = A[i + j];
                    A[i + j] = temp + w * A[i + j + len/2];
                    A[i + j + len/2] = temp - w * A[i + j + len/2];
                    w *= wn;
                }
            }
        }
        if(invert)
            for(int i = 0; i < n; i++)
                A[i] /= n;
    }
    template<typename T>
    void opt_mul(vector<T> &a, vector<T> &b, vector<T> &res) {
        int n = max(a.size(), b.size()), p = 1;
        while(p < n) p <<= 1;
        p <<= 1;
        vector<base> fa(p);
        for(int i = 0; i < a.size(); i++) fa[i] += base(a[i], 0);
        for(int i = 0; i < b.size(); i++) fa[i] += base(0, b[i]);
        fft(fa, false);
        for(int i = 0; i <= p/2; i++) {
            base bp = fa[i] + fa[(p - i) % p].conj();
            base _q = fa[(p - i) % p] - fa[i].conj();
            base q(_q.imag(), _q.real());
            fa[i] = (bp * q) * 0.25;
            if(i > 0) fa[p - i] = fa[i].conj();
        }
        fft(fa, true);
        res.resize(p);
        for(int i = 0; i < p; i++) {
            res[i] = (fa[i].real() + 0.5);
        }
    }
}
