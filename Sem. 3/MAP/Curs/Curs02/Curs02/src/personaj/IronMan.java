package personaj;

public class IronMan extends Character implements CanFly, CanTalk{
    @Override
    public void fight() {
        System.out.println("IronMan se lupta.");
    }

    @Override
    public void fly() {
        System.out.println("IronMan zboara.");
    }

    @Override
    public void talk() {
        System.out.println("IronMan vorbeste.");
    }

    @Override
    public void play() {
        System.out.println("IronMan se joaca.");
    }
}
