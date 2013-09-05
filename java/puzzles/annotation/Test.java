@Clazz(
	name="Test",
	methods={
			@Method(result="void",name="test"),
			@Method(result="int",name="help")
	}
)
public class Test {
		public void test() {};
		public int help() { return 0; };
}
