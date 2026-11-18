package seminar8.repository;

import seminar8.domain.Movie;
import java.util.List;

public interface MovieRepository extends PagingRepository<Long, Movie> {
    List<Integer> getYears();
}
