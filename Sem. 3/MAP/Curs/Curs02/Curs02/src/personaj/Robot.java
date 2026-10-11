package personaj;

public class Robot extends Character implements CanTalk {
    @Override
    public void fight() {
        System.out.println("Robot se lupta.");
    }

    @Override
    public void talk() {
        System.out.println("Robot vorbeste.");
    }

    @Override
    public void play() {
        System.out.println("Robot se joaca.");
    }
}
