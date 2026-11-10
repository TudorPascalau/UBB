package curs.repository.db;

import java.sql.SQLException;

/**
 * Function that may throw SQLException.
 * java.util.function.Function cannot be used with JDBC code: its method apply
 * does not declare checked exceptions, and almost every JDBC method throws SQLException.
 *
 * @param <T> - type of the argument
 * @param <R> - type of the result
 */
@FunctionalInterface
public interface SqlFunction<T, R> {

    /**
     *
     * @param t - the argument
     * @return the result of the function
     * @throws SQLException if a database access error occurs
     */
    R apply(T t) throws SQLException;
}
