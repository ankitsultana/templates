#include <iostream>
#include <vector>
using namespace std;

/*
 * Convex Hull Constrained
 * Constrain being that the slopes should be strictly increasing/decreasing
 */

template<typename T>
struct HullConstrained {
    struct Line {
        T m, c;
        Line() { }
        Line(T m, T c) : m(m), c(c) { }
    };
    HullConstrained() { }
    HullConstrained(int sz) {
        pts.reserve(sz), lines.reserve(sz);
    }
    void insert(Line x) {
        if(lines.size() <= 1) {
            lines.push_back(x);
            if(lines.size() == 2) {
                pts.push_back(get_x(lines[0], lines[1]));
            }
            return ;
        }
        double curr_x = get_x(x, lines.back());
        while(pts.size() > 0 and pts.back() >= curr_x) {
            lines.pop_back(), pts.pop_back();
            curr_x = get_x(x, lines.back());
        }
        lines.push_back(x);
        if(lines.size() > 1) pts.push_back(curr_x);
    }
    T eval(T x) {
        int idx = int(lower_bound(pts.begin(), pts.end(), x) - pts.begin());
        return lines[idx].c + lines[idx].m * x;
    }
    inline bool empty() { return lines.empty(); }
private:
    vector<double> pts;
    vector<Line> lines;
    double get_x(Line &l, Line &r) {
        return double(l.c - r.c) / double(r.m - l.m);
    }
};
