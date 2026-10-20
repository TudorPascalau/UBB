package repository;

import domain.Entity;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * In-memory storage; entity validation belongs to the service.
 * @param <ID> identifier type
 * @param <E> entity type
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final Map<ID, E> entities = new HashMap<>();

    /**
     * Creates an in memory repository.
     */
    public InMemoryRepository() {}

    @Override public E findOne(ID id) {
        if (id == null) throw new IllegalArgumentException("ID cannot be null");
        return entities.get(id);
    }

    @Override public Iterable<E> findAll() { return new ArrayList<>(entities.values()); }


    @Override public E save(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entity cannot be null");
        E existing = entities.get(entity.getId());
        if (existing != null) return existing;
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override public E update(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entity cannot be null");
        if (!entities.containsKey(entity.getId())) return entity;
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override public E delete(ID id) {
        if (id == null) throw new IllegalArgumentException("ID cannot be null");
        return entities.remove(id);
    }

    /**
     * Copies the current state for rollback.
     * @return a detached map of the current immutable entities
     */
    protected final Map<ID, E> snapshot() { return new HashMap<>(entities); }
    /**
     * Restores a previously captured state.
     * @param snapshot state to restore
     */
    protected final void restore(Map<ID, E> snapshot) {
        entities.clear();
        entities.putAll(snapshot);
    }
}
