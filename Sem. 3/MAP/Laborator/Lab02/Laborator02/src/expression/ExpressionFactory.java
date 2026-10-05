package expression;

import model.ComplexNumber;
import model.Operation;

public class ExpressionFactory {

    public ComplexExpression createExpression(Operation operation, ComplexNumber[] operands) {
        return operation.createExpression(operands);
    }
}
