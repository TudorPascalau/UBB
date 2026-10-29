package ui;

import domain.Community;
import domain.Friendship;
import domain.User;
import repository.RepositoryException;
import service.ServiceException;
import service.SocialNetworkService;
import service.UserCriteria;
import validation.ValidationException;

import java.util.List;
import java.util.Scanner;
import java.util.function.Predicate;
import java.util.stream.Collectors;

import static util.StreamHelper.stream;

/**
 * Console presentation using the supplied application service.
 */
public class UserInterface {
    private final SocialNetworkService service;
    private final Scanner scanner;

    /**
     * Creates a user interface using an already configured service.
     * @param service network operations
     * @throws IllegalArgumentException if the service is null
     */
    public UserInterface(SocialNetworkService service) {
        if (service == null) throw new IllegalArgumentException("Service cannot be null");
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
                    case "10":
                        filterUsers();
                        break;
                    case "0":
                        running = false;
                        break;
                    default:
                        System.out.println("Invalid option");
                }
            }
            catch (UIException e) {
                System.out.println(e.getMessage());

                if (e.getCause() instanceof java.util.NoSuchElementException) {
                    return;
                }
            }
            catch (IllegalArgumentException e) {
                System.out.println("Invalid argument: " + e.getMessage());
            }
            catch (ValidationException e) {
                System.out.println("Invalid data: " + e.getMessage());
            }
            catch (ServiceException e) {
                System.out.println("Operation could not be completed: " + e.getMessage());
            }
            catch (RepositoryException e) {
                System.out.println("Error storing data: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println();
        System.out.println("1. Add user");
        System.out.println("2. Remove user");
        System.out.println("3. Show users");
        System.out.println("4. Add friendship");
        System.out.println("5. Remove friendship");
        System.out.println("6. Show friendships");
        System.out.println("7. Show community count");
        System.out.println("8. Show the most sociable community");
        System.out.println("9. Show all communities");
        System.out.println("10. Filter users");
        System.out.println("0. Exit");
        System.out.print("Option: ");
    }

    /**
     * Reads a search criterion and displays matching users.
     */
    private void filterUsers() {
        System.out.println("1. Last name equals");
        System.out.println("2. First name equals");
        System.out.println("3. Last name AND first name");
        System.out.println("4. Last name OR first name");
        System.out.println("5. Last name differs");
        System.out.println("6. First name differs");

        String option = readLine("Filter option: ");
        Predicate<User> criterion;

        switch (option) {
            case "1":
                criterion = UserCriteria.lastNameEquals(
                        readLine("Last name: "));
                break;

            case "2":
                criterion = UserCriteria.firstNameEquals(
                        readLine("First name: "));
                break;

            case "3":
                criterion = UserCriteria.lastNameEquals(
                                readLine("Last name: "))
                        .and(UserCriteria.firstNameEquals(
                                readLine("First name: ")));
                break;

            case "4":
                criterion = UserCriteria.lastNameEquals(
                                readLine("Last name: "))
                        .or(UserCriteria.firstNameEquals(
                                readLine("First name: ")));
                break;

            case "5":
                criterion = UserCriteria.lastNameEquals(
                        readLine("Last name: ")).negate();
                break;

            case "6":
                criterion = Predicate.not(
                        UserCriteria.firstNameEquals(
                                readLine("First name: ")));
                break;

            default:
                System.out.println("Invalid filter option.");
                return;
        }

        displayUsers(service.findUsers(criterion));
    }

    private void displayUsers(List<User> users) {
        if (users.isEmpty()) {
            System.out.println("No users found.");
            return;
        }

        users.forEach(System.out::println);
    }

    private String readLine(String prompt) {
        System.out.print(prompt);

        try {
            return scanner.nextLine().trim();
        } catch (java.util.NoSuchElementException e) {
            throw new UIException("Input ended.", e);
        }
    }

    private Long readId(String prompt) {
        String input = readLine(prompt);

        try {
            return Long.parseLong(input);
        } catch (NumberFormatException e) {
            throw new UIException("ID must be a valid integer.", e);
        }
    }


    private void addUser() {
        String firstName = readLine("First name: ");
        String lastName = readLine("Last name: ");

        service.addUser(firstName, lastName);
        System.out.println("User added.");
    }

    private void removeUser() {
        Long id = readId("User ID: ");

        service.removeUser(id);
        System.out.println("User removed.");
    }

    private void showUsers() {
        List<User> users = stream(service.getUsers()).collect(Collectors.toList());
        displayUsers(users);
    }

    private void addFriendship() {
        Long first = readId("First user ID: ");
        Long second = readId("Second user ID: ");
        service.addFriendship(first, second);
        System.out.println("Friendship added.");
    }

    private void removeFriendship() {
        Long first = readId("First user ID: ");
        Long second = readId("Second user ID: ");
        service.removeFriendship(first, second);
        System.out.println("Friendship removed.");
    }

    private void showFriendships() {
        List<Friendship> friendships = stream(service.getFriendships()).toList();

        if (friendships.isEmpty()) {
            System.out.println("No friendships found.");
            return;
        }

        friendships.forEach(System.out::println);
    }

    private void showCommunityCount() {
        System.out.println("Number of communities: " + service.getCommunityCount());
    }

    private void showMostSociableCommunity() {
        System.out.println("Most sociable community: "
                + service.getMostSociableCommunity());
    }

    private void showCommunities() {
        List<Community> communities = service.getCommunities();

        if (communities.isEmpty()) {
            System.out.println("No communities found in the network.");
            return;
        }

        communities.forEach(System.out::println);
    }

}
