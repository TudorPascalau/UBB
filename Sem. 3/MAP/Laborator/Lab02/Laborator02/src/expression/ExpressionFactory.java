package expression;

import model.ComplexNumber;
import model.Operation;

public interface ExpressionFactory {
    ComplexExpression createExpression(
            Operation operation, ComplexNumber[] operands);
}
