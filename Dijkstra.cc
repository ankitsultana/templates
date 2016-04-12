#define F first
#define S second
int dijk(int a, int b, vector<vector<pair<int, int> > > &adj) {
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	vector<bool> vis(V+1, false);
	q.push(make_pair(0, a));
	while(!q.empty()){
		pair<int, int> f = q.top();
		q.pop();
		if(vis[f.S])	continue;
		vis[f.S] = true;
		if(f.S == b)	return f.F;
		for(vector<pair<int, int> >::iterator it = adj[f.S].begin(); it != adj[f.S].end(); it++){
			if(!vis[it->S]){
				q.push(make_pair(it->F+f.F, it->S));
			}
		}
	}
	return 0;
}
