# Seminar01 — exercitiile 1–5.1

Implementare conform `../Sem1_2_TaskRunner.pdf`, pana la StackContainer inclusiv.

- `Task`: constructor, get/set, `execute`, `toString`, `equals` si `hashCode`.
- `MessageTask`: afiseaza mesajul in formatul cerut, inclusiv data cu `yyyy-MM-dd hh:mm`.
- `SortingTask`: sorteaza si afiseaza vectorul folosind un `AbstractSorter`; strategii: BubbleSort si QuickSort.
- `Main`: creeaza un array de cinci MessageTask, le afiseaza, demonstreaza sortarile si executa mesajele in ordine LIFO.
- `StackContainer`: array redimensionabil, `add`, `remove`, `size`, `isEmpty`. Metoda `get` din proiectul initial este pastrata; indexul 0 reprezinta baza stivei.

`remove()` intoarce `null` pentru o stiva goala. Capacitatea initiala poate fi zero, dar nu negativa; `add(null)` este respins.

## Intrebarile de la exercitiul 1

`Task` este abstracta deoarece descrie un task general, fara o implementare comuna pentru executie. Subclasele definesc concret `execute()`; nu putem instantia direct `Task`.

`equals` compara identificatorul si descrierea numai intre obiecte de aceeasi clasa concreta (`getClass()`). Astfel se pastreaza simetria in relatia de mostenire: un MessageTask si un SortingTask nu sunt egale, chiar daca au acelasi identificator si aceeasi descriere. O subclasa care modifica `equals` trebuie sa respecte in continuare simetria si sa adapteze `hashCode`. Implementarea curenta foloseste aceleasi atribute pentru ambele metode, deci obiectele egale au acelasi hash code.

## Rulare si verificare

In IntelliJ IDEA se poate rula `src/Main.java`. Testele din `tests/Seminar01Test.java` sunt independente de JUnit; marcheaza `tests` drept Test Sources Root pentru a le rula din IDE.

Din PowerShell, in directorul Seminar01:

```powershell
New-Item -ItemType Directory -Force out | Out-Null
$sources = Get-ChildItem src, tests -Recurse -Filter *.java | Select-Object -ExpandProperty FullName
javac -encoding UTF-8 -d out $sources
java -cp out Main
java -cp out Seminar01Test
```

Testele verifica formatul mesajelor, executia taskurilor, contractul equals/hashCode, ambele sortari fata de rezultatul `Arrays.sort`, ordinea LIFO, redimensionarea si reutilizarea stivei.
