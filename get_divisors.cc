vector<int> divs(int x) {
    vector<int> res;
    for(int i = 2; i*i <= x; i++) {
        if(x % i == 0) {
            res.push_back(i);
            if(i*i != x) {
                res.push_back(x/i);
            }
        }
    }
    sort(res.begin(), res.end());
    return res;
}
