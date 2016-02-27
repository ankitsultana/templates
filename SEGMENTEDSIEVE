#define MAXN 32000
#define MAXINTERVAL 200003

bool is_prime[MAXN] = {false};
bool flag[MAXINTERVAL] = {false};
vector<LL> primes;
/* Compute all the primes before hand */
void sieve_eratosthenes()
{
	std::fill(&is_prime[0], &is_prime[0] + MAXN, true);
	is_prime[1] = false;
	for(int i = 2; i*i <= MAXN; i++){
		if(is_prime[i]){
			for(int j = i*i; j < MAXN; j += i){
				is_prime[j] = false;
			}
		}
	}
	for(int i = 2; i < MAXN; i++) {
		if(is_prime[i])
			primes.PB((LL)i);
	}
}

/* Returns the prime-count within range [a,b] and marks them in flag[] */
int segmented_sieve(int a, int b)
{
	if(a > b)	swap(a,b);
	assert(b - a < MAXINTERVAL);
	std::fill(&flag[0], &flag[0] + MAXINTERVAL, false);
	int res = 0;
	for(int i = 0; i < primes.size(); i++) {
		if(primes[i] > b)	break;
		int index = a/primes[i];
		for(LL j = index; ; j++) {
			if(primes[i]*j >= a && primes[i]*j <= b) {
				flag[primes[i]*j - a] = true;
			}
			else if(primes[i]*j > b) {
				break;  
			}
		}
	}
	for(int i = 0; i <= b-a; i++) {
		if(i + a < MAXN) {
			if(is_prime[i+a]) {
				res++;  
			}
		}
		else if(!flag[i]) {
			res++;
		}
	}
	return res;
}
