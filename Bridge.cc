int high[MAXN] = {0}, depth[MAXN] = {0}, n, ROOT;
bool vis[MAXN] = {false};
vector<pair<int, int> > result;
vector<int> adj[MAXN];
void FindBridges(int node, int prev = -1)
{
	depth[node] = prev == -1?0: depth[prev]+1;
	vis[node] = true;
	high[node] = depth[node];
	int child;
    for(int i = 0; i < adj[node].size(); i++) {
		child = adj[node][i];
		if(child == prev)	continue;
		if(vis[child]){
			high[node] = min(high[node], depth[child]);
		}
		else{
			FindBridges(child, node);
			high[node] = min(high[node], high[child]);
			if(high[child] > depth[node]){
				result.PB(MP(node, child));
			}
		}
	}
}

void initialise()
{
	result.clear();
    for(int i = 0; i <= n; i++) {
		adj[i].clear();
		high[i] = 0, depth[i] = 0, vis[i] = false;
	}
}

void solve()
{
    for(int i = 1; i <= n; i++) {
		if(vis[i])	continue;
		ROOT = i;
		FindBridges(ROOT, -1);
	}
}
