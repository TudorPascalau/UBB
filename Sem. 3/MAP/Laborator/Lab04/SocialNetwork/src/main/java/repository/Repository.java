package repository;
import domain.Entity;

/**
 * Stores and retrieves entities by unique identifier.
 * @param <ID> identifier type
 * @param <E> entity type
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Finds an entity by identifier.
     * @param id identifier
     * @return matching entity or null
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     */
    E findOne(ID id);
    /**
     * Returns all stored entities at the time of the call.
     * @return all stored entities, unaffected by later additions or removals; empty if none exist
     * @throws RepositoryException if persistence fails
     */
    Iterable<E> findAll();
    /**
     * Adds an entity if its identifier is absent; otherwise leaves storage unchanged.
     * @throws validation.ValidationException if the entity violates validation rules
     * @param entity entity to add
     * @return null on success, or the existing entity for a duplicate ID
     * @throws IllegalArgumentException if entity is null
     * @throws RepositoryException if persistence fails
     */
    E save(E entity);
    /**
     * Replaces the entity with the same identifier; leaves storage unchanged if none exists.
     * @throws validation.ValidationException if the entity violates validation rules
     * @param entity replacement entity
     * @return null on success, or the supplied entity if its identifier is absent
     * @throws IllegalArgumentException if entity is null
     * @throws RepositoryException if persistence fails
     */
    E update(E entity);
    /**
     * Removes an entity by identifier.
     * @param id identifier
     * @return removed entity, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     */
    E delete(ID id);
}
