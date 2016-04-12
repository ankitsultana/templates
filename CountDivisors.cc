#define MAXN 1000003

bool is_prime[MAXN] = {false};
vector<LL> primes;
void sieve_eratosthenes() {
	for(int i = 0; i < MAXN; i++)	is_prime[i] = true;
	is_prime[1] = false;
	for(int i = 2; i*i <= MAXN; i++){
		if(is_prime[i]){
			for(int j = i*i; j < MAXN; j += i){
				is_prime[j] = false;
			}
		}
	}
	for(int i = 2; i < MAXN; i++)
		if(is_prime[i])
			primes.push_back(i);
}

/* Miller Rabbin,
 * Complexity: O(k * log2^3(n))
 * * * * * * * * * * * */
inline LL multiply(LL a, LL b, const LL &m)
{
	a %= m, b %= m; 
	long double res = a;res *= b;
	LL c = (LL)(res/m); 
	a *= b, a -= c*m, a %= m;
	if(a < 0)	
		a += m; 
	return a;
}

inline LL power(LL a, LL b, const LL &m)
{
	LL ans = 1;  
	while(b) {
		if(b & 1) {
			ans = multiply(ans, a, m);
		}
		a = multiply(a, a, m);
		b >>= 1;
	}
	return ans;
}

// Returns true if p is prime
inline bool Miller(LL p) {
	int b[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	if(p < 2)	return false;  
	if(p != 2 && !(p&1))	return false;
	for(int i = 0; i < 25; i++) {
		if(p == b[i])	return true;  
		else if(p % b[i] == 0)	return false;
	}
	int cnt = 0;
	LL s = p-1;
	while(!(s&1)) {
		s /= 2;  
		cnt++;
	}
	LL accuracy = 2, m;
	for(int i = 0; i < accuracy; i++) {
		LL a = rand() % (p-1) + 1;
		m = p;
		LL x = power(a, s, m);
		if(x == 1 || x == p-1)	continue;
		int flag = 0;
		for(int i = 1; i < cnt; i++) {
			x = multiply(x, x, m);  
			if(x == 1)	return false;
			if(x == p-1) {
				flag = 1;  
				break;
			}
		}
		if(flag)	continue;
		return false;
	}
	return true;
}

LL count_divisors(LL n)
{
	LL ans = 1;
	for(auto p: primes) {
		if(p*p*p > n)	break;
		LL count = 1;
		while(n % p == 0) {
			n /= p;
			count++;
		}
		ans = ans*count;
	}
	LL sq = sqrt(double(n));
	if(Miller(n)) {
		ans = ans*2;
	}
	else if(sq*sq == n && Miller(sq)) {
		ans *= 3;
	}
	else if(n != 1) {
		ans *= 4;
	}
	return ans;
}
