package expression;

import model.ComplexNumber;

public final class MultiplicationExpression extends ComplexExpression {
    public MultiplicationExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {

        double real = a.getReal() *  b.getReal() - a.getImaginary() * b.getImaginary();
        double  imaginary = a.getReal() * b.getImaginary() + a.getImaginary() *  b.getReal();

        return new ComplexNumber(real, imaginary);
    }
}
