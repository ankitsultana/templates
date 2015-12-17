template<typename T>
T extendedeuclid (T a, T b, T & x, T & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	T x1, y1;
	T d = extendedeuclid (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
