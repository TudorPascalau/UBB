package expression;

import model.ComplexNumber;
import model.Number;
import model.Operation;

public class ComplexExpressionFactory implements ExpressionFactory {

    @Override
    public ComplexExpression createExpression(Operation operation, Number[] operands) {
        ComplexNumber[] complexOperands = new ComplexNumber[operands.length];

        for (int i = 0; i < operands.length; i++) {
            if (!(operands[i] instanceof ComplexNumber)) {
                throw new IllegalArgumentException("Operand must be a complex number");
            }

            complexOperands[i] = (ComplexNumber) operands[i];
        }

        switch (operation) {
            case ADDITION:
                return new AdditionExpression(complexOperands);
            case SUBTRACTION:
                return new SubtractionExpression(complexOperands);
            case MULTIPLICATION:
                return new MultiplicationExpression(complexOperands);
            case DIVISION:
                return new DivisionExpression(complexOperands);
            default:
                throw new IllegalArgumentException("Unsupported operation: " + operation);
        }
    }
}
