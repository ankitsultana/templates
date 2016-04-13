#define MAXN 202
#define INF 1000000000

int n;
int adj_m[MAXN][MAXN], u[MAXN], v[MAXN], link[MAXN], par[MAXN], used[MAXN], minval[MAXN];
void Hungarian() {
	REP(i,MAXN)	par[i] = 0, u[i] = 0, v[i] = 0, used[i] = 0, minval[i] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < MAXN; j++) {
			used[j] = false;
			minval[j] = INF;
		}
		int j_cur = 0;
		par[j_cur] = i;
		do {
			used[j_cur] = true;
			int j_next, delta = INF, i_cur = par[j_cur];
			for (int j = 0; j <= n; j++)
				if (!used[j]) {
					int cur = adj_m[i_cur][j] - u[i_cur] - v[j];
					if (cur < minval[j]) {
						minval[j] = cur; link[j] = j_cur;
					}
					if (minval[j] < delta) {
						delta = minval[j]; j_next = j;
					}
				}
			for (int j = 0; j <= n; j++)
				if (used[j]) {
					u[par[j]] += delta; v[j] -= delta;
				}
				else {
					minval[j] -= delta;
				}
			j_cur = j_next;
		} while (par[j_cur]);
		do {
			int j_prev = link[j_cur];
			par[j_cur] = par[j_prev];
			j_cur = j_prev;
		} while (j_cur > 0);
	}
	// cout<<v[0]<<'\n'; // For Maximum.. For minim change to -ve
}

/* Take edge weights negative for Max */
