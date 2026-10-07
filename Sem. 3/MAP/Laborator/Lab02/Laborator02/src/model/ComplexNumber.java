package model;

public final class ComplexNumber implements Number {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    private ComplexNumber requireComplexNumber(Number other) {
        if (!(other instanceof ComplexNumber)) {
            throw new IllegalArgumentException(
                    "Operand must be a complex number"
            );
        }

        return (ComplexNumber) other;
    }

    @Override
    public ComplexNumber add(Number other) {
        ComplexNumber operand = requireComplexNumber(other);

        return new ComplexNumber(
                real + operand.real,
                imaginary + operand.imaginary
        );
    }

    @Override
    public ComplexNumber subtract(Number other) {
        ComplexNumber operand = requireComplexNumber(other);

        return new ComplexNumber(
                real - operand.real,
                imaginary - operand.imaginary
        );
    }

    @Override
    public ComplexNumber multiply(Number other) {
        ComplexNumber operand = requireComplexNumber(other);

        return new ComplexNumber(
                real * operand.real - imaginary * operand.imaginary,
                real * operand.imaginary + imaginary * operand.real
        );
    }

    @Override
    public ComplexNumber divide(Number other) {
        ComplexNumber operand = requireComplexNumber(other);

        if (operand.real == 0.0 && operand.imaginary == 0.0) {
            throw new ArithmeticException("Cannot divide by zero.");
        }

        double denominator =
                operand.real * operand.real
                        + operand.imaginary * operand.imaginary;

        return new ComplexNumber(
                (real * operand.real
                        + imaginary * operand.imaginary) / denominator,
                (imaginary * operand.real
                        - real * operand.imaginary) / denominator
        );
    }

    @Override
    public String toString() {
        String sign = imaginary < 0.0 ? "-" : "+";
        return real + sign + Math.abs(imaginary) + "*i";
    }
}
