package personaj;

public class Character implements CanFight{
    @Override
    public void fight() {
        System.out.println("Personajul se joaca.");
    }

    @Override
    public void play() {
        System.out.println("Personajul se lupta.");
    }
}
