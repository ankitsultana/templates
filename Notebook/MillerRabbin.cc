/* Miller Rabbin,
 * Complexity: O(k * log2^3(n))
 * * * * * * * * * * * */
inline LL multiply(LL a, LL b, const LL &m) {
	a %= m, b %= m; 
	long double res = a;res *= b;
	LL c = (LL)(res/m); 
	a *= b, a -= c*m, a %= m;
	if(a < 0)	
		a += m; 
	return a;
}

inline LL power(LL a, LL b, const LL &m) {
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
	if(p < 2)	return false;  
	if(p != 2 && !(p&1))	return false;
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
