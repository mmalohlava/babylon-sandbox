package puzzles;

/**
 *
 * @author Michal Malohlava
 */
public class A {

    void test() {
        EventSource es = new EvilEventSource();
        ThisEscape te = new ThisEscape(es);
    }
	
	/**
	 * Main.
	 */
	public static final void main(String[] argv) {
        A a = new A();
        a.test();
	}

    interface EventListener {
        void onEvent(Event e);
    }

    interface Event {
    }

    interface EventSource {
        void registerListener(EventListener el);
    }

    class EvilEventSource implements EventSource {
        public void registerListener(EventListener el) {
           System.out.println("This (evilEvetSource) = " + el.ThisEscape.this);
        }
    }

    class ThisEscape {
        public ThisEscape(A es) {
            es.registerListener(new EventListener() {
                public void onEvent(Event e) {
                    doSomething(e);
                }
            });
        }

        protected void doSomething(Event e) {
           System.out.println("This (doSomething) = " + this);
        }
    }

}
