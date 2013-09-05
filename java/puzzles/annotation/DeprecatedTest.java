/**
 *
 * @author Michal Malohlava
 */
public class DeprecatedTest {
	
        	public static final void main(String[] argv) {

                A a = new A();
                a.deprecatedMethod(null);		
	}
}

class A {
  public static void deprecatedMethod( I  a ) {
  }
}

@Deprecated
interface I {}

