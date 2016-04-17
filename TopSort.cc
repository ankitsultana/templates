void topsort() {
	queue<int> q;
    for(int i = 1; i <= n; i++) {
		if(indegree[i] == 0)
			q.push(i);
	}
	vector<int> result;
	int edge_count = 0;
	while(!q.empty()) {
		int f = q.front();
		q.pop();
		for(vector<int>::iterator it = adj[f].begin(); it != adj[f].end(); it++) {
			edge_count++;
			indegree[*it]--;
			if(indegree[*it] == 0)
				q.push(*it);
		}
		result.push_back(f);
	}
	if(edge_count != E) {
		cout<<"Impossible\n";
	}
}
