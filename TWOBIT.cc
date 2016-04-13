template <typename T>
class TwoBIT {
private:
	int max_x, max_y, setter;
	vector<vector<T> > tree;
public:
	TwoBIT(int max_x, int max_y): max_x(max_x), max_y(max_y) {
		tree = vector<vector<T> >(max_x, vector<T>(max_y));
	}
	void reset() {
		REP(i,SZ(tree)) {
			REP(j,SZ(tree[i])) {
				tree[i][j] = 0;
			}
		}
	}
	void reset(int m1, int m2) {
		REP(i,m1) {
			REP(j,m2) {
				tree[i][j] = 0;
			}
		}
	}
	T query_y(int x, int y) {
		if(x < 0 || y < 0)	return 0;
		T res = 0;
		while(y >= 0) {
			res = res + tree[x][y];
			if(res >= mod)
				res -= mod;
			y = (y & (y+1)) - 1;
		}
		return res;
	}
	T query(int x, int y) {
		if(x < 0 || y < 0)	return 0;
		T res = 0, temp;
		while(x >= 0) {
			temp = query_y(x, y);
			res = res + temp;
			if(res >= mod)
				res -= mod;
			x = (x & (x+1)) - 1;
		}
		return res;
	}
	T full_query(int x1, int y1, int x2, int y2) {
		LL res = query(x2, y2);
		res -= query(x2, y1-1);
		res -= query(x1-1, y2);
		res += query(x1-1, y1-1);
		return res;
	}
	void update(int x, int y, T val) {
		/* setter = Grid[x][y];
		Grid[x][y] = val; */
		while(x <= max_x) {
			update_y(x, y, val);
			x |= x+1;
		}
	}
	void update_y(int x, int y, T val) {
		/* while(y <= max_y) {
			tree[x][y] += val - setter;
			y |= y+1;
		} */
		while(y <= max_y) {
			tree[x][y] += val;
			y |= y+1;
		}
	}
};
