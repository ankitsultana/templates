template<typename T> // Runtime MOD determination
struct modint {
    T val, MOD;
    modint(T MOD, T a = 0) { this->MOD = MOD; val = a % MOD; if(val < 0) val += MOD; }
    modint& operator+=(modint rhs) { this->val = this->val + rhs.val; if(this->val >= MOD) this->val -= MOD; return *this; }
    modint& operator-=(modint rhs) { if((this->val -= rhs.val) < 0) this->val += MOD; return *this; }
    modint& operator*=(modint rhs) { this->val = (this->val * rhs.val) % MOD; return *this; }
    modint& operator/=(modint rhs) { *this = (*this * rhs.pow(MOD - 2)); return *this; }
    modint operator+(modint rhs) const { return modint(*this) += rhs; }
    modint operator-(modint rhs) const { return modint(*this) -= rhs; }
    modint operator*(modint rhs) const { return modint(*this) *= rhs; }
    modint operator/(modint rhs) const { return modint(*this) /= rhs; }
    modint& operator=(T rhs) { *this = modint(rhs); return *this; }
    template<typename S>
    modint pow(S e) const {
        modint val = modint(1), base = modint(*this);
        while(e > 0) {
            if(e % 2) { val = val * base; }
            base = base * base, e /= 2;
        }
        return val;
    }
};
