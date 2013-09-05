import java.lang.reflect.*;

/**
 *
 * @author Michal Malohlava
 */
public class EnumIntrospection {

        // Simple enum
        enum LifecycleEnum {
                STARTING (1),
                STARTED  (2),
                STOPPING (4),
                STOPPED  (8);

                private int code;

                // cannot be public !
                LifecycleEnum(int c) {
                        this.code = c;
                }
        }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                Class<LifecycleEnum> clazz = LifecycleEnum.class;

                // is clazz represents enum type?
                System.out.println("isEnum() = " + clazz.isEnum());
                LifecycleEnum[] enumElements = clazz.getEnumConstants();

                // introspect declaration of enum
                System.out.println("\nEnum has " + enumElements.length + " constants:");

                for(LifecycleEnum element : enumElements) {
                        System.out.println(" - " + element);
                }

                System.out.println("\nInternal fields of enum:");

                Field[] fields = clazz.getDeclaredFields();

                for (Field field : fields) {
                        showField(field);
                }
	}

        public static final void showField(Field f) {
                System.out.println(f.toGenericString());
        }
}
