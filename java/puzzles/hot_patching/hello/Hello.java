/**
 * Simple hello world.
 *
 * @author Michal Malohlava
 */
public class Hello {

    public static String HELLO_STRING = "Hello w#!.ld";
	private Class printerClass;
	public Hello(Class pc) { this.printerClass = pc; } 

        public void run() throws Exception {
                while(true) {
                        Printer printer = (Printer) printerClass.newInstance();
                        printer.print(HELLO_STRING);
                        try {
                                Thread.sleep(1500);
                        } catch (InterruptedException _) {}
                }
        }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) throws Exception {
                Hello h = new Hello(Printer.class);
		
		Printer p = new Printer();
		
                h.run();
		p.print("This is the end");

	}
}
