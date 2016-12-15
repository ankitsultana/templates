/* Bellman Ford:
 * 		Complexity: O(V*E)
 * * * * * * * * * * * * * */
int n, m, dp[MAXN];
vector<int> adj[MAXN], wt[MAXN];
void initialize() {
    for(int i = 1; i <= n; i++) {
		adj[i].clear();
		wt[i].clear();
		dp[i] = INF;
	}
}
void bellman_ford(int v, int start_vertex = -1) {
	dp[v] = 0;
	vector<int> p(n+1, -1);
	int x;
    for(int i = 0; i < n; i++) {
		x = -1;
        for(int k = 1; k <= n; k++) {
            for(int j = 0; j < adj[k].size(); j++) {
				int other = adj[k][j];
				if(dp[k] < INF) {
					if(dp[other] > dp[k] + wt[k][j]) {
						dp[other] = dp[k] + wt[k][j];
						p[other] = k;
						x = other;
					}
				}
			}
		}
	}
	/* Check Negative Cycle */
	if(x != -1) {
		cout << "Negative Cycle Found\n";
		/* Print Negative Cycle */
		/* * * * * * * * * * * * * * * * * * * * *
		int y = x;
        for(int i = 0; i < n; i++) {
			y = p[y];
		}
		vector<int> path;
		for(int cur = y; ;cur = p[cur]) {
			path.PB(cur);
			if(cur == y && path.size() > 1)	break;
		}
		reverse(path.begin(), path.end());
        for(int i = 0; i < path.size(); i++) {
			cout << path[i] << ' ';
		}
		* * * * * * * * * * * * * * * * * * * * */
		return ;
	}
	/* Print Path */
	/* * * * * * * * * * * * * * * * * * * * *
	assert(start_vertex != -1);
	vector<int> path;
	for(int cur = start_vertex; cur != -1; cur = p[cur]) {
		path.PB(cur);
	}
	reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++) {
		cout<<path[i]<<' ';
	}
	* * * * * * * * * * * * * * * * * * * * */
}
