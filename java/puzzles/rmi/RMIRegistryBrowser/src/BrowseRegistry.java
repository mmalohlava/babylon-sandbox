import java.rmi.*;
import java.rmi.registry.*;

public class BrowseRegistry {

  public static void main(String[] argv) throws Exception {
    String host = argv.length == 0 ? "localhost" : argv[0];
    String port = argv.length <= 1 ? "1099" : argv[1];
    Registry reg = LocateRegistry.getRegistry(host, Integer.parseInt(port));
    String[] objs = reg.list();
    if (objs.length == 0) {
      System.out.println("Zadne objekty nejsou zaregistrovany");
      System.out.println("===================================");
    } else {
      for (int i=0; i<objs.length; i++) {
        System.out.println(objs[i]);
      }
    }
  }
}
