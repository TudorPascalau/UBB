package model;

public final class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(
                real + other.real,
                imaginary + other.imaginary
        );
    }

    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(
                real - other.real,
                imaginary - other.imaginary
        );
    }

    public ComplexNumber multiply(ComplexNumber other) {
        return new ComplexNumber(
                real * other.real -  imaginary * other.imaginary,
                real * other.imaginary +  imaginary * other.real
        );
    }

    public ComplexNumber divide(ComplexNumber other) {
        if (other.real == 0.0 && other.imaginary == 0.0) {
            throw new ArithmeticException(
                    "Nu se poate împărți la numărul complex zero."
            );
        }

        double denominator = other.real * other.real + other.imaginary * other.imaginary;

        return new ComplexNumber(
                (real * other.real + imaginary * other.imaginary) / denominator,
                (imaginary * other.real - real * other.imaginary) / denominator
        );
    }

    @Override
    public String toString() {
        String sign = imaginary < 0.0 ? "-" : "+";
        return real + sign + Math.abs(imaginary) + "*i";
    }
}
