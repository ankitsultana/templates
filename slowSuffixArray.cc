#define MAXN 10003
#define MAXLOGN 19
/*  Build: O(n*log2(n)*log2(n))
 *  LCP:   O(log2(n))
 *  Case:  Lower
 * * * * * * * * * * * * */
struct suffix_array {
	int sa[MAXN][MAXLOGN], size;	// sa[i][log] is position of i-th suffix in lex order
	int arr[MAXN], log;	// arr[i] is the suffix at position i
	int sizess[MAXN];
	bool lower_case;
	string s;
	suffix_array(string s, bool lower_case = true): s(s), log(0) {
		this->size = s.size();
		this->lower_case = lower_case;
		preprocess();
	}
	void preprocess() {
		for(int i = 0; i < size; i++)	sa[i][0] = s[i] - (lower_case?'a': 'A');
		int cnt = 1;
		log = 0;
		for(int k = 1; (cnt >> 1) < size; k++, log++, cnt <<= 1) {
			for(int i = 0; i < size; i++)
				events[i] = {sa[i][k-1], i + cnt < size?sa[i+cnt][k-1]: -1, i};
			sort(events, events + size);
			for(int i = 0; i < size; i++) {
				if(i > 0 && events[i].a == events[i-1].a && events[i].b == events[i-1].b) {
					sa[events[i].idx][k] = sa[events[i-1].idx][k];
				} else {
					sa[events[i].idx][k] = i;
				}
			}
		}
		for(int i = 0; i < size; i++) {
			arr[sa[i][log]] = i;
			sizess[sa[i][log]] = size - i;
		}
	}
	int lcp(int x, int y) {		// of [x..n) and [y..n)
		if(x > y)	swap(x, y);
		int res = 0;
		for(int i = log; i > -1; i--) {
			if(sa[x][i] == sa[y][i]) {
				res += min(1<<i, min(size - y, size - x));
				x += 1<<i, y += 1<<i;
				if(x >= size || y >= size)	break;
			}
		}
		return res;
	}
	struct event {
		int a, b, idx;
		bool operator<(const event &other) const {
			return a == other.a?b < other.b: a < other.a;
		}
	}events[MAXN];
	void printer() {
		for(int i = 0; i < size; i++) {
			cout << arr[i] << ' ';
		} cout << endl;
	}
	void solve() {
		int res = size - arr[0];
		for(int i = 1; i < size; i++) {
			int l = lcp(arr[i], arr[i-1]);
			res += sizess[i] - l;
		}
		cout << res << '\n';
	}
};
