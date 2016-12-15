int find_common(int a, int b, int c, int d) {
	int lca_one = LCA(a, c), lca_two = LCA(a, d);
	int res = (depth[lca_one]-depth[lca_two]);
	lca_one = LCA(b, c), lca_two = LCA(b, d);
	res -= (depth[lca_one]-depth[lca_two]);
	return abs(res);
}
