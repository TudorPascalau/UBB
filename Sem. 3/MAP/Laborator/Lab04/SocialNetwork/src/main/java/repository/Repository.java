package repository;
import domain.Entity;

import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * Stores and retrieves entities by unique identifier.
 * @param <ID> identifier type
 * @param <E> entity type
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Finds an entity by identifier.
     *
     * @param id identifier of the entity to find
     * @return an Optional containing the matching entity,
     *         or an empty Optional if no entity exists with the given identifier
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     */
    Optional<E> findOne(ID id);

    /**
     * Adds an entity if its identifier is absent;
     * otherwise leaves storage unchanged.
     *
     * @param entity entity to add
     * @return an empty Optional if the entity was added,
     *         or an Optional containing the existing entity
     *         if its identifier is already present
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if the entity violates validation rules
     * @throws RepositoryException if persistence fails
     */
    Optional<E> save(E entity);

    /**
     * Replaces the entity with the same identifier;
     * otherwise leaves storage unchanged.
     *
     * @param entity replacement entity
     * @return an empty Optional if the entity was updated,
     *         or an Optional containing the supplied entity
     *         if its identifier is absent
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if the entity violates validation rules
     * @throws RepositoryException if persistence fails
     */
    Optional<E> update(E entity);

    /**
     * Removes an entity by identifier.
     *
     * @param id identifier of the entity to remove
     * @return an Optional containing the removed entity,
     *         or an empty Optional if no entity exists with the given identifier
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     */
    Optional<E> delete(ID id);

    /**
     * Returns all stored entities at the time of the call.
     * @return all stored entities, unaffected by later additions or removals; empty if none exist
     * @throws RepositoryException if persistence fails
     */
    Iterable<E> findAll();

    /**
     * Finds all entities matching the supplied condition.
     * @param filter condition used to select entities
     * @return a list containing the matching entities; empty if none match
     * @throws IllegalArgumentException if filter is null
     * @throws RepositoryException if persistence fails
     */
    default List<E> findAll(Predicate<E> filter) {
        if (filter == null) {
            throw new IllegalArgumentException("Filter cannot be null");
        }

        return StreamSupport.stream(findAll().spliterator(), false).filter(filter).collect(Collectors.toList());
    }

}
