package model;

import expression.*;

public enum Operation {
    ADDITION("+") {
        @Override
        public ComplexExpression createExpression(
                ComplexNumber[] operands) {
            return new AdditionExpression(operands);
        }
    },
    SUBTRACTION("-") {
        @Override
        public ComplexExpression createExpression(
                ComplexNumber[] operands) {
            return new SubtractionExpression(operands);
        }
    },
    MULTIPLICATION("*") {
        @Override
        public ComplexExpression createExpression(
                ComplexNumber[] operands) {
            return new MultiplicationExpression(operands);
        }
    },
    DIVISION("/") {
        @Override
        public ComplexExpression createExpression(
                ComplexNumber[] operands) {
            return new DivisionExpression(operands);
        }
    };

    private final String symbol;

    Operation(String symbol) {
        this.symbol = symbol;
    }

    public abstract ComplexExpression createExpression(ComplexNumber[] operands);

    public static Operation fromSymbol(String symbol) {
        for (Operation operation : values()) {
            if (operation.symbol.equals(symbol)) {
                return operation;
            }
        }
        throw new IllegalArgumentException(
                "Invalid operation: " + symbol);
    }
}
