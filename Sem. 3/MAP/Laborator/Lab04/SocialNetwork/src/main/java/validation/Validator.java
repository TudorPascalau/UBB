package validation;

/**
 * Checks whether an entity satisfies the applicable validation rules.
 * @param <T> entity type
 */
public interface Validator<T> {
    /**
     * Checks entity validity.
     * @param entity entity to validate
     * @throws ValidationException if the entity is null or violates the validation rules
     */
    void validate(T entity);
}
