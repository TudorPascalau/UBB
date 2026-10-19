package domain;
import java.util.Objects;

/**
 * Immutable entity identity.
 * @param <ID> identifier type
 */
public abstract class Entity<ID> {
    private final ID id;
    /**
     * Creates a entity.
     * @param id immutable identifier
     * @throws IllegalArgumentException if id is null
     */
    protected Entity(ID id) {
        if (id == null) throw new IllegalArgumentException("ID cannot be null");
        this.id = id;
    }
    /**
     * Returns the immutable identifier.
     * @return the identifier
     */
    public ID getId() { return id; }
    /**
     * Compares object values.
     * @param other object to compare
     * @return whether class and ID match
     */
    @Override public final boolean equals(Object other) {
        if (this == other) return true;
        if (other == null || getClass() != other.getClass()) return false;
        Entity<?> entity = (Entity<?>) other;
        return id.equals(entity.id);
    }
    /**
     * Returns a hash consistent with equality.
     * @return a hash consistent with equality
     */
    @Override public final int hashCode() { return Objects.hash(getClass(), id); }
}
