package IF_handson;

/**
 * Hands-on 1: interfata functionala.
 * O interfata functionala are O SINGURA metoda abstracta.
 */
public class Ex1_InterfataFunctionala {

    // TODO 1. Definiti interfata functionala Operatie (marcati-o cu @FunctionalInterface) care contine:
    //   a) metoda abstracta calculeaza, care primeste doua numere reale si intoarce un numar real;
    //   b) metoda default laPatrat(double x), care intoarce rezultatul lui calculeaza(x, x);
    //   c) metoda statica aduna(double a, double b), care intoarce suma celor doua numere.
    // Intrebare: de ce interfata ramane functionala, desi are trei metode?



    public static void main(String[] args) {
        // TODO 2. Creati un obiect Operatie numit inmultire, folosind o CLASA ANONIMA,
        //         care inmulteste cele doua numere.

        // TODO 3. Creati un obiect Operatie numit inmultireLambda, folosind o LAMBDA,
        //         care inmulteste cele doua numere.

        // TODO 4. Creati un obiect Operatie numit adunare, folosind o REFERINTA LA METODA
        //         catre metoda statica aduna din Operatie.

        // TODO 5. Afisati:
        //   - inmultire.calculeaza(3, 4)        -> 12.0
        //   - inmultireLambda.calculeaza(3, 4)  -> 12.0
        //   - adunare.calculeaza(3, 4)          -> 7.0
        //   - inmultireLambda.laPatrat(5)       -> 25.0
        // Bonus: ce afiseaza adunare.laPatrat(5)? De ce?
    }
}
