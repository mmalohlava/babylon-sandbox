/**
 */

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <map>
#include <list>

using namespace std;

void fce() throw() {
	throw 2;
}

void test1() {
	fce();
}

void fce_unexpected() {
	cout << "!!!VYJIMKA!!!" << endl;
	return;
}

void fce_terminate() {
	cout << "TERMINATE CALLED" << endl;
}

int main() {
	set_unexpected(fce_unexpected);
	set_terminate(fce_terminate);

	test1();

	return 0;
}
