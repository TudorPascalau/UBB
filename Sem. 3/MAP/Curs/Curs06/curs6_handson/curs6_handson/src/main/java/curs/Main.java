package curs;

import curs.domain.Utilizator;
import curs.domain.validators.UtilizatorValidator;
import curs.domain.validators.ValidationException;
import curs.repository.Repository;
import curs.repository.RepositoryException;
import curs.repository.factory.RepositoryFactory;

import java.io.IOException;
import java.io.InputStream;
import java.util.Optional;
import java.util.Properties;

public class Main {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) throws IOException {
        try {
            Repository<Long, Utilizator> repo = creeazaRepo();
            create(repo);
            readAll(repo);
            readOne(repo);
            update(repo);
            delete(repo);
        } catch (RepositoryException e) {
            System.out.println("Eroare la baza de date: " + e.getMessage());
        }
    }

    // Cerinta 0. Creati repository-ul DB cu RepositoryFactory, din config.properties.

    /**
     *
     * @return the database repository created by the factory
     * @throws IOException if config.properties cannot be read
     */
    static Repository<Long, Utilizator> creeazaRepo() throws IOException {
        Properties props = new Properties();
        try (InputStream in = Main.class.getResourceAsStream("/config.properties")) {
            props.load(in);
        }
        return new RepositoryFactory(props).createUtilizatorRepository(new UtilizatorValidator());
    }

    // Creati repository-ul in fisier cu acelasi factory: se schimba doar repository.type (nu se apeleaza).

    /**
     *
     * @return the file repository created by the factory
     * @throws IOException if config.properties cannot be read
     */
    static Repository<Long, Utilizator> creeazaRepoFile() throws IOException {
        Properties props = new Properties();
        try (InputStream in = Main.class.getResourceAsStream("/config.properties")) {
            props.load(in);
        }
        props.setProperty("repository.type", "FILE");   // fisierul: file.utilizatori din config
        return new RepositoryFactory(props).createUtilizatorRepository(new UtilizatorValidator());
    }

    // Cerinta 1 (Create). Salvati: a) Elena Radu, fara id (valid); b) un utilizator invalid; c) null.

    static void create(Repository<Long, Utilizator> repo) {
        System.out.println("save...");
    }

    // Cerinta 2 (Read). Afisati toti utilizatorii.

    /**
     *
     * @param repo - the database repository
     */
    static void readAll(Repository<Long, Utilizator> repo) {


    }

    // Cerinta 3 (Read). Cautati: a) Elena (exista); b) id 9999 (nu exista); c) id null.

    /**
     *
     * @param repo - the database repository
     */
    static void readOne(Repository<Long, Utilizator> repo) {

    }

    // Cerinta 4 (Update). Modificati: a) id 9999 (nu exista); b) Elena cu date invalide; c) null;
    //                    d) Elena -> Elena Radulescu (valid).

    /**
     *
     * @param repo - the database repository
     */
    static void update(Repository<Long, Utilizator> repo) {

    }

    // Cerinta 5 (Delete). Stergeti: a) Elena (exista); b) Elena din nou (nu mai exista); c) id null.
    static void delete(Repository<Long, Utilizator> repo) {

    }
}
