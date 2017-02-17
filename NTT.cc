template<typename T>
struct NTT {
  T mod, pr, n, pr_inv;
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
  vector<T> ntt(const vector<T> &a, bool invert) {
    vector<T> A = a;
    LL n = A.size();
    vector<T> pows(n);
    bit_reverse(A);
    for(int len = 2; len <= n; len *= 2) { // find a len-th root of unity
      T wn = invert ? pr_inv : pr;
      for(int i = len; i < this->n; i <<= 1) wn = wn * wn % mod;
      T temp, temp_2;
      int half = len/2;
      pows[0] = 1;
      for(int i = 1; i < half; i++) pows[i] = pows[i-1] * wn % mod;
      for(int i = 0; i < n; i += len) {
        for(int j = 0; j < half; j++) {
          int one = i + j, two = i + j + half;
          temp = A[one], temp_2 = pows[j] * A[two] % mod;
          (A[one] = temp + temp_2) < mod ? A[one] : (A[one] - mod);
          (A[two] = temp - temp_2) >= 0 ? A[two] : (A[two] + mod);
        }
      }
    }
    if(invert) {
      T x = modinv((LL)n, mod);
      for(int i = 0; i < n; i++)
        A[i] = A[i] * x % mod;
    }
    return A;
  }
  vector<T> multiply(const vector<T> &a, const vector<T> &b) {
    int n = max(a.size(), b.size()), p = 1;
    while(p < n) p <<= 1;
    p <<= 1;
    vector<T> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(p), fb.resize(p);
    fa = ntt(fa, false);
    fb = ntt(fb, false);
    vector<T> fc(p);
    for(int i = 0; i < p; i++) {
      fc[i] = fa[i] * fb[i] % mod;
    }
    fc = ntt(fc, true);
    return fc;
  }
  void init() {
    mod = ::mod;
    pr = 1489;
    pr_inv = modinv(pr, mod);
    n = 1 << 19;
  }
};
