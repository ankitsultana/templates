/* Number the edges
 * * * * * * * * * * */
int high[MAXN] = {0}, depth[MAXN] = {0}, n, ROOT, E;
bool vis[MAXN] = {false};
vector<pair<int, int> > result;
vector<pair<int, int> >  adj[MAXN];

/* Bridge Tree Stuff
 * * * * * * * * * * */
bool is_bridge[MAXN] = {false};
int comp[MAXN] = {0};
int global_iter = 1;
vector<int> tree[MAXN];

void FindBridges(int node, int prev = -1)
{
	depth[node] = prev == -1?0: depth[prev]+1;
	vis[node] = true;
	high[node] = depth[node];
	int child;
    for(int i = 0; i < adj[node].size(); i++) {
		child = adj[node][i].first;
		if(child == prev)	continue;
		if(vis[child]){
			high[node] = min(high[node], depth[child]);
		}
		else{
			FindBridges(child, node);
			high[node] = min(high[node], high[child]);
			if(high[child] > depth[node]){
				// result.push_back(make_pair(node, child));
				is_bridge[adj[node][i].second] = true;
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
	// Take Input
}

// Call make_bridge_tree(1, 1, vis);
void compress_bridge_components(int node, int comp_no, bool vis[])
{
	if(vis[node])	return ;
	comp[node] = comp_no;
	vis[node] = true;
	int sz = int(adj[node].size());
    for(int i = 0; i < adj[node].size(); i++) {
		if(vis[adj[node][i].first])	continue;
		compress_bridge_components(adj[node][i].first, is_bridge[adj[node][i].second]?++global_iter: comp_no, vis);
	}
}
void make_bridge_tree() {
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < adj[i].size(); j++) {
			if(is_bridge[adj[i][j].second]){
				tree[comp[i]].push_back(comp[adj[i][j].first]);
			}
		}
	}
}
void solve() {
    for(int i = 1; i <= n; i++) {
		if(vis[i])	continue;
		ROOT = i;
		FindBridges(ROOT, 0);
	}
	// Found the Bridges
	bool vis[MAXN] = {false};
	compress_bridge_components(1, 1, vis);
	make_bridge_tree();
}
/* Call like so
 * initialise();
 * solve();
 */
