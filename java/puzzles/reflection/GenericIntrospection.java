import java.lang.reflect.*;

/**
 *
 * @author Michal Malohlava
 */

class A<T extends Throwable, U extends T> {
        private T value;
}

public class GenericIntrospection {
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                Class<A> clazz = A.class;

                System.out.println("Type parameters for class " + clazz + ":");
                for(TypeVariable tvar : clazz.getTypeParameters()) {
                        System.out.print(tvar);
                        System.out.print(" on ");
                        System.out.print(tvar.getGenericDeclaration());
                        System.out.print(" with upper bounds: ");
                        for(Type typ : tvar.getBounds()) {
                                System.out.print(typ + ",");
                        }
                        System.out.println();
                }
	}
}
