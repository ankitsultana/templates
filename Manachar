// even positions are spaces (even length palindromes)
// odd ones, i are (i-1)/2 th in string
int L[2*MAXN];
void manachar(string input) {
	int size = int(input.size());
	int N = 2*size+1;
	// initialise L array
	std::fill(&L[0], &L[0] + N, 0);
	// Start
	L[0] = 0, L[1] = 1;
	int C = 1, R = 2, i = 0, iMirror, maxLPSCenterPosition = 0, start = -1, end = -1, diff = -1;
	for(int i = 2; i < N; i++) {
		iMirror = 2*C-i;
		L[i] = 0;
		diff = R-i;
		if(diff > 0)
			L[i] = min(L[iMirror], diff);
		while ( ((i + L[i]) < N && (i - L[i]) > 0) && 
            ( ((i + L[i] + 1) % 2 == 0) || (input[(i + L[i] + 1)/2] == input[(i - L[i] - 1)/2] ))) {
            L[i]++;
        }
		if(i + L[i] > R){
			C = i;
			R = i+L[i];
		}
	}
}
