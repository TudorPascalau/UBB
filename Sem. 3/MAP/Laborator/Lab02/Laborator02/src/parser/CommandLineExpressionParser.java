package parser;

import expression.Expression;
import expression.ExpressionFactory;
import model.Number;
import model.Operation;

public class CommandLineExpressionParser implements ExpressionParser {
    private final NumberParser numberParser;
    private final ExpressionFactory expressionFactory;

    public CommandLineExpressionParser(NumberParser numberParser, ExpressionFactory expressionFactory) {
        this.numberParser = numberParser;
        this.expressionFactory = expressionFactory;
    }

    @Override
    public Expression parse(String[] args) {
        validateStructure(args);

        Operation operation = Operation.fromSymbol(args[1]);
        Number[] operands = new Number[args.length/2 + 1];

        for (int i = 0; i < operands.length; i++) {
            operands[i] = numberParser.parse(args[i*2]);
        }

        return expressionFactory.createExpression(operation, operands);
    }

    private void validateStructure(String[] args) {
        if(args == null || args.length < 3 || args.length % 2 == 0) {
            throw new IllegalArgumentException("Input is not a valid expression");
        }

        for(String arg : args) {
            if(arg == null || arg.trim().isEmpty()) {
                throw new IllegalArgumentException("Argument is empty");
            }
        }

        for(int i = 3; i < args.length; i+=2) {
            if(!args[1].equals(args[i])) {
                throw new IllegalArgumentException("All operators must be the same");
            }
        }
    }
}
