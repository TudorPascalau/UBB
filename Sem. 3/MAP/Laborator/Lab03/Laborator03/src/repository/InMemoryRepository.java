package repository;

import domain.Entity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E>{

    private final Map<ID, E> entities;

    public InMemoryRepository() {
        this.entities = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null");
        }

        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return new ArrayList<>(entities.values());
    }

    @Override
    public E save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        if(entities.containsKey(entity.getId())) {
            return entities.get(entity.getId());
        }

        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        if(!entities.containsKey(entity.getId())) {
            return entity;
        }

        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null");
        }

        return entities.remove(id);
    }
}
