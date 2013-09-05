/**
 */

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <map>
#include <list>

using namespace std;
class A {
	public: 
		A() { cout << "A()" << endl ; };
};

class B : public A {
};

class X {
};

void fce() throw (A) {

	throw B();
}

void test1() {
	fce();
}


int main() {
	try {
		test1();
	} catch (X &e) {
		cout << "X catched" << endl;
	} catch (A &e) {
		cout << "B catched" << endl;
	} catch (B & e) {
		cout << "A catched " << endl;
	} catch (...) {
		cout << "... catched" << endl;
	}

	return 0;
}
