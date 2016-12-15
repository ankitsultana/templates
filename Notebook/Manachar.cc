// even positions are spaces (even length palindromes)
// odd ones, i are (i-1)/2 th in string
int L[2*MAXN];
int max_end[MAXN];
void manachar(const string &input) {
	int size = int(input.size());
    for(int i = 0; i < size; i++) max_end[i] = 1;
	int N = 2*size+1;
	// initialise L array
	std::fill(&L[0], &L[0] + N, 0);
	// Start
	L[0] = 0, L[1] = 1;
	int C = 1, R = 2, i = 0, iMirror, maxLPSCenterPosition = 0, start = -1, end = -1, diff = -1;
    int crap;
    int last = 0;
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
        if(L[i] != 0) {
            crap = (i + L[i] - 1);
            crap = (crap-1)/2;
            for(int x = max(last, 1 + (i-1)/2); x <= crap; x++) {
                max_end[x] = max(max_end[x], L[i] - 2 * (crap - x));
            }
            last = max(last, crap);
        }
	}
}

