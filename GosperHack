int next_set(int mask)
{
	int c = mask & -mask;
	int r = mask + c;
	mask = (((mask^r)>>2) / c) | r;
	return mask;
}
