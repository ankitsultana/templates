/* Start Centroid */
int c_par[MAXN];
int subtree[MAXN];
bool dead[MAXN];
vector<int> c_tree[MAXN];

int size_dfs(int v, int prev) {
	if(dead[v])	return 0;
	int res = 1;
	for(auto &elem: adj[v]) {
		if(dead[elem] || elem == prev) continue;
		res += size_dfs(elem, v);
	}
	return (subtree[v] = res);
}
int find_centroid(int v, int prev, int size_comp) {
	if(dead[v])	return -1;
	int max_sub = size_comp - subtree[v], temp = -1;
	for(auto &elem: adj[v]) {
		if(dead[elem] || elem == prev)	continue;
		temp = find_centroid(elem, v, size_comp);
		if(temp > 0)	return temp;
		max_sub = max(max_sub, subtree[elem]);
	}
	if(max_sub <= size_comp/2)	return v;
	return -1;
}
void build_centroid_tree(int v = 1, int prev = -1) {
	int curr = find_centroid(v, -1, size_dfs(v, -1));
	assert(curr != -1);
	dead[curr] = true;
	c_par[curr] = prev;
	if(prev != -1)
		c_tree[prev].push_back(curr), c_tree[curr].push_back(prev);
	for(auto &elem: adj[curr]) {
		if(dead[elem])	continue;
		build_centroid_tree(elem, curr);
	}
}
/* End Centroid */
