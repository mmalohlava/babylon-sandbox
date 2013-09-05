import java.util.*;
class Book {
	Book() { System.out.println("Book()"); }
	String name;
};
public class Test3 {
	private void test() {
		int [][] a = new int[2][2];
		//int a = new int[2][2];
		//int[2] a = new int[2][2];
		//int [2] a = new int[2,2];

	}

	private void test2() {
		Thread t;
		boolean b = true;

		if (b) {
			System.out.println("A");
		} else {
			System.out.println("B");
		}
	}

	public synchronized void foo() {
		System.out.println("Hello");
	}

	public synchronized void bar(int i) {
		if (i==0) {
			bar(1);
		} else {
			System.out.println("done");
		}
	}

	public static void main(String[] argv){
		Test3 t = new Test3();

		t.bar(1);

		int[] a = new int[3];

		System.out.println(a.length);
		Collection<Integer> z = new LinkedList<Integer>();
		Integer[] b = z.toArray(new Integer[0]);

		Book[] books = new Book[4];

		books[3].name = "aaa";
	}
}
	
