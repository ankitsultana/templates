/*	Author: Ankit Sultana
 * * * * * * * * * * * * * * * * */
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#define LL long long
#define PB push_back
#define SWAP(a,b) a=a+b-(b=a)
#define MP make_pair
#define vi vector<int>
#define vll vector<LL>
#define REP(i,n)	for(__typeof(n) i = 0; i < n; i++)
#define REP1(i,n)	for(__typeof(n) i = 1; i <= n; i++)
#define REPc(i,j,n)	for(__typeof(n) i = j; i <= n; i++)
#define F first
#define S second
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define mod 1000000007ll
#define SZ(a) int(a.size())
#define SZll(a) (LL)(a.size())
#define MAXN 10

using namespace std;

template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }
template<typename T> T expo(T b, T e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

LL h[MAXN], c[MAXN], dp[MAXN] = {0};

//	ASSUMPTIONS:
//			c[i] < c[i+1]
//			c[i] != c[i+1]

// Return x coord of intersection point of line i and j
double get_x(int i, int j)
{
	double one = double(double(dp[j])-double(dp[i]));
	double two = double(double(c[i])-double(c[j]));
	double res = double(one)/double(two);
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n;
	// initialise h[i], and c[i]
	// initialise dp[1], dp[2]

	// For storing points
	// stack[i] stores intersection points of line_no[i] & line_no[i+1]
	double stack[MAXN];
	// Size of stack and count of lines
	// in lower envelope
	// line_cnt = pnt_cnt+1 always
	int pnt_cnt = 0, line_cnt = 1;

	// Kind of a mapping, maps line numbers by the
	// appearance in the lower envelope
	int line_no[MAXN] = {0};
	line_no[0] = 1, line_no[1] = 2;

	stack[0] = get_x(line_no[0], line_no[1]);
	pnt_cnt++;
	line_cnt++;
	double x1, x2;
	// Each new line will definitely be added to lower envelope
	// However some lines may have to be removed
	for(int i = 3; i <= n; i++){
		double new_x = double(h[i]);
		int idx = int(upper_bound(stack, stack+pnt_cnt, new_x)-stack);
		// line_no[idx] is the line of lower envelope which intersects with
		// x = new_x
		dp[i] = dp[line_no[idx]]+c[line_no[idx]]*h[i];

		// Keep popping last lines, till
		// x1 > x2 i.e
		// intersection(second last, being added)  > intersection(last, second last)
		// Don't make the stack empty
		// Last line becomes irrelevant
		while(pnt_cnt > 0){
			// find intersection of last two lines
			x2 = stack[pnt_cnt-1];
			// find intersection of second last line and
			// line being currently added
			x1 = get_x(line_no[line_cnt-2], i);
			if(x1 > x2)	break;
			pnt_cnt--;
			line_cnt--;
		}
		// Now insert last line
		stack[pnt_cnt] = get_x(line_no[line_cnt-1], i);
		line_no[line_cnt] = i;
		pnt_cnt++;
		line_cnt++;
	}
	// Answer is dp[n]
	return 0;
}
