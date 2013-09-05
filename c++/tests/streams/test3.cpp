#include <iostream>

using namespace std;

template<typename T, typename C>
class manip_comma {
public:
	manip_comma(basic_ostream<C>& (*pFun) (basic_ostream<C> &,T), T val): _x(val), manip_fce(val) {};

	void operator() (basic_ostream<C>& os) const {
		manip_fce(os, _x);
	}
private:
	T _x;
	basic_ostream<C>& (*manip_fce)(basic_ostream<C>&,T);
};

template<typename T, typename C>
basic_ostream<C> & operator<<(basic_ostream<C> & os, const manip_comma<T,C>& manip) {
	manip(os);

	return os;
}

ostream & comma_func(ostream & os, int n) {
	os << "____----____";

	return os;
}

manip_comma<int, char> func_comma(int n) {
	return (manip_comma<int, char>((ostream&(*)(ostream&, int))(&comma_func), n));
}

int main() {
	cout << func_comma(5);

	return 0;
}
