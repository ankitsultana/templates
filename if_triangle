template<typename T>
inline bool if_triangle(T x1, T y1, T x2, T y2, T x3, T y3) {
	return abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) != 0;
}

// Given sides, preferably use double/float
template<typename S, typename T>
inline S dist(T x1, T y1, T x2, T y2) {
	S res = sqrt((S) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) );
	return res;
}
template<typename T>
inline bool if_triangle(T a, T b, T c) {
	return (a + b > c) && (b + c > a) && (a + c > b);
}
