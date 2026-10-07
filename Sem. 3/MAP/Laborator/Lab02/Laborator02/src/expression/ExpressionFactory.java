package expression;

import model.Number;
import model.Operation;

public interface ExpressionFactory {
    Expression createExpression(
            Operation operation, Number[] operands);
}
