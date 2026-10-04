package expression;

import model.ComplexNumber;

public final class AdditionExpression extends ComplexExpression {
    public AdditionExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {
        return a.add(b);
    }
}
