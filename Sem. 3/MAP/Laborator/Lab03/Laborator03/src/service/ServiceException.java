package service;

/**
 * Invalid network operation.
 */
public class ServiceException extends RuntimeException {
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     */
    public ServiceException(String message) { super(message); }
    /**
     * Creates an exception with failure details.
     * @param message description of the failure
     * @param cause original failure
     */
    public ServiceException(String message, Throwable cause) { super(message, cause); }
}
