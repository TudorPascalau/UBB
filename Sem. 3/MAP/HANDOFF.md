# MAP — predare între proiectele locale

Ultima actualizare: 4 octombrie 2026  
Folder MAP: `E:\Facultate\UBB\Sem. 3\MAP`  
Celălalt proiect local: numele și calea nu au fost încă precizate.

## Scop și utilizare

Acest fișier este punctul comun de context pentru continuarea lucrului din MAP sau din celălalt proiect local. La începutul unei sesiuni, citește acest document și verifică fișierele relevante. La final, actualizează secțiunea „Ultima sesiune” cu ce s-a realizat efectiv, verificările făcute și următorul pas.

Din celălalt proiect, citește și actualizează fișierul original de la `E:\Facultate\UBB\Sem. 3\MAP\HANDOFF.md`, dacă ai acces. Dacă lucrezi cu o copie, precizează data și proiectul sursă și reconciliază modificările cu originalul. Documentul transmite context; nu sincronizează automat codul și nu pornește comunicarea între proiecte.

## Starea curentă observată

Inventar bazat pe citirea surselor la 3 octombrie 2026. Acesta nu reprezintă un istoric confirmat al sesiunilor anterioare.

| Zonă | Ce există | Stare observată |
| --- | --- | --- |
| `Curs` | `curs1.pdf` | Material de curs; conținutul nu a fost analizat în această sesiune. |
| `Laborator/Lab01` | Clasele `Car`, `AudiCar`, `PorscheCar`, `Application`; `exemplu.mdj` | Exemplu Java de moștenire și polimorfism. |
| `Laborator/Lab02` | `Lab1_2026-2027.pdf` și proiectul `Laborator02` | Calculator de expresii cu numere complexe, organizat în `model`, `expression` și `parser`. |
| `Seminar/Seminar 1` | `Task`, `MessageTask`, `Container`, `StackContainer`, `Main` | Implementare în lucru; `Main` și `StackContainer` conțin cod incomplet. |

### Laborator 02 — context pentru continuare

- `ComplexNumber` are câmpuri finale și operații de adunare, scădere, înmulțire și împărțire; împărțirea la zero aruncă o excepție.
- `ComplexExpression` evaluează operanzii succesiv, de la stânga la dreapta. Clasele derivate implementează cele patru operații, iar `ExpressionFactory` selectează expresia.
- `CommandLineExpressionParser` citește argumentele în alternanță număr/operator și cere ca toți operatorii să fie identici.
- `ComplexNumberParser` folosește o expresie regulată și elimină spațiile dintr-un număr.
- De verificat: coeficientul imaginar omis în forme precum `1+i` este tratat în codul actual ca `0.0`; dacă forma este acceptată, coeficientul așteptat este `1.0`. Gruparea alternativelor din expresia regulată merită verificată pentru semne și zecimale.
- Cerințele din PDF nu au fost confruntate cu implementarea. Compilarea și execuția nu au fost verificate în această sesiune.

### Seminar 1 — lucru rămas vizibil

- Completarea instrucțiunii `MessageTask task1 =` din `Main`.
- Implementarea metodelor `remove`, `add`, `size` și `get` din `StackContainer`.
- Corectarea referințelor `Tasks` la câmpul `tasks` și eliminarea fragmentului izolat `T`.
- Clarificarea utilizării parametrului de capacitate din constructorul `StackContainer`.

## Ultima sesiune

- **Data:** 5 octombrie 2026.
- **Proiect sursă:** MAP.
- **Obiectiv:** sincronizarea README-ului și diagramei UML cu interfețele introduse pentru DIP.
- **Realizat:** adăugarea NumberParser și transformarea contractului ExpressionFactory în interfață în UML; reprezentarea DefaultExpressionFactory și a realizărilor ComplexNumberParser -> NumberParser și DefaultExpressionFactory -> ExpressionFactory. Actualizarea atributelor și constructorului parserului, inclusiv numele actual defaultExpressionFactory; agregările parserului sunt către interfețe. README-ul descrie contractele, injecția în Main, efectul asupra DIP/ISP și limita rămasă în Operation.
- **Fișiere modificate:** Laborator/Lab02/readme.txt, Laborator/Lab02/Lab02.mdj și HANDOFF.md. Sursele Java au fost doar citite.
- **Verificări:** confruntarea cu sursele Java actuale, JSON valid, identificatori unici și fără referințe invalide noi; casetele interfețelor noi nu se suprapun cu parserul. Fără compilare Java sau verificare vizuală în StarUML, fiind actualizate documentația și modelul.
- **Decizii relevante:** DIP este respectat pentru colaboratorii parserului; Operation încă instanțiază clasele concrete ale expresiilor. Main construiește implementările, dar rămâne stabil când se adaugă operații în enum.
- **Următorul pas:** revizuirea vizuală a diagramei în StarUML.
## Model pentru actualizări viitoare

Înlocuiește secțiunea „Ultima sesiune” cu datele reale ale sesiunii încheiate. Actualizează și starea curentă dacă implementarea s-a schimbat. Păstrează mai jos un rezumat scurt al sesiunii precedente când este util.

```text
Data:
Proiect sursă și cale:
Obiectiv:
Realizat:
Fișiere modificate:
Verificări și rezultate:
Decizii relevante:
Probleme / informații lipsă:
Următorul pas concret:
```

## Istoric scurt

- 2026-10-03 — Document inițial creat în rădăcina MAP; starea surselor inventariată, fără modificări de cod.
- 2026-10-04 — Completarea claselor și a enumerării din `Lab02.mdj` conform codului Java, fără relații.
- 2026-10-04 — Ajustarea relațiilor adăugate de utilizator, fără legături suplimentare ale fabricii către clasele concrete.
- 2026-10-04 — Verificarea variantei finale și a PDF-ului; compilare reușită, identificarea erorii pentru coeficientul imaginar omis și a elementelor UML rămase în model.




