LL fact[MAXN] = {0}, ifact[MAXN] = {0};
void preprocess()
{
	fact[0] = (ifact[0] = 1);
	REPc(i,1,MAXN-1){
		fact[i] = (fact[i-1]*i)%mod;
	}
	ifact[MAXN-1] = modinv(fact[MAXN-1]);
	for(LL i = MAXN-2; i > 0; i--){
		ifact[i] = (ifact[i+1]*(i+1))%mod;
	}
	assert((fact[2]*ifact[2])%mod == 1);
}
