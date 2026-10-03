package parser;

import expression.ComplexExpression;

public interface ExpressionParser {
    ComplexExpression parse(String[] args);
}
