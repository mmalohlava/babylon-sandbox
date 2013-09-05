package cz.s-a.ten;

public class Parent {
    public static void main(String[] args) {
         System.out.println("Hi I am Parent Class main!!");
    }
}
 
class Child extends Parent {
    public static void main(String[] args) {
        super.main();
        System.out.println("Hi I am ChildClass main !");
    }
} 
