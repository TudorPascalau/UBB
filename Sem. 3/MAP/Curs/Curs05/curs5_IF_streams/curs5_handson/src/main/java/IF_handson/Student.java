package IF_handson;

/**
 * Simple student used in the examples (data, nu trebuie implementata)
 */
public class Student {
    private final int id;
    private final String nume;
    private final double media;

    /**
     *
     * @param id    - the id of the student
     * @param nume  - the name of the student
     * @param media - the average grade of the student
     */
    public Student(int id, String nume, double media) {
        this.id = id;
        this.nume = nume;
        this.media = media;
    }

    /**
     *
     * @return the id of the student
     */
    public int getId() {
        return id;
    }

    /**
     *
     * @return the name of the student
     */
    public String getNume() {
        return nume;
    }

    /**
     *
     * @return the average grade of the student
     */
    public double getMedia() {
        return media;
    }

    @Override
    public String toString() {
        return nume + "(" + media + ")";
    }
}
