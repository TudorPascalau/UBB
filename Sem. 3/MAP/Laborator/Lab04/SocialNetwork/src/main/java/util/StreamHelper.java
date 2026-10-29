package util;

import java.util.Objects;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/**
 * Provides stream utilities for Iterable sources.
 */
public final class StreamHelper {
    private StreamHelper() {}

    /**
     * Creates a new sequential stream over the supplied source.
     *
     * @param source source of elements
     * @param <T> element type
     * @return a new sequential stream over the source
     * @throws NullPointerException if source is null
     */
    public static <T> Stream<T> stream(Iterable<T> source) {
        Objects.requireNonNull(source, "Source cannot be null");

        return StreamSupport.stream(source.spliterator(), false);
    }
}
