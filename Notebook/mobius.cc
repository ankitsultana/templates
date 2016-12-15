#define MAXN 100003
int mu[MAXN];
void compute_mu() {
    mu[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if(is_prime[i]) {
            mu[i] = -1;
            for(int j = MAXN/i; j > 1; j--) {
                if(j == i || j*i >= MAXN) continue;
                mu[j*i] = mu[j] * (-1);
            }
        }
    }
}
