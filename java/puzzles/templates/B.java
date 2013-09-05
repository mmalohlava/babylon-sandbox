import java.util.Iterator;

/**
 *
 * @author Michal Malohlava
 */
public class B {

    public static <T> TreeIterator<T> getTreeIt() {
        return null;
    }

    public static interface TreeIterator<E> extends Iterator<E> {
    }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
        Iterable<? extends B> list = new Iterable<? extends B>() {
            public Iterator<? extends B> iterator() {
                return (Iterator<? extends B>) getTreeIt();
            }
        };


		
	}
}
