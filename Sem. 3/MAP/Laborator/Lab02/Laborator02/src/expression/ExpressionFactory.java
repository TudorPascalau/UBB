package expression;

import model.ComplexNumber;
import model.Operation;

public class ExpressionFactory {

    public ComplexExpression createExpression(Operation operation, ComplexNumber[] operands) {
        return switch (operation) {
            case ADDITION -> new AdditionExpression(operands);
            case SUBTRACTION -> new SubtractionExpression(operands);
            case MULTIPLICATION -> new MultiplicationExpression(operands);
            case DIVISION -> new DivisionExpression(operands);
        };
    }
}
