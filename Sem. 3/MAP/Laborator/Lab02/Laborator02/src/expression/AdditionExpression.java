package expression;

import model.ComplexNumber;

public final class AdditionExpression extends ComplexExpression {
    public AdditionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {

        double real = a.getReal() +  b.getReal();
        double  imaginary = a.getImaginary() +  b.getImaginary();

        return new ComplexNumber(real, imaginary);
    }
}
