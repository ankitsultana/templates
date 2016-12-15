template<typename T, T MOD>
struct modint {
    T val;
    modint() : val(0) { }
    modint(T a) { val = a % MOD; if(val < 0) val += MOD; }
    T get() { return val; }
    modint& operator+=(modint rhs) { this->val = (this->val + rhs.val) % MOD; return *this; }
    modint& operator-=(modint rhs) { if((this->val -= rhs.val) < 0) this->val += MOD; return *this; }
    modint& operator*=(modint rhs) { this->val = (this->val * rhs.val) % MOD; return *this; }
    modint& operator/=(modint rhs) { *this = (*this * rhs.pow(MOD - 2)); return *this; }
    modint operator+(modint rhs) const { return modint(*this) += rhs; }
    modint operator-(modint rhs) const { return modint(*this) -= rhs; }
    modint operator*(modint rhs) const { return modint(*this) *= rhs; }
    modint operator/(modint rhs) const { return modint(*this) /= rhs; }
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
