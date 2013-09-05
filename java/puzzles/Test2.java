/**
 *
 */

class Root {
	public String getName() { return "ROOT" ; }
};

class Node extends Root {
	public String getName() { return "NODE"; }
}

public class Test2 {

	public static final void main(String[] args) {

		Root r = new Root() ;
		Node n = new Node() ;

		System.out.println("Result n: " + n.getName());
		System.out.println("Result r: " + r.getName());
		r = n;
		System.out.println("r = n;");
		System.out.println("Result r: " + r.getName());
	}
}
