/**
 * Zavola se intova metoda, v C# se zavola float.
 * @author Michal Malohlava
 */
public class B {
    class X {
        public void m(int n) {
            System.out.println("Int Value : " + n);
        }
    }

    class Y extends X {
        public void m(float n) {
            System.out.println("Float Value : " + n);
        }
    }

    public void test() {
        Y y = new Y();

        y.m(3);
    }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
        B b = new B();

        b.test();
		
	}
}
