/**
 * Generic template method.
 *
 * @type T concrete implementation
 *
 * @author Michal Malohlava
 */
public abstract class GTMethod<T extends PrimitiveImpl> {
	
        /**
         * Method defining template.
         *
         * Implementation can be changed via generic type IMPL
         */
        public final void templateMethod() {
                System.out.println("Calling the first primitive method implementation...");
                primitiveMethodAImpl();
                
                System.out.println("Calling the second primitive method implementation...");
                primitiveMethodBImpl();
        }

        private void primitiveMethodAImpl() {
                ((T) this).primitiveMethodA();
        }

        private void primitiveMethodBImpl() {
                ((T) this).primitiveMethodB();
        }

	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                ConcreteImpl gtMethod = new ConcreteImpl();

                gtMethod.templateMethod();
		
	}
}

class ConcreteImpl extends GTMethod<ConcreteImpl> implements PrimitiveImpl {
                public void primitiveMethodA() {
                        System.out.println("Primitive method A");
                }

                public void primitiveMethodB() {
                        System.out.println("Primitive method B");
                }
 
}

