import expression.ComplexExpression;
import expression.ExpressionFactory;
import parser.CommandLineExpressionParser;
import parser.ComplexNumberParser;
import parser.ExpressionParser;

public class Main {
    public static void main(String[] args) {

        ComplexNumberParser numberParser = new ComplexNumberParser();
        ExpressionFactory expressionFactory = new ExpressionFactory();

        ExpressionParser parser = new CommandLineExpressionParser(numberParser, expressionFactory);
        ComplexExpression expression = parser.parse(args);

        System.out.println(expression.evaluate());
    }
}
