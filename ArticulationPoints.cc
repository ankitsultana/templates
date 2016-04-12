int high[MAXN] = {0}, depth[MAXN] = {0}, n;
bool vis[MAXN] = {false};
bool is_articulate[MAXN] = {false};
vector<int> result, adj[MAXN];
int ROOT;
void FindArticulate(int node, int prev = -1) {
	depth[node] = prev == -1?0: depth[prev]+1;
	vis[node] = true;
	high[node] = depth[node];
	int sz = SZ(adj[node]), child;
	int children = 0;
    for(int i = 0; i < sz; i++) {
		child = adj[node][i];
		if(child == prev)	continue;
		if(vis[child]){
			high[node] = min(high[node], depth[child]);
		} else {
			children++;
			FindArticulate(child, node);
			high[node] = min(high[node], high[child]);
			if(node == ROOT && children > 1) {
				is_articulate[node] = true;
			}
			if(node != ROOT && high[child] >= depth[node]) {
				is_articulate[node] = true;
			}
		}
	}
}

// Use a global variable n == number of vertices
void initialise() {
	result.clear();
    for(int i = 0; i <= n; i++) {
		depth[i] = high[i] = 0;
		vis[i] = false;
		is_articulate[i] = false;
		adj[i].clear();
	}
}

void solve() {
    for(int i = 1; i <= n; i++) {
		if(vis[i])	continue;
		ROOT = i;
		FindArticulate(i);
	}
	int answer = 0;
    for(int i = 1; i <= n; i++) {
		if(is_articulate[i]){
			answer++;
			// result.PB(i);
		}
	}
	// OUTPUT: answer
}
