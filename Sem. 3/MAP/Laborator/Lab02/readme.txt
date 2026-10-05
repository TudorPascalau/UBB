Programul evaluează expresii cu numere complexe primite ca argumente în linia de comandă. O expresie conține minimum doi operanzi și același operator între ei: adunare, scădere, înmulțire sau împărțire. Evaluarea se face succesiv, de la stânga la dreapta, iar rezultatul este afișat în consolă.

Ideea principală este separarea interpretării datelor de crearea și evaluarea expresiei. "ComplexNumber" reprezintă un număr complex și implementează operațiile aritmetice. "NumberParser" definește contractul parsării unui număr, implementat de "ComplexNumberParser". "CommandLineExpressionParser" validează structura expresiei, identifică operația prin "Operation.fromSymbol" și parsează operanzii folosind acest contract. "ExpressionFactory" este interfața pentru crearea expresiilor, iar implementarea "DefaultExpressionFactory" deleagă crearea către operația aleasă. "ComplexExpression" definește algoritmul comun de evaluare.

Enumerarea "Operation" asociază fiecărei constante simbolul operatorului, păstrat în câmpul privat și final "symbol". Metoda statică "fromSymbol" parcurge tabloul constantelor returnat de "values()" și returnează constanta cu simbolul corespunzător; pentru un simbol necunoscut aruncă "IllegalArgumentException". Fiecare constantă implementează metoda abstractă "createExpression" și construiește expresia specifică. Soluția folosește comportament specific constantelor enum, fără lambda, referințe la constructori sau alte facilități introduse în Java 8 ori ulterior.

Cele patru clase concrete de expresii implementează operația specifică. Numerele complexe sunt imutabile: operațiile returnează obiecte noi, fără modificarea operanzilor. Operanzii unei expresii sunt păstrați într-un tablou "ComplexNumber[]".

------------------------------
Principii de proiectare SOLID

S - Single Responsibility Principle
Fiecare clasă are o responsabilitate clară: reprezentarea și aritmetica numerelor complexe, parsarea unui număr, interpretarea unei expresii, crearea expresiei sau evaluarea acesteia. Această separare permite modificarea unei responsabilități fără a amesteca logica ei cu celelalte.

O - Open/Closed Principle
"ComplexExpression" poate fi extinsă prin subclase care implementează "executeOperation", fără modificarea algoritmului din "evaluate". Interfața "ExpressionParser" permite introducerea altor implementări de parsare. Parserul folosește "Operation.fromSymbol", iar fabrica apelează polimorfic "operation.createExpression(operands)"; nu mai folosesc switch-uri pentru selectarea operației sau a clasei expresiei. Adăugarea unui operator nou presupune adăugarea unei subclase de expresie și a unei constante în "Operation", cu simbolul și implementarea metodei "createExpression". "Main", parserul și fabrica rămân neschimbate. Principiul este aplicat parțial la nivelul aplicației, deoarece enumerarea "Operation" trebuie în continuare modificată la extindere.

L - Liskov Substitution Principle
Clasele "AdditionExpression", "SubtractionExpression", "MultiplicationExpression" și "DivisionExpression" pot fi utilizate prin referințe de tip "ComplexExpression". Codul care evaluează expresia apelează aceeași metodă "evaluate", fără verificarea tipului concret. Evaluarea presupune operanzi valizi pentru operația aleasă; împărțirea la zero este semnalată prin excepție.

I - Interface Segregation Principle
Interfața "ExpressionParser" definește doar metoda "parse" pentru argumentele unei expresii, "NumberParser" definește doar metoda "parse" pentru textul unui număr, iar "ExpressionFactory" definește doar metoda "createExpression". Contractele sunt separate și restrânse; implementările lor nu sunt obligate să ofere operații de afișare sau alte funcționalități care nu țin de responsabilitatea respectivă.

D - Dependency Inversion Principle
"CommandLineExpressionParser" depinde de interfețele "NumberParser" și "ExpressionFactory", nu de clasele concrete "ComplexNumberParser" și "DefaultExpressionFactory". Câmpurile și parametrii constructorului au tipurile interfețelor, iar implementările concrete respectă aceste contracte. Astfel, parsarea numerelor sau crearea expresiilor poate fi înlocuită fără modificarea parserului expresiei. DIP este respectat pentru aceste colaborări ale parserului.
"Main" construiește implementările concrete și le furnizează prin constructor, apoi folosește abstracțiile "ExpressionParser" și "ComplexExpression" pentru parsare și evaluare. Construirea obiectelor concrete în punctul de configurare al aplicației este necesară și nu anulează inversarea dependențelor din parser. Adăugarea unei operații noi în enum nu necesită modificarea acestei configurări.
La nivelul întregii aplicații, aplicarea DIP are încă o limită: "Operation" cunoaște și instanțiază clasele concrete ale expresiilor. Interfețele noi elimină dependențele concrete ale parserului, dar nu elimină această legătură din enum.
-------------------------------------------------
Sabloane de proiectare

Simple Factory: 
Interfața "ExpressionFactory" oferă parserului contractul pentru crearea expresiilor prin metoda "createExpression". Clasa "DefaultExpressionFactory" implementează contractul, deleagă la "operation.createExpression(operands)" și returnează rezultatul prin tipul abstract "ComplexExpression". Alegerea constructorului este implementată în fiecare constantă a enum-ului "Operation", nu într-un switch al fabricii. Parserul nu instanțiază direct clasele expresiilor. Această organizare păstrează rolul de Simple Factory printr-un contract separat de implementarea sa; interfața nu reprezintă, singură, șablonul GoF Abstract Factory.
În diagrama UML, această organizare se regăsește în interfața "ExpressionFactory", în clasa "DefaultExpressionFactory" și în relația de realizare dintre ele. Metoda "createExpression" apare în contract, în implementare și ca metodă abstractă în "Operation". Enumerarea conține și atributul privat "symbol", constructorul privat "Operation(symbol: String)" și metoda statică "fromSymbol(symbol: String): Operation". Metoda veche "parseOperation" a fost eliminată din parser și din diagramă. Clasele concrete de expresii sunt legate prin generalizare de "ComplexExpression". Agregarea dintre "CommandLineExpressionParser" și interfața "ExpressionFactory" arată că parserul păstrează o referință prin contractul fabricii.

Template Method:
Metoda "evaluate" din "ComplexExpression" definește algoritmul comun: pornește de la primul operand, parcurge restul tabloului și apelează "executeOperation" la fiecare pas. În cod, "evaluate" este "final", iar "executeOperation" este abstractă. Fiecare subclasă implementează doar operația aritmetică specifică.
În diagrama UML, acest șablon se regăsește în clasa abstractă "ComplexExpression", în metodele "evaluate" și "executeOperation" și în relațiile de generalizare ale celor patru expresii concrete. Metodele "executeOperation" din subclase reprezintă implementările pasului variabil al algoritmului.

Injecția de dependențe prin constructor este o tehnică suplimentară folosită pentru colaboratorii parserului. Agregările din UML leagă "CommandLineExpressionParser" de interfețele "NumberParser" și "ExpressionFactory". Relațiile de realizare arată că "ComplexNumberParser" implementează "NumberParser", iar "DefaultExpressionFactory" implementează "ExpressionFactory". Atributul "numberParser" și parametrul cu același nume au tipul "NumberParser"; atributul "defaultExpressionFactory" și parametrul "expressionFactory" au tipul "ExpressionFactory", conform codului actual.
