package ui;

import domain.Community;
import domain.CommunityAnalyzer;
import repository.UserFileRepository;
import repository.FriendshipFileRepository;
import repository.Repository;
import domain.FriendshipId;
import validation.UserValidator;
import validation.FriendshipValidator;
import domain.Friendship;
import domain.User;
import repository.RepositoryException;
import service.ServiceException;
import service.SocialNetworkService;
import validation.ValidationException;

import java.util.Scanner;

/**
 * Console presentation and startup error handling.
 */
public class UserInterface {
    /**
     * Builds the file-backed application and reports startup failures.
     */
    public static void start() {
        try {
            UserValidator userValidator = new UserValidator();
            Repository<Long, User> users = new UserFileRepository(userValidator);
            FriendshipValidator friendshipValidator = new FriendshipValidator(users);
            Repository<FriendshipId, Friendship> friendships =
                    new FriendshipFileRepository(friendshipValidator);
            SocialNetworkService service = new SocialNetworkService(users, friendships,
                    userValidator, friendshipValidator, new CommunityAnalyzer());
            new UserInterface(service).run();
        } catch (RepositoryException | ValidationException | ServiceException
                | IllegalArgumentException e) {
            System.out.println("Aplicatia nu poate porni: " + e.getMessage());
        }
    }

    private final SocialNetworkService service;
    private final Scanner scanner;

    /**
     * Creates a user interface.
     * @param service network operations
     */
    public UserInterface(SocialNetworkService service) {
        this.service = service;
        this.scanner = new Scanner(System.in);
    }

    /**
     * Runs the menu; invalid operations are reported without stopping the menu.
     */
    public void run() {
        boolean running = true;
        while (running) {
            printMenu();

            if(!scanner.hasNextLine()) {
                break;
            }

            String option = scanner.nextLine().trim();

            try{
                switch (option) {
                    case "1":
                        addUser();
                        break;
                    case "2":
                        removeUser();
                        break;
                    case "3":
                        showUsers();
                        break;
                    case "4":
                        addFriendship();
                        break;
                    case "5":
                        removeFriendship();
                        break;
                    case "6":
                        showFriendships();
                        break;
                    case "7":
                        showCommunityCount();
                        break;
                    case "8":
                        showMostSociableCommunity();
                        break;
                    case "9":
                        showCommunities();
                        break;
                    case "0":
                        running = false;
                        break;
                    default:
                        System.out.println("Invalid option");
                }
            }
            catch (java.util.NoSuchElementException e) {
                System.out.println("Intrarea a fost inchisa. Aplicatia se opreste.");
                return;
            }
            catch (NumberFormatException e) {
                System.out.println("ID has to be a number");
            }
            catch (ValidationException | ServiceException | RepositoryException
                    | IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println();
        System.out.println("1. Adauga utilizator");
        System.out.println("2. Sterge utilizator");
        System.out.println("3. Afiseaza utilizatorii");
        System.out.println("4. Adauga prietenie");
        System.out.println("5. Sterge prietenie");
        System.out.println("6. Afiseaza prieteniile");
        System.out.println("7. Afiseaza numarul de comunitati");
        System.out.println("8. Afiseaza comunitatea cea mai sociabila");
        System.out.println("9. Afiseaza toate comunitatile");
        System.out.println("0. Iesire");
        System.out.print("Optiune: ");
    }

    private Long readId(String prompt) {
        System.out.print(prompt);
        return Long.parseLong(scanner.nextLine().trim());
    }

    private void addUser() {
        System.out.print("Prenume: ");
        String firstName = scanner.nextLine().trim();

        System.out.print("Nume: ");
        String lastName = scanner.nextLine().trim();

        service.addUser(firstName, lastName);
        System.out.println("Utilizator adaugat.");
    }

    private void removeUser() {
        Long id = readId("ID utilizator: ");

        service.removeUser(id);
        System.out.println("Utilizator sters.");
    }

    private void showUsers() {
        boolean found = false;

        for (User user : service.getUsers()) {
            System.out.println(user);
            found = true;
        }

        if (!found) {
            System.out.println("Nu exista utilizatori.");
        }
    }

    private void addFriendship() {
        Long first = readId("ID primul utilizator: ");
        Long second = readId("ID al doilea utilizator: ");
        service.addFriendship(first, second);
        System.out.println("Prietenie adaugata.");
    }

    private void removeFriendship() {
        Long first = readId("ID primul utilizator: ");
        Long second = readId("ID al doilea utilizator: ");
        service.removeFriendship(first, second);
        System.out.println("Prietenie stearsa.");
    }

    private void showCommunityCount() {
        System.out.println("Numar de comunitati: " + service.getCommunityCount());
    }

    private void showMostSociableCommunity() {
        System.out.println("Comunitatea cea mai sociabila: "
                + service.getMostSociableCommunity());
    }

    private void showCommunities() {
        boolean found = false;

        for (Community community : service.getCommunities()) {
            System.out.println(community);
            found = true;
        }

        if (!found) {
            System.out.println("Nu exista comunitati in retea.");
        }
    }

    private void showFriendships() {
        boolean found = false;

        for (Friendship friendship : service.getFriendships()) {
            System.out.println(friendship);
            found = true;
        }

        if (!found) {
            System.out.println("Nu exista prietenii.");
        }
    }
}
