package validation;

/**
 * Invalid entity data.
 */
public class ValidationException extends RuntimeException {
    private static final long serialVersionUID = 1L;
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
