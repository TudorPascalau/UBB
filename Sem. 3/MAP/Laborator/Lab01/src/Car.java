public class Car {
    private int year;
    private double price;

    public Car(int year, double price) {
        this.year = year;
        this.price = price;
    }

    public Car() {
        this.year = 0;
        this.price = 0;
    }

    public int getYear() {
        return this.year;
    }

    public double getPrice() {
        return this.price;
    }

    @Override
    public String toString() {
        return this.year + " " + this.price;
    }
}
