package seminar7.repository.db;

import seminar7.domain.Movie;
import seminar7.domain.validators.Validator;
import seminar7.repository.Repository;
import seminar7.repository.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MovieDBRepository implements Repository<Long,Movie> {
    private final Validator<Movie> validator;
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(Validator<Movie> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Movie> findOne(Long id) {

        if(id == null){
            throw new IllegalArgumentException("Id cannot be null");
        }

        try(Connection connection = DriverManager.getConnection(url,username,password);){
            PreparedStatement ps = connection.prepareStatement("SELECT * FROM filme where id = ?");
            Movie m = null;
            ps.setLong(1,id);
            try(ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    m = new Movie(rs.getString("titlu"),
                            rs.getString("regizor"),
                            rs.getInt("an"), rs.getInt("durata"));
                    m.setId(rs.getLong("id"));
                }
            }

            return Optional.ofNullable(m);
        }
        catch(SQLException e) {
            throw new RepositoryException("Error while reading data:" + e.getMessage(), e);
        }

    }

    @Override
    public Iterable<Movie> findAll() {
        List<Movie> movies  = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url,username,password);){
            PreparedStatement ps = connection.prepareStatement("SELECT * FROM filme order by id");
            // select * from filme where id=?
            // ps.setLong(1,id);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Movie m = new Movie(rs.getString("titlu"),
                        rs.getString("regizor"),
                        rs.getInt("an"), rs.getInt("durata"));
                m.setId(rs.getLong("id"));
                movies.add(m);
            }
        }
        catch(SQLException e) {
            throw new RepositoryException("Error while reading data:" + e.getMessage(), e);
        }

        return movies;
    }

    @Override
    public Optional<Movie> save(Movie entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity cannot be null");
        }

        validator.validate(entity);
        String sql = "insert into filme (titlu, regizor, an, durata) values(?,?,?,?)";
        try(Connection connection = DriverManager.getConnection(url, username, password)){
            PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, entity.getTitle());
            ps.setString(2, entity.getDirector());
            ps.setInt(3, entity.getYear());
            ps.setInt(4, entity.getDuration());
            ps.executeUpdate();
            try(ResultSet resultSet = ps.getGeneratedKeys()){
                resultSet.next();
                entity.setId(resultSet.getLong(1));
            }
        }
        catch (SQLException e) {
            throw new RepositoryException("Error while reading data:" + e.getMessage(), e);
        }

        return Optional.empty();
    }

    @Override
    public Optional<Movie> delete(Long id) {

        Optional<Movie> movie = findOne(id);
        if(movie.isPresent()){
            return movie;
        }

        String sql = "delete from filme where id=?";
        try(Connection connection = DriverManager.getConnection(url, username, password)){
            PreparedStatement ps = connection.prepareStatement(sql);
            ps.setLong(1, id);
            ps.executeUpdate();
        }
        catch (SQLException e) {
            throw new RepositoryException("Error while deleting data " + e.getMessage(), e);
        }

        return movie;
    }

    @Override
    public Optional<Movie> update(Movie entity) {

        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        validator.validate(entity);

        String sql = "UPDATE filme SET titlu = ?, regizor = ?, an = ?, durata = ? WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, entity.getTitle());
            ps.setString(2, entity.getDirector());
            ps.setInt(3, entity.getYear());
            ps.setInt(4, entity.getDuration());
            ps.setLong(5, entity.getId());

            int rowsAffected = ps.executeUpdate();
            if(rowsAffected == 0){
                return Optional.of(entity);
            }

        }
        catch (SQLException e) {
            throw new RepositoryException("Error while updating data: " + e.getMessage(), e);
        }

        return Optional.empty();
    }


    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT * FROM filme WHERE regizor = ? order by an";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, director);

            try(ResultSet rs = ps.executeQuery()){
                while (rs.next()) {
                    Movie m = new Movie(rs.getString("titlu"),
                            rs.getString("regizor"),
                            rs.getInt("an"), rs.getInt("durata"));
                    m.setId(rs.getLong("id"));
                    movies.add(m);
                }
            }

        }
        catch (SQLException e) {
            throw new RepositoryException("Error while updating data: " + e.getMessage(), e);
        }

        return movies;
    }
}
