/**
 * Exception in dtor.
 */
#include <iostream>

using namespace std;

class A {
public:
	void print() { cout << "A.print()" << endl ; };
	~A() { cout << "~A()" << endl; throw 20; };
};

int fce() {
	A a;

	a.print();

	throw 21;

}

int main() {
try {
	fce();
} catch (int) {
	cout << "catched()" << endl;
}
}
