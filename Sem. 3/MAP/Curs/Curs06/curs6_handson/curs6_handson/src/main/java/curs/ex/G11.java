package curs.ex;

/**
 * Quiz: what does the program print? (this in an anonymous class vs. this in a lambda)
 */
public class G11 {

    private final String nume = "G11";

    /**
     * runs the same action written as an anonymous class and as a lambda
     */
    void ruleaza() {
        Runnable anonima = new Runnable() {
            private final String nume = "anonima";

            @Override
            public void run() {
                System.out.println("clasa anonima: " + this.nume);
            }
        };
        Runnable lambda = () -> System.out.println("lambda:        " + this.nume);

        anonima.run();
        lambda.run();
    }

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        new G11().ruleaza();
    }
}
