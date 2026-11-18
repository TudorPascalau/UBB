package seminar8.util;

/**
 * How to sort: by which field and in which direction.
 * @param field     one of: title, director, year, duration
 * @param ascending true = ASC, false = DESC
 */
public record Sort(String field, boolean ascending) { //Immutable class
}
