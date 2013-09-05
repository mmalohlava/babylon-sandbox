import java.lang.instrument.*;
import com.sun.tools.attach.*;

/**
 *
 * @author Michal Malohlava
 */
public class Attach {
	
	/**
	 * Main.
	 */
	public static final void main(String[] args) {

                try {
                if (args.length != 3) {
                        printHelp();
                        return;
                }

	        VirtualMachine vm = VirtualMachine.attach(args[0]);	

                 vm.loadAgent(args[1], args[2]);
                } catch (Exception e) {
                        System.out.println("Vyjimka:");
                        e.printStackTrace();
                }
	}

        public static void printHelp() {
                System.out.println("Parameters: <java-id> <agent-jar> <path-to-redefined-class>");
        }
}
