	queue<int> q;
	REP1(i,n){
		if(indegree[i] == 0)
			q.push(i);
	}
	vi result;
	int edge_count = 0;
	bool exists[30] = {false};
	while(!q.empty()){
		int f = q.front();
		q.pop();
		for(vi::iterator it = adj[f].begin(); it != adj[f].end(); it++){
			edge_count++;
			indegree[*it]--;  
			if(indegree[*it] == 0)
				q.push(*it);
		}
		result.PB(f);
	}

	if(edge_count != E){
		cout<<"Impossible\n";  
	}
	// result contains top sorted
