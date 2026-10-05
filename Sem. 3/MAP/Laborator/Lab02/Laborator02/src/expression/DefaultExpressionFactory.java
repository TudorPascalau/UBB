package expression;

import model.ComplexNumber;
import model.Operation;

public class DefaultExpressionFactory implements ExpressionFactory {

    @Override
    public ComplexExpression createExpression(Operation operation, ComplexNumber[] operands) {
        return operation.createExpression(operands);
    }
}
