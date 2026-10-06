import expression.ComplexExpression;
import expression.DefaultExpressionFactory;
import expression.ExpressionFactory;
import parser.CommandLineExpressionParser;
import parser.ComplexNumberParser;
import parser.ExpressionParser;
import parser.NumberParser;

public class Main {
    public static void main(String[] args) {

        NumberParser numberParser = new ComplexNumberParser();
        ExpressionFactory expressionFactory = new DefaultExpressionFactory();

        ExpressionParser parser = new CommandLineExpressionParser(numberParser, expressionFactory);

        try {
            ComplexExpression expression = parser.parse(args);
            System.out.println(expression.evaluate());
        } catch (IllegalArgumentException e) {
            System.err.println("Invalid expression: " + e.getMessage());
        } catch (ArithmeticException e) {
            System.err.println("Arithmetic error: " + e.getMessage());
        }
    }
}
