package curs.ex.functional;

/**
 * Circle given by its radius
 */
public class Cerc {

    private final double raza;

    /**
     *
     * @param raza - the radius of the circle
     */
    public Cerc(double raza) {
        this.raza = raza;
    }

    /**
     *
     * @return the radius of the circle
     */
    public double getRaza() {
        return raza;
    }

    /**
     *
     * @param c - the circle
     * @return the area of the circle (static method, usable as Arie&lt;Cerc&gt; through Cerc::arie)
     */
    public static double arie(Cerc c) {
        return Math.PI * c.raza * c.raza;
    }

    /**
     *
     * @return the string representation of the circle
     */
    @Override
    public String toString() {
        return "Cerc{raza=" + raza + '}';
    }
}
