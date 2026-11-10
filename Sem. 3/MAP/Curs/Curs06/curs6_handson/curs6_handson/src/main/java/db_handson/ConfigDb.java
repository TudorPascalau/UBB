package db_handson;

import java.io.IOException;
import java.io.InputStream;
import java.io.UncheckedIOException;
import java.util.Properties;

/**
 * The connection data, read from config.properties (data, nu trebuie implementata)
 */
public final class ConfigDb {

    public static final String URL;
    public static final String USER;
    public static final String PASSWORD;

    static {
        Properties props = new Properties();
        try (InputStream in = ConfigDb.class.getResourceAsStream("/config.properties")) {
            props.load(in);
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
        URL = props.getProperty("db.url");
        USER = props.getProperty("db.user");
        PASSWORD = props.getProperty("db.password");
    }

    private ConfigDb() {
    }
}
