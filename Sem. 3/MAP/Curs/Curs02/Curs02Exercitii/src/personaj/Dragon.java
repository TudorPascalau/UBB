package personaj;

public class Dragon implements CanPlay, CanFight, CanFly{
    @Override
    public void fight() {
        System.out.println("Dragonl se lupta");
    }

    @Override
    public void fly() {
        System.out.println("Dragonl zboara");
    }

    @Override
    public void play() {
        System.out.println("Dragonl se joaca");
    }
}
