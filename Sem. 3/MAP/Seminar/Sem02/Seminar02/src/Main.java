class Shape {
    void print() {
        System.out.println("Shape - A");
    }
}
class Rectangle extends Shape {
     void print() {
        System.out.println("Rectangle - B");
    }
}
class Main {
    public static void main(String[] args) {
        Shape a = new Shape();
        Shape b = new Rectangle();
        a.print();
        b.print();
    }
}
