/* Returns smallest such x
 * that, a^x === b mod m | O(root(m) * log2)
 * * * * * * * * * * * * * * * */
template<typename T>
T baby_step (T a, T b, T m) {
	T n = (T) sqrt (m + .0) + 1;
	T an = 1;
	for (T i=0; i<n; ++i)
		an = (an * a) % m;
	map<T,T> vals;
	for (T i=1, cur=an; i<=n; ++i) {
		if (!vals.count(cur))
			vals[cur] = i;
		cur = (cur * an) % m;
	}
	T final_ans = INF;
	for (T i=0, cur=b; i<=n; ++i) {
		if (vals.count(cur)) {
			T ans = vals[cur] * n - i;
			if (ans < m && ans != 0) {
				final_ans = min(final_ans, ans);
			}
		}
		cur = (cur * a) % m;
	}
	return final_ans == INF?-1: final_ans;
}
