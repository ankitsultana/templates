struct kosaraju {
    vector<int> rev_graph[MAXN], adj[MAXN];
    int glob_time = 0, f[MAXN] = {0}, finv[MAXN] = {0};
    int comp[MAXN] = {0}, scc_cnt = 0;;
    bool vis[MAXN], visited[MAXN];
    void dfs1(int node, bool vis[]) {
        if(vis[node])	return ;
        vis[node] = true;
        int sz = int(rev_graph[node].size());
        for(int i = 0; i < sz; i++) {
            if(vis[rev_graph[node][i]])	continue;
            dfs1(rev_graph[node][i], vis);
        }
        f[node] = ++glob_time;
        finv[glob_time] = node;
    }
    void dfs2(int node, bool vis[], const int &leader) {
        if(vis[node])	return ;
        vis[node] = true;
        comp[node] = scc_cnt;
        int sz = int(adj[node].size());
        for(int i = 0; i < sz; i++) {
            if(vis[adj[node][i]])	continue;
            dfs2(adj[node][i], vis, leader);
        }
    }
    void init() {
        for(int i = 0; i <= n; i++) {
            adj[i].clear();
            rev_graph[i].clear();
            f[i] = (finv[i] = 0);
            comp[i] = 0;
        }
    }
    void solve() {
        // build graph
        glob_time = 0;
        scc_cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(vis[i])	continue;
            dfs1(i, vis);
        }
        for(int i = n; i > 0; i--){
            if(visited[finv[i]])	continue;
            scc_cnt++;
            dfs2(finv[i], visited, finv[i]);
        }
    }
};
