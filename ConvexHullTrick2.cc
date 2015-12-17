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
#define MAXN 102

using namespace std;

template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }
template<typename T> T expo(T b, T e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

int dp[MAXN][MAXN] = {0};

// "Slope" of the line
int c[MAXN] = {0};

// x coordinate at which you need to evaluate
int h[MAXN] = {0}, n;

// Get x coordinate of intersection of lines i and j
double get_x(int depth, int i, int j)
{
	double one = double(double(dp[depth][j])-double(dp[depth][i]));
	double two = double(double(c[i])-double(c[j]));
	double res = double(one)/double(two);
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	// initialise dp[0][x] for all x
	int height, width;
	REP1(i,height){
		// Compute dp[i][1], dp[i][2] first
		// 			=====
		// End Computation
		double stack[MAXN];
		int pnt_cnt = 0, line_cnt = 1;

		int line_no[MAXN] = {0};
		line_no[0] = 1, line_no[1] = 2;

		// Insert lines 1 and 2
		stack[0] = get_x(i-1, line_no[0], line_no[1]);
		line_cnt++, pnt_cnt++;

		double x1, x2;
		REPc(j,3,width){
			double new_x = double(h[j]);
			int idx = int(upper_bound(stack, stack+pnt_cnt, new_x)-stack);
			dp[i][j] = dp[i-1][line_no[idx]]+c[line_no[idx]]*h[j];

			while(pnt_cnt > 0){
				x2 = stack[pnt_cnt-1];
				x1 = get_x(i-1, line_no[line_cnt-2], j);
				if(x1 > x2)	break;
				pnt_cnt--, line_cnt--;
			}
			stack[pnt_cnt] = get_x(i-1, line_no[line_cnt-1], j);
			line_no[line_cnt] = j;
			pnt_cnt++, line_cnt++;
		}
	}
	return 0;
}
