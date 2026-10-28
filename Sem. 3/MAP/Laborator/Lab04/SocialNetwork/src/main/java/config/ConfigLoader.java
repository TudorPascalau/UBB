package config;

import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Properties;

/** Reads UTF-8 application properties without selecting or creating repositories. */
public final class ConfigLoader {
    private ConfigLoader() {}

    /**
     * Reads application configuration using a Reader.
     * @param fileName configuration file path, relative to the working directory
     * @return the loaded properties
     * @throws IOException if the configuration cannot be read
     */
    public static Properties load(String fileName) throws IOException {
        Properties properties = new Properties();
        try (FileReader reader = new FileReader(fileName, StandardCharsets.UTF_8)) {
            properties.load(reader);
        }
        return properties;
    }
}
