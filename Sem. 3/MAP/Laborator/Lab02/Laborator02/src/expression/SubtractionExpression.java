package expression;

import model.ComplexNumber;

public final class SubtractionExpression extends ComplexExpression {
    public SubtractionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {
        return a.subtract(b);
    }
}
