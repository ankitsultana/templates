LL S[MAXN][MAXN] = {0}, n;
void stirling_second_kind() {
	S[0][0] = 1;
    for(int i = 0; i < MAXN; i++) {
		if(i == 0)	continue;
        for(int k = 1; k <= i; k++) {
			S[i][k] = (((k*S[i-1][k])%mod)+S[i-1][k-1])%mod;
		}
	}
}
