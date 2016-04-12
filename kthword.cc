string kthword(LL k)
{
	string res;  
	for(; k > 0; k = (k-1)>>1) {
		res.push_back(alphabet[(k-1)%2]);  
	}
	return res;
}
