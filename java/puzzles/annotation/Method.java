import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
public @interface Method {
		String result();
		String name();
}
