struct Dinic {
  typedef LL FLOW_TYPE;
  static const int MAXN = 2e5, INF = 1e9;
  struct edge {
		int a, b;
    FLOW_TYPE cap, flow;
	};
	int n, s, t;
  vector<int> d, ptr, q;
	vector<edge> e;
	vector<vector<int> > g;
	//takes in number of nodes source and sink
	Dinic(int a, int b, int c): n(a), s(b), t(c) {
    d = vector<int>(MAXN, 0);
    ptr = vector<int>(MAXN, 0);
    q = vector<int>(MAXN, 0);
    g = vector<vector<int> >(MAXN);
  }
	void add_edge(int a, int b, FLOW_TYPE cap) {
		edge e1 = { a, b, cap, 0 };
		edge e2 = { b, a, 0, 0 };
		g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
	}
	bool bfs() {
    int qh=0, qt=0;
    q[qt++] = s;
    fill(d.begin(), d.end(), -1);
    d[s] = 0;
    while(qh < qt && d[t] == -1) {
      int v = q[qh++];
      for(size_t i=0; i<g[v].size(); ++i) {
        int id = g[v][i],
          to = e[id].b;
        if(d[to] == -1 && e[id].flow < e[id].cap) {
          q[qt++] = to;
          d[to] = d[v] + 1;
        }
      }
    }
    return d[t] != -1;
	}
	FLOW_TYPE dfs(int v, FLOW_TYPE flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
      int id = g[v][ptr[v]],
        to = e[id].b;
      if (d[to] != d[v] + 1)  continue;
      FLOW_TYPE pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
      if (pushed) {
        e[id].flow += pushed;
        e[id^1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
	}
	FLOW_TYPE dinic() {
    FLOW_TYPE flow = 0;
    for(;;) {
      if(!bfs()) break;
      fill(ptr.begin(), ptr.end(), 0);
      while(FLOW_TYPE pushed = dfs(s, INF))
        flow += pushed;
    }
    return flow;
	}
  void cut_dfs(int r, vector<bool> &vis) {
    if(vis[r]) return ;
    vis[r] = true;
    for(auto &id: g[r]) {
      int to = e[id].b;
      if(e[id].cap - e[id].flow > 0) {
        cut_dfs(to, vis);
      }
    }
  }
  vector<int> find_cut() { // Returns S
    vector<bool> vis(MAXN, false);
    cut_dfs(s, vis);
    vector<int> ans;
    for(int i = 0; i < vis.size(); i++) {
      if(vis[i]) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};
