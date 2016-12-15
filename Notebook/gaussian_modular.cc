/* Gauss for modular inverses
 */
template<typename T, typename S>
vector<vector<T> > gaussian(vector<vector<T> > m, S mod) {
    if(m.empty())   return { };
    int no_rows = m.size(), no_cols = m[0].size();
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(m[row][col] == 0) {
            int f = -1;
            for(int i = row+1; i < no_rows; i++) {
                if(m[i][col] != 0) { f = i; break; }
            }
            if(f == -1) continue;
            swap(m[f], m[row]);
        }
        for(int c = col+1; c < no_cols; c++) m[row][c] = (m[row][c] * modinv(m[row][col], mod)) % mod;
        m[row][col] = 1;
        for(int r = row+1; r < no_rows; r++) {
            T temp = m[r][col];
            for(int c = col; c < no_cols; c++) m[r][c] = (m[r][c] - ((m[row][c] * temp)%mod) + mod) % mod;
        }
        row++;
    }
    return m;
}
template<typename T, typename S>
vector<vector<T> > inverse(vector<vector<T> > m, S mod) {
    vector<vector<T> > temp(m.size(), vector<T>(m[0].size() * 2, 0));
    for(int i = 0; i < m.size(); i++)   for(int j = 0; j < m[i].size(); j++)    temp[i][j] = m[i][j];
    for(int i = 0; i < m.size(); i++)   temp[i][i+m[i].size()] = 1;
    vector<vector<T> > x = gaussian(temp, mod);
    vector<vector<T> > res = m;
    int n = m.size();
    for(int r = 0; r < n; r++) {
        for(int c = r+1; c < n; c++) {
            if(x[r][c]) {
                T crap = x[r][c];
                for(int i = c; i < 2*n; i++) {
                    x[r][i] = (x[r][i] - ((crap * x[c][i]) % mod) + mod) % mod;
                }
            }
        }
    }
    for(int i = 0; i < m.size(); i++)   for(int j = 0; j < m[i].size(); j++)    res[i][j] = x[i][j+m[i].size()];
    return res;
}
template<typename T>
vector<vector<T> > mul(vector<vector<T> > lhs, vector<vector<T> > rhs, T mod) { // Modular Multiplication
    vector<vector<T> > res(lhs.size(), vector<T>(rhs.size(), 0));
    for(int i = 0; i < res.size(); i++) {
        for(int j = 0; j < res[i].size(); j++) {
            for(int x = 0; x < lhs[0].size(); x++) {
                res[i][j] = (res[i][j] + ((lhs[i][x] * rhs[x][j]) % mod)) % mod;
            }
        }
    }
    return res;
}
/* End Modular Gaussian
 */
