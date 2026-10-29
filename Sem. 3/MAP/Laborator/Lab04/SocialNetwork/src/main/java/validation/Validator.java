package validation;

/**
 * Checks whether an entity satisfies the applicable validation rules.
 * @param <T> entity type
 */
@FunctionalInterface
public interface Validator<T> {
    /**
     * Checks entity validity.
     * @param entity entity to validate
     * @throws ValidationException if the entity is null or violates the validation rules
     */
    void validate(T entity);

    /**
     * Composes this validator with another validator, in that order.
     * The second validator runs only if this validator succeeds.
     * @param other validator to run after this validator
     * @return a validator that applies both validation strategies
     * @throws IllegalArgumentException if the other validator is null
     */
    default Validator<T> andThen(Validator<T> other) {
        if (other == null) {
            throw new IllegalArgumentException("Validator cannot be null");
        }
        return entity -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}
