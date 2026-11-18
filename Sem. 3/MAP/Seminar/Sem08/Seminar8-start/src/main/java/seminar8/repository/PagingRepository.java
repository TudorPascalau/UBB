package seminar8.repository;

import seminar8.domain.Entity;
import seminar8.util.Page;
import seminar8.util.Pageable;
import seminar8.util.Sort;

public interface PagingRepository<ID , E extends Entity<ID>> extends Repository<ID, E> {

    Page<E> findAllOnPage(Pageable pageable);

    Page<E> findAllOnPage(Pageable pageable, Sort sort);
}
