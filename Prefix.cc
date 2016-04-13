int P[MAXN] = {0};
void prefix(const string &p) {
	int size = (int)p.size();
	int k = 0;
	P[0] = 0;
    for(int i = 1; i < size; i++) {
		while(k > 0 && p[k] != p[i]){
			k = P[k-1];
		}
		if(p[k] == p[i]){
			k++;
		}
		P[i] = k;
	}
}
