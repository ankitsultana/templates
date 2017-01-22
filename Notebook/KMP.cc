int P[MAXN] = {0};
void prefix(const string &p) {
	int size = (int)p.size(), k = 0;
	P[0] = 0;
	for(int i = 1; i < size; i++) {
		while(k > 0 && p[k] != p[i])
			k = P[k-1];
		if(p[k] == p[i])
			k++;
		P[i] = k;
	}
}
int kmp(const string &main_string, const string &pattern) {
	prefix(pattern);
	int res = 0, main_size = int(main_string.size());
	int pattern_size = int(pattern.size());
	int k = 0;
	for(int i = 0; i < main_size; i++) {
		while(k > 0 && pattern[k] != main_string[i]){
			k = P[k-1];
		}
		if(pattern[k] == main_string[i]){
			k++;
		}
		if(k == pattern_size){
			res++;
			k = P[k-1];
		}
	}
	return res;
}
