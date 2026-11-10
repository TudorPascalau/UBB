package IF;

/**
 * Ce este o interfata functionala: o interfata cu O SINGURA metoda abstracta.
 * Aceeasi operatie scrisa in trei feluri: clasa anonima, lambda, referinta la metoda.
 */
public class Ex1_InterfataFunctionala {

    // TODO 1. Definiti interfata functionala Operatie (marcati-o cu @FunctionalInterface) care contine:
    //   a) metoda abstracta calculeaza, care primeste doua numere reale si intoarce un numar real;
    //   b) metoda default laPatrat(double x), care intoarce rezultatul lui calculeaza(x, x);
    //   c) metoda statica aduna(double a, double b), care intoarce suma celor doua numere.
    // Intrebare: de ce interfata ramane functionala, desi are trei metode?
    @FunctionalInterface
    interface Operatie {
        double calculeaza(double a, double b);       // singura metoda abstracta

        default double laPatrat(double x) {          // metodele default nu conteaza
            return calculeaza(x, x);
        }
        static double aduna(double a, double b) {
            return a + b;
        }
    }

    public static void main(String[] args) {
        // TODO 2. Creati un obiect Operatie numit inmultire, folosind o CLASA ANONIMA,
        //         care inmulteste cele doua numere.
        // clasa anonima: mult cod pentru o singura formula
        Operatie inmultire = new Operatie() {
            @Override
            public double calculeaza(double a, double b) {
                return a * b;
            }
        };

        // TODO 3. Creati un obiect Operatie numit inmultireLambda, folosind o LAMBDA,
        //         care inmulteste cele doua numere.
        // lambda: doar parametrii si corpul
        Operatie inmultireLambda = (a, b) -> a * b;

        // TODO 4. Creati un obiect Operatie numit adunare, folosind o REFERINTA LA METODA
        //         catre metoda statica aduna din Operatie.
        // referinta la o metoda existenta, cu aceeasi forma (double, double) -> double
        Operatie adunare = Operatie::aduna;

        Operatie maxReferinta=Math::max; // referinta la metoda statica Math.max

        // TODO 5. Afisati:
        //   - inmultire.calculeaza(3, 4)        -> 12.0
        //   - inmultireLambda.calculeaza(3, 4)  -> 12.0
        //   - adunare.calculeaza(3, 4)          -> 7.0
        //   - inmultireLambda.laPatrat(5)       -> 25.0
        // Bonus: ce afiseaza adunare.laPatrat(5)? De ce?
        System.out.println(inmultire.calculeaza(3, 4));        // 12.0
        System.out.println(inmultireLambda.calculeaza(3, 4));  // 12.0
        System.out.println(adunare.calculeaza(3, 4));          // 7.0
        System.out.println(inmultireLambda.laPatrat(5));       // 25.0 (metoda default)
        System.out.println(adunare.laPatrat(5));               // 10.0 (laPatrat apeleaza calculeaza = aduna)
    }
}
