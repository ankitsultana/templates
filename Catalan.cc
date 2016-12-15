LL catalan[MAXN] = {0};
void precomp_catalan() {
	catalan[1] = (catalan[0] = 1);
    for(int i = 2; i < MAXN; i++) {
        for(int j = 0; j < i; j++) {
			catalan[i] = (catalan[i]+(catalan[j]*catalan[i-1-j])%mod)%mod;
		}
	}
}
