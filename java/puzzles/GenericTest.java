/**
 *
 * @author Michal Malohlava
 */
public class GenericTest<T extends Object> {
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                Test t = new Test();

                t.test(t, null);
	}

        public void test(T t, Object a) {
                T p = (T) a;
                System.out.println(t);
                System.out.println(p);
        }
}

class Test extends GenericTest<Test> {

}
