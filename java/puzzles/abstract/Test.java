interface If {
	void bar();
}

//abstract class A implements If {
abstract class A {
	public void foo() {System.out.println("foo() called"); }
	//public abstract void bar(int i);
};

public class Test extends A {
	public static void main(String[] args) {
		Test t = new Test();
		t.foo();
	}

}
