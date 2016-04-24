#define MAXN 200005

int lcp[MAXN], cnt[256], cls[2][MAXN], pos[2][MAXN], st[MAXN], rnk[MAXN], n;
int suffix_idx[MAXN], suffix_size[MAXN];

void initialize() {
    for(int i = 0; i < 2; i++) for(int j = 0; j < MAXN; j++) cls[i][j] = 0, pos[i][j] = 0, st[j] = 0, rnk[j] = 0;
}

void suffix_array(const string &s) {
	initialize();
	int i, j;
	fill(cnt, 0, sizeof(cnt));
	int n = s.size();
	for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
	for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
	for (i = 0; i < n; i++) pos[0][--cnt[cls[0][i]]] = i;
	int cur = 0;
	for (i = 0; (1 << i) < n; i++) {
		int clen = (1 << i);
		for (j = 0; j < n; j++) {
			if (j > 0 && pos[cur][j - 1] + clen < n && cls[cur][pos[cur][j]] == cls[cur][pos[cur][j - 1]] &&
                cls[cur][pos[cur][j] + clen / 2] == cls[cur][pos[cur][j - 1] + clen / 2]
			   )
				cls[1 - cur][pos[cur][j]] = cls[1 - cur][pos[cur][j - 1]];
			else cls[1 - cur][pos[cur][j]] = j;
		}
		for (j = 0; j < n; j++) { st[j] = j; pos[1 - cur][j] = pos[cur][j]; }
		for (j = 0; j < n; j++) {
			int cele = pos[cur][j] - clen;
			if (cele >= 0) pos[1 - cur][st[cls[1 - cur][cele]]++] = cele;
		}
		cur = 1 - cur;
	}
	for (i = 0; i < n; i++) { pos[0][i] = pos[cur][i]; rnk[pos[cur][i]] = i;}
	int x = 0;
	for (i = 0; i < n; i++) {
		if (rnk[i] < n - 1) {
			for (j = pos[cur][rnk[i] + 1]; max(i, j) + x < n && s[i + x] == s[j + x]; x++);
			lcp[rnk[i] + 1] = x; if (x > 0) x--;
		}
	}
    for(int i = 0; i < n; i++) {
		suffix_idx[i] = pos[1][i];
		suffix_size[i] = n - pos[1][i];
	}
}
