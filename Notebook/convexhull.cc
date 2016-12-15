struct point {
    LL x, y, idx;
    bool operator<(const point &other) const {
        return y == other.y ? x < other.x: y < other.y;
    }
};
LL cross(point o, point a, point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

template<typename iter>
vector<point> convex_hull(iter f, iter e) { // creates convex hull for range [f, e)
    if(e == f) return {};
    else if(int(e - f) == 1) {
        return { *f };
    }
    int n = int(e - f);
    vector<point> hull(2*n);
    sort(f, e);
    int k = 0;
    iter temp;
    for(temp = f; temp != e; temp++) { // lower hull
        while(k >= 2 && cross(hull[k-2], hull[k-1], *temp) <= 0)
            k--;
        hull[k++] = *temp;
    }
    e--, temp = e, e++;
    int t = k;
    do {
        temp--;
        while(k > t && cross(hull[k-2], hull[k-1], *temp) <= 0) k--;
        hull[k++] = *temp;
    } while(temp != f);
    hull.resize(k - (k > 1));
    return hull;
}
