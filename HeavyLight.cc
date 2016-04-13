int subsize[MAXN] = {0}, depth[MAXN] = {0};
void DFS(int node = 1, int prev = -1, int d = 0)
{

	subsize[node] = 1, depth[node] = d, pa[node][0] = prev;
	int size = (int)adj[node].size();
	REP(i,size){
		if(prev == adj[node][i])	continue;
		DFS(adj[node][i], node, d+1);
		subsize[node] += subsize[adj[node][i]];
	}
}

int pos_in_base[MAXN] = {0}, base_array[MAXN] = {0};
int chain_ind[MAXN] = {0}, chain_head[MAXN] = {0};
int ptr = 1, chain_no = 0;
void HLD(int node = 1, int prev = -1, int cost = 0)
{
	if(chain_head[chain_no] == -1)
		chain_head[chain_no] = node;
	pos_in_base[node] = ptr;
	chain_ind[node] = chain_no;
	base_array[ptr++] = cost;
	int ind = -1, maxim = -1, size = (int)adj[node].size();
	REP(i,size){
		if(adj[node][i] == prev)	continue;
		if(subsize[adj[node][i]] > maxim)
			ind = adj[node][i], maxim = subsize[ind];
	}
	if(ind > 0)
		HLD(ind, node);
	REP(i,size){
		if(adj[node][i] == prev || adj[node][i] == ind)	continue;
		chain_no++;
		HLD(adj[node][i], node);
	}
}
