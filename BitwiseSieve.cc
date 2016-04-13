#define MAXN 99999953ull  // last prime
#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))
#define LEN 5761901
unsigned LL base[MAXN/64], primes[LEN];
void sieve() {
	unsigned LL i, j, k;
	for(i=3; i<LEN; i+=2) if(!chkC(base, i))
		for(j=i*i, k=i<<1; j<MAXN; j+=k)
			setC(base, j);
	primes[0] = 2;
	for(i=3, j=1; i<MAXN; i+=2) if(!chkC(base, i))
		primes[j++] = i;
}
