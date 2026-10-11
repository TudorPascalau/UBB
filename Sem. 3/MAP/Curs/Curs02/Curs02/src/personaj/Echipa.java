package personaj;

import java.util.ArrayList;
import java.util.List;

public class Echipa <T extends CanPlay>{
    private final List<T> members = new ArrayList<>();

    public void adauga(T membru) {
        members.add(membru);
    }

    public void joacaToti() {
        for(T membru : members) {
            membru.play();
        }
    }
}
