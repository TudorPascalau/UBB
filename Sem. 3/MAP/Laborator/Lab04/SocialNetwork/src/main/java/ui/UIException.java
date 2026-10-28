package ui;

/**
 * Invalid input entered through the user interface.
 */
public class UIException extends RuntimeException {
    /**
     * Creates an exception with input failure details.
     * @param message description of the failure
     * @param cause original failure
     */
    public UIException(String message, Throwable cause) {
        super(message, cause);
    }
}
