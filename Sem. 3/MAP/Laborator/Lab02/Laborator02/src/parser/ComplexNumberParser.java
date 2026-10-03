package parser;

import model.ComplexNumber;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ComplexNumberParser {

    // Real number REGEX
    private static final String NUMBER = "\\d+(?:\\.\\d+)?|\\.\\d+";

    private static final Pattern COMPLEX_PATTERN = Pattern.compile(
            "^([+-]?" + NUMBER + ")([+-])(" + NUMBER + ")?\\*?i$"
    );

    public ComplexNumber parse(String input) {
        if(input == null) {
            throw new IllegalArgumentException("Input cannot be null");
        }

        // Remove whitespace
        String normalizedInput = input.replaceAll("\\s+", "");

        Matcher matcher = COMPLEX_PATTERN.matcher(normalizedInput);
        if(!matcher.matches()) {
            throw new IllegalArgumentException("Input is not a complex number");
        }

        double real = Double.parseDouble(matcher.group(1));
        String coefficient = matcher.group(3);
        double imaginary = (coefficient == null) ? 0.0 : Double.parseDouble(coefficient);

        if("-".equals(matcher.group(2))) {
            imaginary = -imaginary;
        }

        if(Double.isInfinite(real) || Double.isInfinite(imaginary)) {
            throw new IllegalArgumentException("Input is too big");
        }

        return new ComplexNumber(real, imaginary);
    }
}
