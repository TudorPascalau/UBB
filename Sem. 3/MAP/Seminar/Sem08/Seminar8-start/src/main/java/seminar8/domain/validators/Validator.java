package seminar8.domain.validators;

import java.util.function.Predicate;

/**
 * Validation strategy for entities.
 * Functional interface: it has a single abstract method (validate), so a
 * validator can be written as a lambda expression or as a method reference.
 *
 * @param <T> - type of the entities to be validated
 */
@FunctionalInterface
public interface Validator<T> {

    /**
     *
     * @param entity - the entity to be validated
     * @throws ValidationException if the entity is not valid
     */
    void validate(T entity);

    /**
     * composes two validations: first this one, then the other one;
     * if this validation fails, the other one is not applied
     *
     * @param other - the validation applied after this one; must not be null
     * @return a validator that applies this validation, then the other one
     * @throws IllegalArgumentException if other is null
     */
    default Validator<T> andThen(Validator<T> other) {
        if (other == null)
            throw new IllegalArgumentException("other must be not null");
        return entity -> {
            this.validate(entity);
            other.validate(entity);
        };
    }
}