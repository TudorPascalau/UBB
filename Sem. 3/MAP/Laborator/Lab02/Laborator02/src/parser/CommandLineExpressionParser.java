package parser;

import expression.ComplexExpression;
import expression.ExpressionFactory;
import model.ComplexNumber;
import model.Operation;

public class CommandLineExpressionParser implements ExpressionParser {
    private final ComplexNumberParser numberParser;
    private final ExpressionFactory expressionFactory;

    public CommandLineExpressionParser(ComplexNumberParser numberParser, ExpressionFactory expressionFactory) {
        this.numberParser = numberParser;
        this.expressionFactory = expressionFactory;
    }

    @Override
    public ComplexExpression parse(String[] args) {
        validateStructure(args);

        Operation operation = parseOperation(args[1]);
        ComplexNumber[] operands = new ComplexNumber[args.length/2 + 1];

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

    private Operation parseOperation(String token) {
        switch (token) {
            case "+":
                return Operation.ADDITION;
            case "-":
                return Operation.SUBTRACTION;
            case "*":
                return Operation.MULTIPLICATION;
            case "/":
                return Operation.DIVISION;
            default:
                throw new IllegalArgumentException("Invalid operation");
        }
    }
}
