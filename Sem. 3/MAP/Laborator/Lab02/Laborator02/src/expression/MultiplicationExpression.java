package expression;

import model.ComplexNumber;

public class MultiplicationExpression extends ComplexExpression {
    public MultiplicationExpression(ComplexNumber[] operands) {
        super(operands);
    }

    @Override
    protected ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b) {
        return a.multiply(b);
    }
}
