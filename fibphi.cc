template<typename T, T mod>
struct Num {
    T x, y;
    Num operator+(Num other) {
        return Num(x + other.x, y + other.y);
    }
    Num operator-(Num other) {
        return Num(x - other.x, y - other.y);
    }
    Num operator-() {
        return Num(mod - x, mod - y);
    }
    Num operator*(Num other) {
        return Num(x*other.x + 5*y*other.y, x*other.y + y*other.x);
    }
    template<typename S>
    Num pow(S e) {
        Num res(1, 0), temp = *this;
        while(e) {
            if(e%2) { res = res * temp; }
            temp = temp * temp;
            e /= 2;
        }
        return res;
    }
    T get_answer() {
        return 2*y % mod;
    }
    Num(T a = 0, T b = 0) : x(a%mod), y(b%mod) { }
};
