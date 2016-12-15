template<typename T, int SIZE>
struct matrix {
    T data[SIZE][SIZE];
    matrix() {
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                data[i][j] = 0;
            }
        }
    }
    matrix operator*(matrix &other) { // returns a new instance of matrix
        matrix res;
        for(int r = 0; r < SIZE; r++) {
            for(int k = 0; k < SIZE; k++) {
                for(int c = 0; c < SIZE; c++) {
                    res.data[r][c] = (res.data[r][c] + (data[r][k] * other.data[k][c])) % mod;
                }
            }
        }
        return res;
    }
    matrix& operator*=(matrix &other) {
        *this = *this * other;
        return *this;
    }
    matrix operator+(matrix &other) {
        matrix res;
        for(int r = 0; r < SIZE; r++) {
            for(int c = 0; c < SIZE; c++) {
                res.data[r][c] = (data[r][c] + other.data[r][c]);
                if(res.data[r][c] >= mod) res.data[r][c] -= mod;
            }
        }
        return res;
    }
    matrix& operator+=(matrix &other) {
        for(int r = 0; r < SIZE; r++) {
            for(int c = 0; c < SIZE; c++) {
                data[r][c] += other.data[r][c];
                if(data[r][c] >= mod) data[r][c] -= mod;
            }
        }
        return *this;
    }
    T operator[](int x) {
        return data[x];
    }
    void identity() {
        for(int r = 0; r < SIZE; r++) {
            for(int c = 0; c < SIZE; c++) {
                data[r][c] = r == c;
            }
        }
    }
    matrix expo(long long e) {
        matrix res, base = *this;
        res.identity();
        while(e > 0) {
            if(e % 2) {
                res = res * base;
            }
            base = base * base;
            e /= 2;
        }
        return res;
    }
    vector<T> operator*(const vector<T> &v) {
        vector<T> res(v.size(), 0);
        for(int r = 0; r < SIZE; r++) {
            for(int c = 0; c < SIZE; c++) {
                res[r] += (data[r][c] * v[c]) % mod;
                if(res[r] >= mod) res[r] -= mod;
            }
        }
        return res;
    }
};
