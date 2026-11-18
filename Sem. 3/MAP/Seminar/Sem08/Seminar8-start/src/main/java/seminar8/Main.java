package seminar8;

import seminar8.domain.Movie;
import seminar8.domain.validators.MovieValidator;
import seminar8.repository.MovieRepository;
import seminar8.repository.PagingRepository;
import seminar8.repository.Repository;
import seminar8.repository.RepositoryException;
import seminar8.repository.factory.RepositoryFactory;
import seminar8.util.Page;
import seminar8.util.Pageable;
import seminar8.util.Sort;

import java.io.IOException;
import java.io.InputStream;
import java.util.*;
import java.util.stream.Collectors;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) throws IOException {
        try {
            Repository<Long, Movie> repo = createRepository();
            readAll(repo);
            //TODO the commented calls wont work without fixing the previous todos,
            // complete them one by one and uncomment one by one methods
            getYears(repo);
            //pagination(repo);
            //interactivePagination(repo);
            //sortedPagination(repo);
            yearsWithStreams(repo);
           // streamPage(repo);
            //reports(repo);
        } catch (RepositoryException e) {
            System.out.println("Eroare la baza de date: " + e.getMessage());
        }
    }

    // Bonus 1: distinct years with streams, compared with getYears() from the repository (SQL for the DB)
    static void yearsWithStreams(Repository<Long, Movie> repo) {
        System.out.println("=== Bonus 1: years with streams ===");
        List<Integer> years = repo.stream().map(Movie::getYear).distinct().sorted().toList();
        years.forEach(System.out::println);
    }


    // Bonus 2: one page with streams (skip + limit), compared with findAllOnPage from the DB
    static void streamPage(Repository<Long, Movie> repo) {
        System.out.println("=== Bonus 3: paging with streams ===");
        int pageNumber = 1, pageSize = 3;   // page 2, numbered from 0
        List<Movie> movies = repo.stream()
    }


    static void getYears(Repository<Long, Movie> repo){
        System.out.println("===Get all distinct years===");

        //type check and cast in one step (since Java 16)
        if (repo instanceof MovieRepository movieRepo)
            movieRepo.getYears().forEach(System.out::println);
        else
            System.out.println("getYears is not supported by this repository");
    }

    static void pagination(Repository<Long, Movie> repo) {
        System.out.println("=== Pagination ===");
        if (!(repo instanceof PagingRepository<Long, Movie> pagingRepo)) {
            System.out.println("Pagination is not supported by this repository");
            return;
        }
        int pageSize = 3;
        Page<Movie> page = pagingRepo.findAllOnPage(new Pageable(0, pageSize));
        int totalPages = (page.getTotalNumberOfElements() + pageSize - 1) / pageSize;
        for (int pageNumber = 0; pageNumber < totalPages; pageNumber++) {
            if (pageNumber > 0)
                page = pagingRepo.findAllOnPage(new Pageable(pageNumber, pageSize));
            System.out.println("Page " + (pageNumber + 1) + "/" + totalPages + ":");
            page.getElementsOnPage().forEach(m -> System.out.println("  " + m));
        }
    }

    static void interactivePagination(Repository<Long, Movie> repo) {
        System.out.println("=== Interactive pagination ===");
        if (!(repo instanceof PagingRepository<Long, Movie> pagingRepo)) {
            System.out.println("Pagination is not supported by this repository");
            return;
        }
        Scanner scanner = new Scanner(System.in);

        int pageSize = 0;
        while (pageSize <= 0) {
            System.out.print("Movies per page: ");
            try {
                pageSize = Integer.parseInt(scanner.nextLine().trim());
                if (pageSize <= 0) System.out.println("Must be a positive number");
            } catch (NumberFormatException e) {
                System.out.println("Not a number");
            }
        }

        int pageNumber = 0;
        while (true) {
            Page<Movie> page = pagingRepo.findAllOnPage(new Pageable(pageNumber, pageSize));
            int totalElements = page.getTotalNumberOfElements();
            int totalPages = (totalElements + pageSize - 1) / pageSize;
            System.out.println("Page " + (pageNumber + 1) + "/" + totalPages + ":");
            page.getElementsOnPage().forEach(m -> System.out.println("  " + m));

            System.out.print("[n]ext, [p]revious, [q]uit: ");
            switch (scanner.nextLine().trim().toLowerCase()) {
                case "n" -> {
                    if(pageNumber + 1< totalPages) {
                        pageNumber++;
                    }
                    else {
                        System.out.println("Final page, cannot go further");
                    }

                }
                case "p" -> {
                    if(pageNumber > 0) {
                        pageNumber--;
                    }
                    else {
                        System.out.println("First page, cannot go back");
                    }
                }
                case "q" -> { return; }
                default -> System.out.println("Unknown command");
            }
        }
    }

    static void sortedPagination(Repository<Long, Movie> repo) {
        System.out.println("=== Sorted pagination ===");
        if (!(repo instanceof MovieRepository movieRepo)) {
            System.out.println("Sorted pagination is not supported by this repository");
            return;
        }
        Scanner scanner = new Scanner(System.in);
        System.out.print("Sort by (title / director / year / duration): ");
        String field = scanner.nextLine();
        System.out.print("Direction (asc/desc): ");
        boolean ascending = !scanner.nextLine().trim().equalsIgnoreCase("desc");
        Sort sort = new Sort(field, ascending);

        int pageSize = 3;
        try {
            Page<Movie> first = movieRepo.findAllOnPage(new Pageable(0, pageSize), sort);
            int totalPages = (first.getTotalNumberOfElements() + pageSize - 1) / pageSize;
            for (int pageNumber = 0; pageNumber < totalPages; pageNumber++) {
                Page<Movie> page = movieRepo.findAllOnPage(new Pageable(pageNumber, pageSize), sort);
                System.out.println("Page " + (pageNumber + 1) + "/" + totalPages + ":");
                page.getElementsOnPage().forEach(m -> System.out.println("  " + m));
            }
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }

    static void readAll(Repository<Long, Movie> repo) {
        System.out.println("=== Read all ===");
        repo.findAll().forEach(System.out::println);
    }

    static Repository<Long, Movie> createRepository() throws IOException {
        Properties props = new Properties();
        try (InputStream in = Main.class.getResourceAsStream("/config.properties")) {
            props.load(in);
        }
        return new RepositoryFactory(props).createMovieRepository(new MovieValidator());
    }

    static void reports(Repository<Long, Movie> repo) {
        System.out.println("=== Reports===");

        Map<String, Long> byDirector = repo.stream()
                .collect(Collectors.groupingBy(Movie::getDirector, Collectors.counting()));
        System.out.println("a) Movies by director: " + byDirector);

        OptionalDouble average = repo.stream().mapToInt(Movie::getDuration).average();
        System.out.println("b) Average duration: " + (average.isPresent() ? Math.round(average.getAsDouble()) + " minutes" : "there are no movies"));

        Optional<Movie> longest = repo.stream().max(Comparator.comparingInt(Movie::getDuration));
        System.out.println("c) longest: " + (longest.isPresent() ? longest.get().getTitle() : "there are no movies"));

        List<String> recents = repo.stream()
                .filter(f -> f.getYear() > 2010)
                .sorted(Comparator.comparingInt(Movie::getYear))
                .map(f -> f.getTitle() + " (" + f.getYear() + ")")
                .toList();
        System.out.println("d) after 2010: " + recents);
    }
}
