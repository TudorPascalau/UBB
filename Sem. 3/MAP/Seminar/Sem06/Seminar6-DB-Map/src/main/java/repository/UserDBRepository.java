package repository;

import domain.User;

import java.awt.datatransfer.MimeTypeParseException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserDBRepository {

    private String url;
    private String username;
    private String password;

    public UserDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public List<User> findAll(){
        List<User> users = new ArrayList<>();
        //try-with-resources
        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM USERS");
            ResultSet resultSet = preparedStatement.executeQuery();
            while(resultSet.next()){
                Long id = resultSet.getLong(1);
                String lastName =  resultSet.getString(2);
                String firstName = resultSet.getString(3);
                User  u = new User(id, lastName, firstName);
                users.add(u);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return users;
    }

    public void addUser(User u){
        try(Connection connection = DriverManager.getConnection(url, username, password)) {
            //in my db is lastname, firstname not like in the seminar last_name, first_name
            //update your statement based on your DB
            //check if user with id alreadyExists
            PreparedStatement findBy = connection.prepareStatement("SELECT * FROM USERS WHERE ID=?");
            findBy.setLong(1,u.getId());
            ResultSet resultSet = findBy.executeQuery();
            if(resultSet.next()){
                System.out.println("There is already a user with id:"+u.getId());
            }else {
                PreparedStatement insertStatement = connection.prepareStatement("INSERT INTO USERS (ID, LASTNAME, FIRSTNAME) VALUES(?,?,?)");
                insertStatement.setLong(1, u.getId());
                insertStatement.setString(2, u.getLastName());
                insertStatement.setString(3, u.getFirstName());
                int i = insertStatement.executeUpdate();
                System.out.println("Inserted: " + i + " rows");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<User>findAllByLastName(String lastName){
        List<User>users = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url, username,password)){
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM USERS WHERE LASTNAME=?");
            preparedStatement.setString(1,lastName);
            ResultSet resultSet = preparedStatement.executeQuery();
            while(resultSet.next()){
                User u = new User(resultSet.getLong(1), resultSet.getString(2), resultSet.getString(3));
                users.add(u);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }
}
