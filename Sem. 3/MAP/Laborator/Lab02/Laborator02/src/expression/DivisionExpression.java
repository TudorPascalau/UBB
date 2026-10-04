package expression;

import model.ComplexNumber;

public final class DivisionExpression extends ComplexExpression {
    public DivisionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {
        return a.divide(b);
    }
}
