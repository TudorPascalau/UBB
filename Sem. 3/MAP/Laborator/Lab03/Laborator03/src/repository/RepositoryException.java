package repository;

/**
 * Persistence failure with optional original cause.
 */
@SuppressWarnings("serial")
public class RepositoryException extends RuntimeException {
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     */
    public RepositoryException(String message) { super(message); }
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     * @param cause original failure
     */
    public RepositoryException(String message, Throwable cause) { super(message, cause); }
}
