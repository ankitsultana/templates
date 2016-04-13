/* Convex Hull Trick (Constrained) */
LL m[MAXN], c[MAXN], x[MAXN], dp[MAXN], base[MAXN];
int pnt_cnt, line_no[MAXN];
double stack[MAXN];
// Return intersection points of lines i and j
double get_x(int i, int j) {
	double one = double(double(c[j])-double(c[i]));
	double two = double(double(m[i])-double(m[j]));
	double res = double(one)/double(two);
	return res;
}

void init(int n) {
	pnt_cnt = 1;
	// Initialize (dp[0], dp[1])
	// Initialize m[i], c[i], x[i], base[i]
	// Initialize m[0], c[0], x[0], base[0]
	line_no[0] = 0, line_no[1] = 1;
	stack[0] = get_x(0, 1);
}

LL solve(int n) {
	init(n);
	double x1, x2, curr_x;
	for(int i = 2; i <= n; i++) {
		curr_x = double(x[i]);
		int idx = int(lower_bound(stack, stack + pnt_cnt, curr_x) - stack);
		dp[i] = base[i] + c[line_no[idx]] + m[line_no[idx]]*x[i];
		/* Initialize/Modify c */
		c[i] += dp[i];
		x1 = get_x(line_no[pnt_cnt-1], i), x2 = stack[pnt_cnt-1];
		while(pnt_cnt > 0 && x1 <= x2) {
			x2 = stack[pnt_cnt-1];
			x1 = get_x(line_no[pnt_cnt-1], i);
			if(x1 > x2)	break;
			pnt_cnt--;
		}
		pnt_cnt++;
		// Insert current line
		stack[pnt_cnt-1] = get_x(line_no[pnt_cnt-1], i);
		line_no[pnt_cnt] = i;
	}
	return dp[n];
}
/* End Convex Hull */
