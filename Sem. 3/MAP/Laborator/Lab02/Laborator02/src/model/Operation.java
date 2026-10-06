package model;

public enum Operation {
    ADDITION("+"),
    SUBTRACTION("-"),
    MULTIPLICATION("*"),
    DIVISION("/");

    private final String symbol;

    Operation(String symbol) {
        this.symbol = symbol;
    }

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
