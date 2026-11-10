package curs.ex.functional;

/**
 * Square given by its side
 */
public class Patrat {

    private final double latura;

    /**
     *
     * @param latura - the side of the square
     */
    public Patrat(double latura) {
        this.latura = latura;
    }

    /**
     *
     * @return the side of the square
     */
    public double getLatura() {
        return latura;
    }

    /**
     *
     * @return the string representation of the square
     */
    @Override
    public String toString() {
        return "Patrat{latura=" + latura + '}';
    }
}
