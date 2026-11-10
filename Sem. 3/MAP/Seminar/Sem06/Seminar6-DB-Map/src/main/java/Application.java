import domain.User;
import repository.UserDBRepository;

import java.util.List;

public class Application {

    public static void main(String[] args) {
        String url="jdbc:postgresql://localhost:5432/postgres";
        String username="postgres";
        String password="admin";

        UserDBRepository repo = new UserDBRepository(url, username, password);
        List<User> users = repo.findAll();

        for(User u: users){
            System.out.println(u);
        }

        System.out.println("---Insert----");

        repo.addUser(new User(100l,"Barack","Obama"));
        System.out.println(repo.findAll());

        System.out.println("----FindBy----");
        List<User>filteredUsers = repo.findAllByLastName("Obama");
        System.out.println(filteredUsers);


    }
}
