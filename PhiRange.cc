int phi[MAXN];

void precomp_phi() {
    phi[1] = 1;
    for(int i = 1; i < MAXN; i++){
        if(phi[i] == 0){
            for(int j = i*2; j < MAXN; j+=i){
                if(phi[j] == 0)	phi[j] = j;
                phi[j] = (phi[j]/i)*(i-1);
            }
        }
    }
    for(int i = 1; i < MAXN; i++) {
        if(phi[i] == 0) phi[i] = i-1;
    }
}
