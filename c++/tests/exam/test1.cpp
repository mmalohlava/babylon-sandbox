#include <iostream>
#include <vector>

using namespace std;

void test(vector<int> &v) {

	vector<int>::iterator it;
	it = find(v.begin(), v.end(), 0);
	it = v.insert(it+1, 1);
	v.insert(it-1, -1);
}

int main(void) {
return 0;
}
