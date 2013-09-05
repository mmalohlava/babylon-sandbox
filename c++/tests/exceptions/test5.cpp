/**
 * Polymorfic throw - solution of example test4 
 */
#include <iostream>

using namespace std;

struct ExBase {
	virtual void raise() { throw *this; }
};

struct Ex : public ExBase {
	void raise() { throw *this; };
};

void fce(ExBase &e) {
	e.raise();
}

int main() {
	Ex e;

	try {
		fce(e);
	} catch (Ex & e) {
		cout << "catched(Ex &e)" << endl;
	} catch (...) {
		cout << "catched(...)" << endl;
	}
}
