#define MAXN 200005

int lcp[MAXN], cnt[256], cls[2][MAXN], sa[2][MAXN], st[MAXN], rnk[MAXN], n;
int suffix_idx[MAXN], suffix_size[MAXN];

void initialize()
{
	REP(i,2) REP(j,MAXN) cls[i][j] = 0, sa[i][j] = 0, st[j] = 0, rnk[j] = 0;
}

void suffix_array(const string &s) {
	initialize();
	int i, j;
	memset(cnt, 0, sizeof(cnt));
	int n = s.size();
	for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
	for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
	for (i = 0; i < n; i++) sa[0][--cnt[cls[0][i]]] = i;
	int cur = 0;
	for (i = 0; (1 << i) < n; i++) {
		int clen = (1 << i);
		for (j = 0; j < n; j++) {
			if (j > 0 && sa[cur][j - 1] + clen < n && cls[cur][sa[cur][j]] == cls[cur][sa[cur][j - 1]] &&
					cls[cur][sa[cur][j] + clen / 2] == cls[cur][sa[cur][j - 1] + clen / 2]
			   )
				cls[1 - cur][sa[cur][j]] = cls[1 - cur][sa[cur][j - 1]];
			else cls[1 - cur][sa[cur][j]] = j;
		}
		for (j = 0; j < n; j++) { st[j] = j; sa[1 - cur][j] = sa[cur][j]; }
		for (j = 0; j < n; j++) {
			int cele = sa[cur][j] - clen;
			if (cele >= 0) sa[1 - cur][st[cls[1 - cur][cele]]++] = cele;
		}
		cur = 1 - cur;
	}
	for (i = 0; i < n; i++) { sa[0][i] = sa[cur][i]; rnk[sa[cur][i]] = i;}
	int x = 0;
	for (i = 0; i < n; i++) {
		if (rnk[i] < n - 1) {
			for (j = sa[cur][rnk[i] + 1]; max(i, j) + x < n && s[i + x] == s[j + x]; x++);
			lcp[rnk[i] + 1] = x; if (x > 0) x--;
		}
	}
	REP(i,n) {
		suffix_idx[i] = sa[1][i];
		suffix_size[i] = n - sa[1][i];
	}
	REP(i,n) {
		pos[suffix_idx[i]] = i;
	}
}
