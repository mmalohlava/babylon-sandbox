/**
 * Polymorfic throw - bad example
 */
#include <iostream>

using namespace std;

struct ExBase {
};

struct Ex : public ExBase {
};

void fce(ExBase &e) {
	throw e;
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
