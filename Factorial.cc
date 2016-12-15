template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

LL fact[MAXN] = {0}, ifact[MAXN] = {0};
void preprocess() {
	fact[0] = (ifact[0] = 1);
    for(int i = 1; i < MAXN; i++) {
		fact[i] = (fact[i-1]*i)%mod;
	}
	ifact[MAXN-1] = modinv(fact[MAXN-1], mod);
	for(LL i = MAXN-2; i > 0; i--){
		ifact[i] = (ifact[i+1]*(i+1))%mod;
	}
	assert((fact[2]*ifact[2])%mod == 1);
}

LL nCr(int n, int r) {
    return (fact[n] * ((ifact[n-r] * ifact[r])%mod)) % mod;
}
