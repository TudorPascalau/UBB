package expression;

import model.ComplexNumber;

public final class DivisionExpression extends ComplexExpression {
    public DivisionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {

        if(b.getReal() == 0 && b.getImaginary() == 0) {
            throw new ArithmeticException("Cannot divide by zero.");
        }

        double denominator = b.getReal() * b.getReal() + b.getImaginary() * b.getImaginary();

        double real = (a.getReal() * b.getReal() + a.getImaginary() * b.getImaginary() ) / denominator;
        double imaginary = (a.getImaginary() * b.getReal() - a.getReal() * b.getImaginary() ) / denominator;

        return  new ComplexNumber(real, imaginary);
    }
}
