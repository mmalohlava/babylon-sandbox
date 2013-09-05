package cz.cuni.mff.java.reflect;

import java.lang.reflect.*;

public class Introspector {

  public static void main(String[] args) throws Exception {
    Class cls = Class.forName(args[0]);

    System.out.println("Name:         "+cls.getName());
    System.out.println("is primitive: "+cls.isPrimitive());
    System.out.println("is array:     "+cls.isArray());
    System.out.println("is interface: "+cls.isInterface());
    System.out.println("package:      "+cls.getPackage());
    System.out.println("superclass:   "+cls.getSuperclass());
    System.out.print("interfaces:   ");
    Class[] ifaces = cls.getInterfaces();
    for (int i=0; i<ifaces.length; i++) System.out.print(ifaces[i].getName()+", ");
    System.out.println();

    System.out.println("methods:");
    Method[] mt = cls.getMethods();
    for (int i=0; i<mt.length; i++) System.out.println("  " + mt[i]);
    System.out.println();

    System.out.println("declared methods");
    mt = cls.getDeclaredMethods();
    for (int i=0; i<mt.length; i++) System.out.println("  " + mt[i]);
    System.out.println();

    System.out.println("fields:");
    Field[] ft = cls.getFields();
    for (int i=0; i<ft.length; i++) System.out.println("  " + ft[i]);
    System.out.println();

    System.out.println("declared fields:");
    ft = cls.getDeclaredFields();
    for (int i=0; i<ft.length; i++) System.out.println("  " + ft[i]);
    System.out.println();

    System.out.println("constructors:");
    Constructor[] ct = cls.getConstructors();
    for (int i=0; i<ct.length; i++) System.out.println("  " + ct[i]);
    System.out.println();

    System.out.println("declared constructors:");
    ct = cls.getDeclaredConstructors();
    for (int i=0; i<ct.length; i++) System.out.println("  " + ct[i]);
    System.out.println();

    if (args[1].equals("i")) {
      System.out.println();
      System.out.println("new instance...");
      Object obj = cls.newInstance();
      System.out.println(obj);

      System.out.println();
      System.out.println("invoking method foo(long, boolean)");
      Class[] params = { long.class, boolean.class };
      Method foo = null;
      try {
        foo = cls.getMethod("foo", params);
      } catch (Exception e) {
        System.out.println("no such method");
        System.exit(0);
      }
      Object[] p = { new Long(10L), new Boolean(true) };
      System.out.println("Result: "+foo.invoke(obj, p));
      
      
    }

  }
  
}
