package validation;

/**
 * Invalid entity data.
 */
@SuppressWarnings("serial")
public class ValidationException extends RuntimeException {
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     */
    public ValidationException(String message) { super(message); }
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     * @param cause original failure
     */
    public ValidationException(String message, Throwable cause) { super(message, cause); }
}
