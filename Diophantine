/* Return a integer solution (x, y) to 
 * 		a*x + b*y = gcd(a, b)
 * * * * * * * * * * * * * * * * */
template<typename T>
T extendedeuclid (T a, T b, T & x, T & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	T x1, y1;
	T d = extendedeuclid (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

/* Return a integer solution (x, y) to 
 * 		a*x + b*y = c
 * Assumes that there exists a solution
 * * * * * * * * * * * * * * * * */
template<typename T>
pair<T, T> diophantine(T a, T b, T c)
{
	bool neg_a = a < 0, neg_b = b < 0;
	if(neg_a)	a = -a;if(neg_b)	b = -b;
	T g = gcd(a, b), x, y;
	/* Assert that there exists a solution */
	assert(c % g == 0);
	a /= g, b /= g, c /= g;
	extendedeuclid(a, b, x, y);
	if(neg_a) x = -x;if(neg_b) y = -y;  
	return MP(x*c, y*c);
}
