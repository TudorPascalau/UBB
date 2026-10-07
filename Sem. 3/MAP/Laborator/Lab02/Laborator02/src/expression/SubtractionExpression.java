package expression;

import model.ComplexNumber;

public final class SubtractionExpression extends ComplexExpression {
    public SubtractionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {

        double real = a.getReal() -  b.getReal();
        double imaginary = a.getImaginary() -  b.getImaginary();

        return new ComplexNumber(real, imaginary);
    }
}
