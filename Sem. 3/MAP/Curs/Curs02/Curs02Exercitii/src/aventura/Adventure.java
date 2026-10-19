package aventura;

import personaj.CanFight;
import personaj.CanFly;
import personaj.CanTalk;

import java.util.List;

public class Adventure {
    public static void fightAdventure(CanFight character) {
        character.fight();
    }

    public static void talkAdventure(CanTalk character) {
        character.talk();
    }

    public static void flyAdventure(CanFly character) {
        character.fly();
    }

    // Cerinta 2
    public static <T extends CanFly & CanTalk>
    void rescueAdventure(T character) {
        character.fly();
        character.fly();
    }

    // Cerinta 4
    public static <T extends CanFly>
    void flyAll(List<T> characters) {
        for(CanFly character : characters) {
            character.fly();
        }
    }
}
