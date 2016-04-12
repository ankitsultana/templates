#define MAXN 51
double dearange[MAXN];
template<typename T>
void compute_derangement(T dearange[]) {
	dearange[0] = 1, dearange[1] = 0;
    for(int i = 2; i < MAXN; i++) {
		dearange[i] = (i-1)*(dearange[i-1] + dearange[i-2]);
	}
}
