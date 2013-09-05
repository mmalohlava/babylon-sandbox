#include <iostream>

using namespace std;

class A {
	public:
		A(int ii):i(ii) { cout << "A() throwing exception" << endl; throw 20; };
		int i;
};

class B : public A {
	public: 
		B() 
			try 
				: A(3) 
			{ cout << "B()" << endl; }
			catch (int)
				{ cout << "ctor A() exc. catched()" << endl; } 
	
};
int main() {
	try {
		B b;
	} catch (int) {
		cout << "Exc. catched..." << endl;
	}
}
