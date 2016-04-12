/*
 * Geometry Crap
 */
template<typename T>
struct pt {
    T x, y;
    friend std::ostream& operator<<(std::ostream &os, const pt &x) {
        os << "(" << x.x << ", " << x.y << ")";
        return os;
    }
};

// area of triangle formed by three points (a, b, c)
template<typename T>
T area_of_triangle(pt<T> a, pt<T> b, pt<T> c) {
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
}

// check if (a, b, c) are collinear
template<typename T>
bool collinear(pt<T> a, pt<T> b, pt<T> c) {
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) == 0;
}

// check if x lies on the line segment a -- b
template<typename T>
bool on_segment(pt<T> a, pt<T> b, pt<T> x) {
    if(x.x <= max(a.x, b.x) and x.x >= min(a.x, b.x) and
            x.y <= max(a.y, b.y) and x.y >= min(a.y, b.y)) {
        return collinear(a, b, x);
    }
    return false;
}

// 0  -> collinear
// 1  -> counter clockwise
// -1 -> clockwise
template<typename T>
int orientation(pt<T> p, pt<T> q, pt<T> r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if(val == 0)    return 0;
    return val > 0 ? -1: 1;
}

// check if p1q1 and p2q2 intersect
template<typename T>
bool segments_intersect(pt<T> p1, pt<T> q1, pt<T> p2, pt<T> q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 and o3 != o4)  return true;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;
    return false;
}

// return true if x lies inside polygon
template<typename T>
bool pip(pt<T> x, pt<T> polygon[], int n) {
    if(n < 3)   return false;
    bool c = false;
    for(int i = 0, j = n-1; i < n; j = i++) {
        if((polygon[i].y > x.y) != (polygon[j].y > x.y) &&
            (x.x < (polygon[j].x - polygon[i].x) * (x.y - polygon[i].y) /
                (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            c = !c;
        }
    }
    // return c;  // Uncomment if boundary ==> not inside
    if(c)   return true;
    for(int i = 0, j = n-1; i < n; j = i++)
        if(on_segment(polygon[j], polygon[i], x))
            return true;
    return false;
}

/*
 * Geometry Crap Ends
 */
