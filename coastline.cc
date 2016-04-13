/* Coastline */
struct point {
	LL x, y;
	int idx;
	bool operator<(const point &other) const {
		if(x != other.x) {
			return x < other.x;
		}
		if(y != other.y) {
			return y > other.y;
		}
		return idx > other.idx;
	}
}points[MAXN], temp_points[MAXN];
set<point> coastline;

bool inside(point x)
{
	set<point>::iterator it;
	it = lower_bound(coastline.begin(), coastline.end(), x);
	if(it == coastline.end()) {
		return false;
	}
	return it->y >= x.y;
}

/* ----*
       |
	   |	outside
	   -----*
	inside	|
			|
			|
			----*
				|
				|
				|
*/

void myInsert(point x)
{
	if(coastline.empty()) {
		coastline.insert(x);return ;
	}
	if(inside(x)) {
		return ;
	}
	coastline.insert(x);
	set<point>::iterator it = coastline.find(x), jt;
	if(it == coastline.begin())	return ;
	it--;
	while(it->y <= x.y) {
		if(it == coastline.begin()) {
			coastline.erase(it); break;
		}
		jt = --it, it++;
		coastline.erase(it);
		it = jt;
	}
}
/* Coastline end */
