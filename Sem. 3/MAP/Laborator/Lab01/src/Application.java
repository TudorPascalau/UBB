public class Application {

    public static void main(String[] args) {
        Car car = new Car(2020, 40.5);
        AudiCar audiCar = new AudiCar(2022, 1500, "Germany");
        Car porscheCar = new PorscheCar(2024, 2020, "Macan");
        Car anotherPorscheCar = new PorscheCar(2020, 2020, "Taycan");

        System.out.println(car.toString());
        System.out.println(audiCar.toString());
        System.out.println(porscheCar.toString());
        System.out.println(anotherPorscheCar);

        porscheCar = audiCar;
        System.out.println(porscheCar.toString());
    }
}
