int lp[MAXN];

void precomp_lowest_primes()
{
	lp[1] = -1;
	for(int i = 2; i < MAXN; i++){
		if(lp[i] == 0)
			lp[i] = -1, primes.push_back(i);
		int z = lp[i];
		if(lp[i] == -1) z = i;
		for(int j = 0; j < primes.size() && primes[j] <= z && i*primes[j] < MAXN; j++){
			lp[i*primes[j]] = primes[j];
		}
	}
	REP(i,MAXN){
		if(lp[i] < 0){
			lp[i] = i;  
		}
	}
}
