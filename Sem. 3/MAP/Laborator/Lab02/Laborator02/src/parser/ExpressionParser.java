package parser;

import expression.Expression;

public interface ExpressionParser {
    Expression parse(String[] args);
}
