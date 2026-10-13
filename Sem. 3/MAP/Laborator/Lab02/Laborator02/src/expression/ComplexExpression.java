package expression;

import model.ComplexNumber;

public abstract class ComplexExpression implements Expression {
    private final ComplexNumber[] operands;

    protected ComplexExpression(ComplexNumber[] operands) {
        if (operands == null || operands.length < 2) {
            throw new IllegalArgumentException("An expression requires at least two operands");
        }

        for (ComplexNumber operand : operands) {
            if (operand == null) {
                throw new IllegalArgumentException("Operand cannot be null");
            }
        }

        this.operands = operands.clone();
    }

    protected abstract ComplexNumber executeOperation(
            ComplexNumber a, ComplexNumber b);

    @Override
    public final ComplexNumber evaluate() {
        ComplexNumber result = operands[0];

        for (int i = 1; i < operands.length; i++) {
            result = executeOperation(result, operands[i]);

            double real = result.getReal();
            double imaginary = result.getImaginary();
            if (Double.isInfinite(real) || Double.isInfinite(imaginary)
                    || Double.isNaN(real) || Double.isNaN(imaginary)) {
                throw new ArithmeticException("Calculation produced a non-finite result");
            }
        }

        return result;
    }
}
