template<typename T>
string toString(T x) {
	if(x == 0)	return "0";
	string result;
	while(x){
		result.PB(char(x%10+48));
		x /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}
