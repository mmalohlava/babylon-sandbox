/**
 * RTTI example
 */
#include <iostream>
#include <vector>

using namespace std;

class IFace {
	public:
		virtual void print() = 0;
};

class Derived : public IFace {
	public:
		void print() { cout << "Derived::print()" << endl; };
		void printA() { cout << "Derived::printA()" << endl; };
};

class DerivedDevil : public IFace {
	public:
		void print() { cout << "Derived::print()" << endl; };
		void printDevil() { cout << "Derived::printDevil()" << endl; };
};

void example() {
	vector<IFace *> v;
	Derived der1;
	DerivedDevil der2;
	v.push_back(&der1);
	v.push_back(&der2);

	cout << "EXAMPLE 1" << endl;
	
	vector<IFace *>::iterator it;	
	for(it = v.begin(); it != v.end(); it++) {
		cout << "-----" << endl;
		IFace* iface = *it;
		cout << "typeid(o) =" << typeid(*iface).name() << endl;
		iface->print();
		
		Derived *d = dynamic_cast<Derived *>(iface);
		if (d != NULL) {
			cout << " - dynamic cast to Derived succeded" << endl;
			d->printA();
		} else {	
			cout << " - dynamic cast to Derived failed" << endl;
		}

		if (typeid(*iface) == typeid(Derived)) {
			cout << "This is Derived" << endl;
		} else if (typeid(*iface) == typeid(DerivedDevil)) {
			cout << "This is DerivedEvil" << endl;
		}
		cout << "-----" << endl;
	}

	cout << "end of EXAMPLE 1" << endl;
}

struct Base1 {
	Base1():i(666) {};
	void print() { cout << "This is Base1" << endl; };
	virtual ~Base1() {};
	int i;
};

struct Base2 {
	Base2(): bb(true) {};
	void print() { cout << "This is Base2, bb=" << bb << endl; };
	bool bb ;
};

struct D : public Base1, public Base2 {
};
void example2() {
	cout << endl << "---------------" << endl << "EXAMPLE 2" << endl;
	Base1 base1;
	D d;

	cout << "Base1 base -> typeid = " << typeid(base1).name() << endl;
	cout << "D d -> typeid = " << typeid(d).name() << endl;
	cout << "typeid(D) = " << typeid(D).name() << endl;

	Base1* b = dynamic_cast<Base1 *>(&d);
	cout << "After dynamic_cast: typeid(b) =" << typeid(b).name() << endl;
	cout << "After dynamic_cast: typeid(*b) =" << typeid(*b).name() << endl;
	
	cout << "end of EXAMPLE 2" << endl;
}

void example3() {
	cout << endl << "---------------" << endl << "EXAMPLE 3" << endl;

	D d;
	Base1 *pbase1 = &d;
	// aby tohle proslo musi byt source (pbase1) polymorphic
	Base2 *pbase2 = dynamic_cast<Base2*>(pbase1);
	pbase2->print();

	// spatne
	Base2 *pbase2bad = (Base2 *) pbase1;
	pbase2bad->print();

	
	cout << "end of EXAMPLE 3" << endl;
}
int main() {
	example();
	example2();
	example3();

	return 0;
}

