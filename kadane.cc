template<typename T, typename iter>
T kadane(iter l, iter r) {
    T INF = std::numeric_limits<T>::lowest();
    if(l == r)  return INF;
    T pos = 0, maxim = *l;
    for(iter temp = l; temp != r; temp++) {
        if(*temp > 0)
            pos += *temp;
        maxim = max(maxim, *temp);
    }
    if(pos == 0)    return maxim;
    iter one = l, two = l;
    T res = INF, temp = 0;
    while(two != r) {
        temp += *(two++);
        if(temp < 0) {
            while(one < two && temp < 0) {
                temp -= *(one++);
            }
        }
        res = max(res, temp);
    }
    return res;
}
