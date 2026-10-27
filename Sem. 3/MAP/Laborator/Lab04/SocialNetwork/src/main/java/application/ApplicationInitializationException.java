package application;

/**
 * Application startup failure retaining the original configuration, storage or validation cause.
 */
public final class ApplicationInitializationException extends RuntimeException {
    /**
     * Creates an initialization failure with its original cause.
     * @param message description of the startup failure
     * @param cause original failure
     */
    public ApplicationInitializationException(String message, Throwable cause) {
        super(message, cause);
    }
}
