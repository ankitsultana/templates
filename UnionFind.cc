struct dsu {
  vector<int> Rank, P;
  int V;
  dsu(int v = 0) : V(v) {
    Rank = vector<int>(v + 1, 0);
    P = vector<int>(v + 1, 0);
    for(int i = 0; i < P.size(); i++) {
      P[i] = i, Rank[i] = 1;
    }
  }
  int find_root(int x) { return x == P[x] ? x : P[x] = find_root(P[x]); }
  void merge(int x, int y) {
    int xr = find_root(P[x]), yr = find_root(P[y]);
    if(xr == yr) return ;
    if(Rank[xr] < Rank[yr]) swap(xr, yr), swap(x, y);
    Rank[xr] += Rank[yr];
    P[yr] = xr;
  }
};
