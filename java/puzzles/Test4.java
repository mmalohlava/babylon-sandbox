class A {
	int x = 1;
}

class B extends A {
	int x = 2;
}

public class Test4 {

	public static void main(String[] argv) {
		A b = new B();
		System.out.println(b.x);
	}

}
