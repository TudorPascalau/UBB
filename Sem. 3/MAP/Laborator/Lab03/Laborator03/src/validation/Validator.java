package validation;

/**
 * Strategy for checking an entity's validity.
 * @param <T> entity type
 */
public interface Validator<T> {
    /**
     * Checks entity validity.
     * @param entity entity to validate
     * @throws ValidationException if the entity is invalid
     */
    void validate(T entity);
}
