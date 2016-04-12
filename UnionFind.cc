class UnionFind{
	private:
		int V, Rank[MAXN], P[MAXN];
	public:
		UnionFind(int x)
		{
			V = x;
			for(int i = 0; i <= x; i++)
				Rank[i] = 1, P[i] = i;
		}

		int find_root(int x)
		{
			if(x == P[x])	return x;
			return P[x] = find_root(P[x]);
		}

		void Union(int x, int y)
		{
			int xr = find_root(P[x]), yr = find_root(P[y]);
			if(xr == yr)
				return ;
			if(Rank[xr] >= Rank[yr])
				Rank[xr] += Rank[yr], P[yr] = xr;
			else
				Rank[yr] += Rank[xr], P[xr] = yr;
		}
};
