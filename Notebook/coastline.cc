#include <iostream>
#include <set>
using namespace std;
// Coastline to keep track of points inside(strictly) coastline
//     |
//     |                Inside
//     x-------|
//             |
//             |
//             x-------|
//                     |
//                     x-------
struct coastline {
    struct pt { // Make this global
        int x, y;
        bool operator<(const pt &other) const {
            return x == other.x ? y < other.y : x < other.x;
        }
    };
    set<pt> s;
    bool inside(int x, int y) {
        if(s.empty())    return false;
        auto it = s.insert({x, y});
        if(it.second == false)  return false; // point already in coastline
        if(it.first == s.begin()) {           // Least point, never inside
            s.erase(it.first); return false;
        }
        auto jt = prev(it.first);
        s.erase(it.first);
        // Check with previous element
        if(jt->x == x) {
            if(jt == s.begin()) {
                return false;
            } else {
                return prev(jt)->y < y;
            }
        }
        return jt->y < y;
    }
    void insert(int x, int y) {
        if(inside(x, y))    return ;
        s.insert({x, y});
        // Adjust coastline now
        auto jt = s.find({x, y});
        jt = next(jt);
        while(jt != s.end()) {
            auto temp = next(jt);
            if(jt->y >= y) {
                s.erase(jt);
            } else {
                break;
            }
            jt = temp;
        }
        jt = s.find({x, y});
        // If current lies ON coastline
        if(jt != s.begin() and prev(jt)->x == x) {
            s.erase(jt);
        } else if(jt != s.begin() and prev(jt)->y == y) {
            s.erase(jt);
        }
    }
    friend ostream& operator<<(ostream &os, coastline &crap) {
        for(auto &elem: crap.s) {
            os << "(" << elem.x << ", " << elem.y << ") ";
        }
        return os;
    }
    inline bool empty() { return s.empty(); }
};
