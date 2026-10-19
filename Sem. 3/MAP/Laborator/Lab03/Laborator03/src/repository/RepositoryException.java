package repository;

/**
 * Persistence failure with optional original cause.
 */
public class RepositoryException extends RuntimeException {
    private static final long serialVersionUID = 1L;
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
