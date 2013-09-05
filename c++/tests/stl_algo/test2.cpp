/**
 * Test of STL algorithm
 */
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

using namespace std;

struct Generator {
	static int i;
	string operator()() {
		ostringstream os ;
		os << "A" << i++;
		return os.str();
	}
};
int Generator::i = 1;

struct Gen2 {
	int operator()() {
		//return std::rand();
		return 1;
	}
};


class Trans1 {
	public:
		void operator() (string & a) {
			a.append("!");
		}
};
void test1() {
	vector<string> a(10);
	vector<string> b;

	a.push_back("A");
	a.push_back("B");
	generate(a.begin(), a.end(), Generator() );

	next_permutation(a.begin(), a.end());
	random_shuffle(a.begin(), a.end());
	sort(a.begin(), a.end());

	//transform(a.begin(), a.end(), back_inserter(b), bind2nd(plus<string>(), "!") );
	for_each(a.begin(), a.end(), Trans1() );

	cout << endl << "A:";
	copy(a.begin(), a.end(), ostream_iterator<string>(cout, " - "));
	cout << endl << "B:" ;
	copy(b.begin(), b.end(), ostream_iterator<string>(cout, " - "));
	cout << endl;
}

void test2() {
	vector<int> a;

	generate_n(back_inserter(a),10, Gen2());
	
	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " | "));

	int count = 0;
	cout << endl << "Result: " << accumulate(a.begin(), a.end(), count) << endl;
}

int main() {
	test2();

	return 0;
}
