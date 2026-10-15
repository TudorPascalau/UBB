package ui;

import domain.Friendship;
import domain.User;
import repository.RepositoryException;
import service.ServiceException;
import service.SocialNetworkService;
import validation.ValidationException;

import java.util.Scanner;

public class UserInterface {
    private final SocialNetworkService service;
    private final Scanner scanner;

    public UserInterface(SocialNetworkService service) {
        this.service = service;
        this.scanner = new Scanner(System.in);
    }

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
                    case "0":
                        running = false;
                        break;
                    default:
                        System.out.println("Invalid option");
                }
            }
            catch (NumberFormatException e) {
                System.out.println("ID has to be a number");
            }
            catch (ValidationException | ServiceException | RepositoryException e) {
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
        System.out.println("0. Iesire");
        System.out.print("Optiune: ");
    }

    private Long readId(String prompt) {
        System.out.print(prompt);
        return Long.parseLong(scanner.nextLine().trim());
    }

    private void addUser() {
        System.out.print("Username: ");
        String username = scanner.nextLine().trim();

        System.out.print("Prenume: ");
        String firstName = scanner.nextLine().trim();

        System.out.print("Nume: ");
        String lastName = scanner.nextLine().trim();

        service.addUser(username, firstName, lastName);
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
        System.out.print("Username primul utilizator: ");
        String firstUsername = scanner.nextLine().trim();
        System.out.print("Username al doilea utilizator: ");
        String secondUsername = scanner.nextLine().trim();

        service.addFriendship(firstUsername, secondUsername);
        System.out.println("Prietenie adaugata.");
    }

    private void removeFriendship() {
        Long id = readId("ID prietenie: ");

        service.removeFriendship(id);
        System.out.println("Prietenie stearsa.");
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
