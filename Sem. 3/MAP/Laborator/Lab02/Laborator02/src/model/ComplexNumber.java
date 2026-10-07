package model;

public final class ComplexNumber implements Number {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    @Override
    public String toString() {
        String sign = imaginary < 0.0 ? "-" : "+";
        return real + sign + Math.abs(imaginary) + "*i";
    }
}
