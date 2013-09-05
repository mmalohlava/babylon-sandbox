/**
 *
 * @author Michal Malohlava
 */
public class ThrowR {

    public static boolean test() {
        try {
              return true;
        } finally {
              return false;
        }
    }

    public int numbers() [] {
          return null;
    }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
        System.out.println(test());

	}
}
