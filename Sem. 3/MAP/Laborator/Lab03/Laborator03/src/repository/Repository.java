package repository;
import domain.Entity;

/**
 * CRUD contract shared by all persistence implementations.
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
     * Returns a snapshot of stored entities.
     * @return a snapshot of all entities
     * @throws RepositoryException if persistence fails
     */
    Iterable<E> findAll();
    /**
     * Validates and inserts an entity.
     * @param entity entity to add
     * @return null on success, or the existing entity for a duplicate ID
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if entity is invalid
     * @throws RepositoryException if persistence fails
     */
    E save(E entity);
    /**
     * Validates and replaces an existing entity.
     * @param entity replacement entity
     * @return null on success, or the supplied entity if absent
     * @throws IllegalArgumentException if entity is null
     * @throws validation.ValidationException if entity is invalid
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
