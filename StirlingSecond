LL S[MAXN][MAXN] = {0}, n;
void stirling_second_kind()
{
	S[0][0] = 1;
	REP(i,MAXN){
		if(i == 0)	continue;
		REP1(k,i){
			S[i][k] = (((k*S[i-1][k])%mod)+S[i-1][k-1])%mod;
		}
	}
}
