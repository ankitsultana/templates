template<typename T>
class BIT {
private:
	vector<T> bit;
	int n;
public:
	BIT(int n): n(n) {
		bit.resize(n+1);
	}
	void reset() {
		for(int i = 0; i <= n; i++)	bit[i] = 0;
	}
	void update(int u, T v) {
		while(u <= n) {
			bit[u] = bit[u] + v;
			if(bit[u] >= mod)
				bit[u] -= mod;
			u |= u+1;
		}
	}
	T query(int u) {
		if(u < 0) { return 0; }
		T res = 0;
		while(u >= 0) {
			res = res + bit[u];
			if(res >= mod)	res -= mod;
			u = (u & (u+1)) - 1;
		}
		return res;
	}
};

