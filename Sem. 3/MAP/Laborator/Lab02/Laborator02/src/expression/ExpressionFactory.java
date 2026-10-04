package expression;

import model.ComplexNumber;
import model.Operation;

public class ExpressionFactory {

    public ComplexExpression createExpression(Operation operation, ComplexNumber[] operands) {
        switch (operation) {
            case ADDITION:
                return new AdditionExpression(operands);
            case SUBTRACTION:
                return new SubtractionExpression(operands);
            case MULTIPLICATION:
                return new MultiplicationExpression(operands);
            case DIVISION:
                return new DivisionExpression(operands);
            default:
                throw new IllegalArgumentException("Invalid operation");
        }
    }
}
