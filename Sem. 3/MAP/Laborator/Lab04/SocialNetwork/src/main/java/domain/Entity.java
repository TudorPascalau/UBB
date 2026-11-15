package domain;
import java.util.Objects;

/**
 * An entity whose identity is determined by its concrete type and identifier.
 * @param <ID> identifier type
 */
public abstract class Entity<ID> {
    private ID id;
    /**
     * Creates an entity.
     * @param id entity identifier
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
     * Sets entity ID.
     * @param id identifier to be set
     * @throws IllegalArgumentException if id is null
     */
    public void setId(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("ID cannot be null");
        }

        this.id = id; }

    /**
     * Compares entities by concrete type and identifier.
     * @param other object to compare
     * @return whether class and ID match
     */
    @Override public final boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof Entity<?> entity) || getClass() != other.getClass()) return false;
        return id.equals(entity.id);
    }
    /**
     * Returns a hash consistent with equality.
     * @return a hash consistent with equality
     */
    @Override public final int hashCode() { return Objects.hash(getClass(), id); }
}
