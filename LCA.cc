/* LCA BEGIN */
#define MAXN 10003
#define MAXLOGN 19
int pa[MAXN][MAXLOGN];
int depth[MAXN] = {0};

void lca_dfs(int node = 1, int prev = -1, int d = 0) {
	depth[node] = d;
	pa[node][0] = prev;
	int sz = int(adj[node].size());
	for(int i = 0; i < sz; i++) {
		if(adj[node][i] == prev)	continue;
		lca_dfs(adj[node][i], node, d+1);
	}
}
void preprocess_lca() {
	std::fill(&pa[0][0], &pa[0][0] + MAXN*MAXLOGN, -1);
	lca_dfs();
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= n; i++)
			if(pa[i][j-1] != -1) pa[i][j] = pa[pa[i][j-1]][j-1];
}
int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u]-depth[v];
	for(int i = 0; i < MAXLOGN; i++) if((diff>>i)&1) u = pa[u][i];
	if(u == v) return u;
	for(int i = MAXLOGN-1; i > -1; i--) if(pa[u][i] != pa[v][i])
		u = pa[u][i], v= pa[v][i];
	return pa[u][0];
}
int distance(int u, int v) {
	int l = LCA(u, v);
	return (depth[u] - depth[l]) + (depth[v] - depth[l]);
}
int kth(int u, int k) {
    if(k > depth[u])    return -1;
    for(int i = MAXLOGN-1; i >= 0; i--) {
        if((1<<i) & k) {
            u = pa[u][i];
        }
    }
    return u;
}
/* LCA END */
