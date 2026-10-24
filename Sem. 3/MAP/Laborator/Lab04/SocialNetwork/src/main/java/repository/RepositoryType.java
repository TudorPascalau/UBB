package repository;

/**
 * Persistence backend selected through the application configuration.
 */
public enum RepositoryType {
    /** Stores entities only for the current application run. */
    MEMORY,
    /** Stores entities in separate UTF-8 text files. */
    FILE,
    /** Selects database repository skeletons whose operations are not implemented yet. */
    DATABASE
}
