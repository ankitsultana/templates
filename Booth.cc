int booth(string s) {
	s += s;
	vector<int> f(s.size(), -1);
	int k = 0, size = int(s.size()), i;
    for(int j = 1; j < size; j++) {
		i = f[j-k-1];
		while(i != -1 && s[j] != s[k+i+1]) {
			if(s[j] < s[k+i+1]) {
				k = j-i-1;
			}
			i = f[i];
		}
		if(i == -1 && s[j] != s[k+i+1]) {
			if(s[j] < s[k+i+1]) {
				k = j;
			}
			f[j-k] = -1;
		}
		else {
			f[j-k] = i+1;
		}
	}
	return k;
}
string get_minimal(string s) {
	int rot = booth(s), n = int(s.size());
	string temp(s);
	int iter = 0;
	while(iter < n) {
		temp[iter] = s[(iter + rot)%n];
		iter++;
	}
	return temp;
}
