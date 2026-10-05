package parser;

import model.ComplexNumber;

public interface NumberParser {
    ComplexNumber parse(String input);
}
