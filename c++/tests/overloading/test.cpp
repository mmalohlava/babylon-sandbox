class A {
public:
	int foo(void) { return 3; };
	float foo(void) {return 4;};
};

class B : public A {
public:
	float foo(void) { return 4; };
};

int main(void) {
	A a;

	int c = a.foo();

	return 1;
}
