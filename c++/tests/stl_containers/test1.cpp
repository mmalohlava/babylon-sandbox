/**
 * STL test
 */

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <map>
#include <list>

using namespace std;

void test_multimap() {
	multimap<int, string> mmap;
	multimap<int, string>::iterator it;

	mmap.insert(pair<int, string>(3,"2"));
	mmap.insert(pair<int, string>(3,"ahoj"));
	mmap.insert(make_pair(4,"2"));

	for(it = mmap.begin(); it != mmap.end(); ++it ) {
		cout << (*it).first;
	}

	cout << "Searching:" << endl;
	it = mmap.find(3);

	while (it != mmap.end()) {
		cout << it->second;
		it++;
	}
	cout << endl << "end of search" << endl;
}

void test_set() {
	list<string> ll;
	vector<string> vv;

	ll.push_back("A");
	ll.push_front("B");

	vv.push_back("a");
	//vv.push_front("B");
}

void test_map() {
	map<int, string> mm;
	map<int, string>::iterator it;

	mm[3] = "ahoj";
	mm[3] = "cau";

	for(it = mm.begin(); it != mm.end(); ++it) {
		cout << it->second << endl;
	}


}

int main(char ** argv) {

	test_multimap();

	test_map();

	return 0;
}
