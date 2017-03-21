// TODO : Untested
template<typename T>
vector<T> gaussian(const vector<T> &arr, int BITS) {
  vector<T> res = arr;
  int num_rows = res.size(), num_cols = BITS;
  for(int i = BITS, st = 0; i >= 0; i--, st++) {
    int max_idx = st;
    T max_val = 0;
    for(int j = st; j < num_rows; j++) {
      if(max_val < res[j]) {
        max_val = res[j];
        max_idx = j;
      }
    }
    swap(res[max_idx], res[st]);
    int m = msb(res[st]);
    for(int j = st + 1; j < num_rows; j++) {
      if(res[j] & (1 << m)) {
        res[j] ^= res[st];
      }
    }
  }
  return res;
}
