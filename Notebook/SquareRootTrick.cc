/* Concept:
 * 		(n/i) takes only √n distinct values
 * 		Moreover, for i in [1..√n] all values are distinct
 *     				i.e from [n..√n]
 * 		for i in [√n+1..n] there are only √n values,
 *			thus values repeat.
 * * * */
LL d = 1;
for(; d*d <= n; d++) {
	// work with (n/d)
}
LL x = n/d, lower, upper, freq;
for(; x > 0; x--) {
	lower = (n/(x+1))+1;
	upper = n/x;
	freq = upper - lower + 1;
	// for i in [lower...upper], value of n/i = x
}
