package domain;

import java.util.Objects;

public abstract class Entity<ID> {
    private final ID id;

    protected Entity(ID id) {
        this.id = Objects.requireNonNull(id, "ID cannot be null");
    }

    public ID getId() {
        return id;
    }

    @Override
    public final boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Entity<?> entity = (Entity<?>) o;
        return id.equals(entity.id);
    }

    @Override
    public final int hashCode() {
        return Objects.hash(getClass(), id);
    }

}
