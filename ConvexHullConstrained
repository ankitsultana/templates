/* Start Convex Hull (Constrained) */
#define MAXN 1000003
struct Line {
	LL m, c;
	int idx;
}lines[MAXN];

LL dp[MAXN];
double stack[MAXN];
int line_no[MAXN] = {0};

struct HullConstrained {
private:
	bool upper;
	int pnt_cnt, line_cnt;
public:
	HullConstrained(string upper) {
		this->upper = upper == "upper";
		pnt_cnt = 0, line_cnt = 0;
	}
	void insert(Line x) {
		if(line_cnt == 0) {
			line_no[0] = x.idx, line_cnt++;return ;
		}
		if(line_cnt == 1) {
			if(lines[line_no[0]].m == x.m) {
				if(upper && lines[line_no[0]].c < x.c)
					line_no[0] = x.idx;
				else if(!upper && lines[line_no[0]].c > x.c)
					line_no[0] = x.idx;
			} else {
				line_no[1] = x.idx, line_cnt++;
				stack[0] = get_x(lines[line_no[0]], lines[line_no[1]]);
				pnt_cnt++;
			}
			return ;
		}
		double x1 = get_x(lines[line_no[pnt_cnt-1]], lines[x.idx]), x2 = stack[pnt_cnt-1];
		while(pnt_cnt > 0 && x1 <= x2) {
			x2 = stack[pnt_cnt-1]; 
			x1 = get_x(lines[line_no[pnt_cnt-1]], lines[x.idx]);;  
			if(x1 > x2)	break;
			pnt_cnt--, line_cnt--;
		}
		pnt_cnt++, line_cnt++;
		stack[pnt_cnt-1] = get_x(lines[line_no[pnt_cnt-1]], lines[x.idx]);
		line_no[pnt_cnt] = x.idx;
	}
	double get_x(Line &l, Line &r) {
		return double(r.c - l.c)/double(l.m - r.m);
	}
	LL eval(LL curr_x) {
		int idx = int(lower_bound(stack, stack + pnt_cnt, double(curr_x)) - stack);
		return lines[line_no[idx]].c + lines[line_no[idx]].m*(LL)curr_x;
	}
};
/* End */
