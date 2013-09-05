import java.io.*;
import java.lang.instrument.*;

public class HotPatchAgent {
    public static void agentmain(String agentArgs, Instrumentation inst)
    {
        try
        {
            System.out.println("Redefining Hello class ...");
            File f = new File(agentArgs);
	    System.out.println(f.getAbsolutePath() + " length = " + f.length());

            byte[] fixedHelloClassFile = new byte[(int) f.length()];
            DataInputStream in = new DataInputStream(new FileInputStream(f));
            in.readFully(fixedHelloClassFile);
            in.close();

            ClassDefinition helloDef = 
                new ClassDefinition(Class.forName("Printer"), fixedHelloClassFile);
            inst.redefineClasses(helloDef);
            System.out.println("Redefined Hello class");
        }
        catch(Exception e)
        {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}


