package ui;

import domain.Community;
import domain.Friendship;
import domain.User;
import repository.RepositoryException;
import service.ServiceException;
import service.SocialNetworkService;
import validation.ValidationException;

import java.util.Scanner;

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
        System.out.println("0. Exit");
        System.out.print("Option: ");
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
        boolean found = false;

        for (User user : service.getUsers()) {
            System.out.println(user);
            found = true;
        }

        if (!found) {
            System.out.println("No users found.");
        }
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

    private void showCommunityCount() {
        System.out.println("Number of communities: " + service.getCommunityCount());
    }

    private void showMostSociableCommunity() {
        System.out.println("Most sociable community: "
                + service.getMostSociableCommunity());
    }

    private void showCommunities() {
        boolean found = false;

        for (Community community : service.getCommunities()) {
            System.out.println(community);
            found = true;
        }

        if (!found) {
            System.out.println("No communities found in the network.");
        }
    }

    private void showFriendships() {
        boolean found = false;

        for (Friendship friendship : service.getFriendships()) {
            System.out.println(friendship);
            found = true;
        }

        if (!found) {
            System.out.println("No friendships found.");
        }
    }
}
