package repository;
import model.Entity;
import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E>{

    private Map<ID,E> map;

    public InMemoryRepository() {
        this.map = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if(id == null){
            throw new IllegalArgumentException("Id must not be null");
        }
        return map.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return map.values();
    }

    @Override
    public E save(E entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity must not be null");
        }

        ID id = entity.getId();
        if(map.containsKey(id)){
            return entity;
        }

        map.put(id, entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        return map.remove(id);
    }

    @Override
    public E update(E entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity must not be null");
        }

        if(!map.containsKey(entity.getId()))
            return entity;

        map.put(entity.getId(), entity);
        return null;
    }
}
