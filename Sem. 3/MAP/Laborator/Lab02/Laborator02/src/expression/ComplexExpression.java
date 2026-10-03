package expression;

import model.ComplexNumber;

public abstract class ComplexExpression {
    private final ComplexNumber[] operands;

    protected ComplexExpression(ComplexNumber[] operands) {
        this.operands = operands.clone();
    }

    protected abstract ComplexNumber executeOperation(ComplexNumber a, ComplexNumber b);

    public final ComplexNumber evaluate() {
        ComplexNumber result = operands[0];

        for(int i = 1; i < operands.length; i++) {
            result = executeOperation(result, operands[i]);
        }

        return result;
    }


}
