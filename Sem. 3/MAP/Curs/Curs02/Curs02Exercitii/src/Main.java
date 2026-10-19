import aventura.Adventure;
import personaj.*;
import personaj.Character;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Cerinta 1
        IronMan ironMan = new IronMan();

        Adventure.fightAdventure(ironMan);
        Adventure.talkAdventure(ironMan);
        Adventure.flyAdventure(ironMan);

        CanFight fighter = ironMan;
        CanTalk speaker = ironMan;
        CanFly flyer = ironMan;
        Character character = ironMan;

        Adventure.fightAdventure(fighter);
        Adventure.talkAdventure(speaker);
        Adventure.flyAdventure(flyer);
        Adventure.fightAdventure(character);

        Robot robot = new Robot();
        Adventure.fightAdventure(robot);
        Adventure.talkAdventure(robot);

        // Cerinta 2
        Adventure.rescueAdventure(ironMan);

        // Cerinta 3
        Echipa<CanFly> echipa = new Echipa<>();

        echipa.adauga(new IronMan());
        echipa.joacaToti();

        // Cerinta 4
        List<IronMan> ironMans = new ArrayList<>();
        Adventure.flyAll(ironMans);
    }
}
