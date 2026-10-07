Programul evaluează expresii cu numere complexe primite din linia de comandă. Numerele și expresiile sunt obiecte separate: numerele oferă operațiile aritmetice, iar expresiile pot fi evaluate și extinse cu noi tipuri de operații. Fiecare expresie are minimum doi operanzi și același operator între ei.

------------------------------
Principii de proiectare SOLID

S - Single Responsibility Principle
Fiecare clasă are o responsabilitate clară: reprezentarea și aritmetica numerelor complexe (clasa ComplexNumber), parsarea unui număr (NumberParser), interpretarea unei expresii (ComplexExpression), crearea expresiei sau evaluarea acesteia. Această separare permite modificarea unei responsabilități fără a amesteca logica ei cu celelalte.

O - Open/Closed Principle
Codul este inchis modificarii deoarece algoritmii de creare si evaluare a expresiilor se bazeaza pe interfete (ExpressionFactory, ExpressionParser) ce pot fi extinse prin subclase noi pentru adaugarea unor functionalitati noi.

L - Liskov Substitution Principle
Clasele derivate (expresiile pentru adunare, scădere, înmulțire și împărțire) pot fi folosite în locul clasei de bază (ComplexExpression), deoarece toate respectă același mod de evaluare.

I - Interface Segregation Principle
Interfețele au responsabilități separate și oferă doar metodele necesare: parsarea unui număr (NumberParser), interpretarea unei expresii (ExpressionParser) și crearea acesteia (ExpressionFactory). Alegem câteva interfețe mai mici, separate, peste una mare ce conține toate metodele la un loc.

D - Dependency Inversion Principle
Parserul expresiei depinde de abstracții (NumberParser, ExpressionFactory), primite prin constructor, astfel încât parsarea numerelor și crearea expresiilor pot fi înlocuite fără modificarea lui.

------------------------------
Șabloane de proiectare

Simple Factory
Crearea expresiilor este centralizată într-o fabrică (DefaultExpressionFactory), care alege clasa potrivită operației și permite parserului să obțină expresia fără să cunoască modul de construire.

Template Method
Clasa de bază (ComplexExpression) definește algoritmul comun de evaluare (evaluate), iar clasele derivate implementează doar operația specifică (executeOperation).
