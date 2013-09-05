import java.lang.reflect.*;
import java.lang.annotation.*;
import test.*;
import annotations.*;

/**
 *
 * @author Michal Malohlava
 */
public class PackageAnnotation {
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
                Class<Test> clazz = Test.class;

                Package pack = clazz.getPackage();

                System.out.println("Package annotation for '" + pack + "' : ");
                for(Annotation annotation : pack.getAnnotations()) {
                        System.out.println(" - " + annotation);
                }

                Class<PackageAnnotation> clazz2 = PackageAnnotation.class;

                pack = clazz2.getPackage();

                 System.out.println("Package annotation for '" + pack + "' : ");
                for(Annotation annotation : pack.getAnnotations()) {
                        System.out.println(" - " + annotation);
                }
	}
}
