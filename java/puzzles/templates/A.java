import java.util.*;

/**
 *
 * @author Michal Malohlava
 */
public class A<T extends Integer> {

	// type erassure zmeni T na Integer
        T value;
        Collection<Item> l = new LinkedList<Item>();

        public A(T t) {
                this.value = t;
        }

        public void test() {
                System.out.println("this.value = " + value);
        }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                A<Integer> a = new A<Integer>(new Integer(33));

                a.test();
		
	}

        public static class Item {};
}
