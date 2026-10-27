package domain;

import java.util.function.Predicate;

public class CriteriaUser {
    public static Predicate<User> firstNameStartsWith(String prefix){
        return u-> u.getFirstName().startsWith(prefix);
    }

    public static Predicate<User> hasLastName(String name){
        return u-> u.getLastName().equals(name);
    }

    public static Predicate<User> hasAtLeastFriends(int n){
        return  u-> u.getFriends().size() >= n;
    }

    public static boolean withoutFriends(User u){
        return u.getFriends().isEmpty();
    }
}
