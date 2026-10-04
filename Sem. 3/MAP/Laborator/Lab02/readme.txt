**Principiile OOP**

Aplicația folosește încapsularea prin atribute private și metode care oferă acces controlat la comportamentul obiectelor. În `ComplexNumber`, componentele reală și imaginară sunt `private final`, iar operațiile creează obiecte noi, fără să modifice operanzii. În `ComplexExpression`, copierea tabloului primit prin constructor protejează expresia față de modificarea ulterioară a tabloului original.

Abstractizarea este realizată prin interfața `ExpressionParser` și clasa abstractă `ComplexExpression`. Interfața definește contractul pentru transformarea argumentelor într-o expresie, iar clasa abstractă definește mecanismul comun de evaluare, fără să fixeze operația aritmetică.

Moștenirea permite claselor `AdditionExpression`, `SubtractionExpression`, `MultiplicationExpression` și `DivisionExpression` să reutilizeze algoritmul din `ComplexExpression`. Fiecare clasă implementează doar operația specifică prin `executeOperation`.

Polimorfismul apare atunci când aplicația lucrează cu o referință `ComplexExpression`, iar apelul `executeOperation` execută implementarea clasei concrete. De asemenea, `Main` utilizează parserul prin tipul `ExpressionParser`, ceea ce permite schimbarea implementării de parsare.

Agregarea exprimă colaborarea dintre `CommandLineExpressionParser`, `ComplexNumberParser` și `ExpressionFactory`. Colaboratorii sunt primiți din exterior și pot exista sau fi reutilizați independent de parser.

**Principiile SOLID**

**S — Single Responsibility Principle.** Responsabilitățile sunt separate: `ComplexNumber` implementează aritmetica numerelor complexe, `ComplexNumberParser` interpretează un număr, `CommandLineExpressionParser` verifică și interpretează expresia, `ExpressionFactory` selectează obiectul potrivit, iar clasele de expresii realizează evaluarea. Astfel, schimbarea formatului de intrare nu necesită modificarea formulelor matematice.

**O — Open/Closed Principle.** Algoritmul comun din `ComplexExpression` poate fi extins prin introducerea unei subclase care implementează `executeOperation`, fără modificarea metodei `evaluate`. Interfața `ExpressionParser` permite adăugarea altor parsere. Principiul este aplicat parțial la nivelul întregii aplicații: introducerea unui operator nou necesită și modificarea enumerării `Operation`, a fabricii și a interpretării operatorilor.

**L — Liskov Substitution Principle.** Cele patru expresii concrete pot fi utilizate prin tipul `ComplexExpression`: toate acceptă operanzi complecși și implementează aceeași semnătură pentru operația binară. Algoritmul de evaluare funcționează fără verificări ale tipului concret. Împărțirea la zero este tratată ca un caz matematic invalid; contractul de evaluare trebuie să permită semnalarea acestuia prin excepție.

**I — Interface Segregation Principle.** `ExpressionParser` are un contract restrâns, format din metoda `parse`. Implementările nu sunt obligate să ofere funcții de afișare, calcul aritmetic sau creare a expresiilor care nu țin de responsabilitatea lor.

**D — Dependency Inversion Principle.** `Main` folosește abstracțiile `ExpressionParser` și `ComplexExpression` pentru parsare și evaluare. Totuși, principiul este aplicat parțial: `CommandLineExpressionParser` depinde de tipurile concrete `ComplexNumberParser` și `ExpressionFactory`. Primirea acestora prin constructor reprezintă injecție de dependențe, dar nu este, singură, o aplicare completă a DIP.

**Șabloanele de proiectare**

Aplicația folosește **Template Method**: metoda finală `evaluate` stabilește pașii evaluării, iar metoda abstractă `executeOperation` reprezintă pasul particularizat de subclase.

`ExpressionFactory` implementează o **Simple Factory**, centralizând selectarea și instanțierea expresiilor. Parserul solicită o expresie prin fabrică și primește rezultatul prin tipul abstract `ComplexExpression`. Implementarea nu reprezintă șablonul GoF Factory Method, deoarece alegerea nu este delegată unor subclase ale fabricii.

Interfața `ExpressionParser` permite implementări alternative de parsare, care pot fi alese la construirea aplicației. Această organizare susține schimbarea comportamentului de parsare fără modificarea evaluării matematice.

**Legătura cu cerințele laboratorului**

Aplicația preia argumentele din linia de comandă prin `Main.main`. `CommandLineExpressionParser` verifică existența a minimum doi operanzi, alternanța număr–operator, argumentele necompletate și utilizarea aceluiași operator în întreaga expresie.

Cele patru operații solicitate sunt reprezentate prin enumerarea `Operation` și clasele concrete de expresii. `ComplexExpression.evaluate` aplică operația succesiv, de la stânga la dreapta, iar `Main` afișează rezultatul.

Proiectarea urmează sugestiile laboratorului: o clasă pentru numărul complex, un parser care implementează o interfață, clase distincte pentru operații și folosirea șabloanelor de proiectare. Organizarea în pachetele `model`, `parser` și `expression` separă componentele aplicației.

Restricția privind utilizarea tablourilor este respectată prin `ComplexNumber[]`; nu sunt folosite colecții generice predefinite sau stream-uri.

Conformitatea funcțională rămâne incompletă până la corectarea coeficientului imaginar omis, deoarece PDF-ul include explicit forma `-2+i`.