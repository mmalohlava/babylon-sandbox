import java.io.*;

/**
 *
 * @author Michal Malohlava
 */
public class TestStdIORedirect {
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) throws FileNotFoundException {
        PrintStream fos = new PrintStream(new FileOutputStream(new File("test.txt")));
        System.setOut(fos);
        System.setErr(fos);

        System.out.println("Thi is an OUT test");
        System.err.println("Thi is an ERR  test");

        fos.close();
	}
}
