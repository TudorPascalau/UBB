------------------------------
Principii de proiectare SOLID

S - Single Responsibility Principle
Fiecare clasă are o responsabilitate clară: reprezentarea numerelor complexe (ComplexNumber), parsarea unui număr (ComplexNumberParser), interpretarea unei expresii (CommandLineExpressionParser), crearea expresiei (ComplexExpressionFactory) sau evaluarea acesteia (ComplexExpression). Această separare permite modificarea unei responsabilități fără a amesteca logica ei cu celelalte.

O - Open/Closed Principle
Moștenirea din ComplexExpression permite adăugarea unor expresii noi fără modificarea algoritmului evaluate. Interfețele permit înlocuirea implementărilor numerelor, expresiilor, parserelor și fabricii, precum poate fi văzut în diagrama UML. Principiul este aplicat parțial: adăugarea unei operații noi necesită modificarea enumerării Operation și a selecției din ComplexExpressionFactory.

L - Liskov Substitution Principle
Clasele derivate (expresiile pentru adunare, scădere, înmulțire și împărțire) pot fi folosite în locul clasei de bază (ComplexExpression), deoarece toate respectă același mod de evaluare. În UML, acest principiu este reprezentat prin relațiile de generalizare dintre cele patru expresii concrete și ComplexExpression.

I - Interface Segregation Principle
Interfețele au responsabilități separate și oferă doar metodele necesare: operații aritmetice (Number), evaluarea unei expresii (Expression), parsarea unui număr (NumberParser), interpretarea unei expresii (ExpressionParser) și crearea acesteia (ExpressionFactory). În UML apar cinci interfețe mici și distincte, realizate de clasele corespunzătoare.

D - Dependency Inversion Principle
Parserul expresiei depinde de abstracții (NumberParser, ExpressionFactory), primite prin constructor, și lucrează cu Number și Expression, astfel încât parsarea numerelor și crearea expresiilor pot fi înlocuite fără modificarea lui. În UML, CommandLineExpressionParser este asociat cu interfețele NumberParser și ExpressionFactory, iar implementările concrete realizează aceste interfețe.

------------------------------
Șabloane de proiectare

Simple Factory
Crearea expresiilor este centralizată în ComplexExpressionFactory, care realizează ExpressionFactory. Interfața primește Number[] și returnează Expression, iar fabrica concretă verifică și convertește operanzii în ComplexNumber[] și returnează ComplexExpression. Selectează expresia concretă în funcție de Operation și permite parserului să obțină expresia fără să cunoască modul de construire.

Template Method
Clasa de bază (ComplexExpression) definește algoritmul comun de evaluare (evaluate), iar clasele derivate implementează doar operația specifică (executeOperation).
