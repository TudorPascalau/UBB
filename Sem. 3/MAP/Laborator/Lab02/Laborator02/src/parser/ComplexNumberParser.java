package parser;

import model.ComplexNumber;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ComplexNumberParser implements NumberParser {

    private static final String NUMBER =
            "(?:\\d+(?:\\.\\d+)?|\\.\\d+)";

    private static final Pattern COMPLEX_PATTERN = Pattern.compile(
            "^(?:([+-]?" + NUMBER + ")(?:([+-])(?:(" + NUMBER + ")\\*?)?i)?"
                    + "|([+-]?)(?:(" + NUMBER + ")\\*?)?i)$"
    );

    @Override
    public ComplexNumber parse(String input) {
        if (input == null) {
            throw new IllegalArgumentException("Input cannot be null");
        }

        Matcher matcher = COMPLEX_PATTERN.matcher(input);

        if (!matcher.matches()) {
            throw new IllegalArgumentException("Input is not a complex number");
        }

        double real = 0.0;
        String imaginarySign;
        String imaginaryCoefficient;

        if (matcher.group(1) != null) {
            real = Double.parseDouble(matcher.group(1));
            imaginarySign = matcher.group(2);
            imaginaryCoefficient = matcher.group(3);
        } else {
            imaginarySign = matcher.group(4);
            imaginaryCoefficient = matcher.group(5);
        }

        double imaginary = 0.0;
        if (imaginarySign != null) {
            imaginary = (imaginaryCoefficient == null) ? 1.0 : Double.parseDouble(imaginaryCoefficient);
            if ("-".equals(imaginarySign)) {
                imaginary = -imaginary;
            }
        }

        if (Double.isInfinite(real) || Double.isInfinite(imaginary)) {
            throw new IllegalArgumentException("Input is too big");
        }

        return new ComplexNumber(real, imaginary);
    }
}
