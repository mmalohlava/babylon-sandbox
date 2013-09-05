/**
 *
 * @author Michal Malohlava
 */
public class OsArch {
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
	    System.out.println("os.arch = " + System.getProperty("os.arch"));
	    System.out.println("sun.arch.data.model = " + System.getProperty("sun.arch.data.model"));
	}
}
