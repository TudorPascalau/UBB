# Programare multi modul

### Modularizare
+ Program -> unitati logice
+ Cod (al unitatilor)
+ Obj -> fisier binar

### Reutilizarea de cod
+ Refolosire cod -> ==#include NU este multi-modul==
+ Trebuie preluat din alt fisier

~~~
%ifndef
%define
.....
%endif
~~~
==Not true multi modul==

# True multi-modul:
 + N unitati de cod - asamblate / compilate separat
 + Aduse impreuna de link editor

## Sumar responsabilitati:
 1. Pre-procesare
 2. Asamblor
 3. Compilator
 4. Linkeditor - fisiere obiect **.obj** => biblioteca sau program

## Cerinte NASM multi-modul:
+ Directive / etichete noi :
	 + global - accesibil catre toti
	 + extern - solicita acces la fisier
+ Solicitare fara disponibilitate = eroare!
+ Limbaje nivel mai inalt ofera constructii sintactice cu rol echivalent

## Legare statica la linkeditare
 + Unirea mai multor fisiere binare
	 + Intrari: *.obj* si *.lib*
	 + Iesire *.exe*
+ Modularizarea codului in asamblare
~~~
	  call eticheta
	  ret [n]
 ~~~

# Pasii necesari construirii programului executabil final
 + Se asambleaza fisierul main.asm
	 + `nasm.exe - fobj main.asm`
+ Se aseambleaza fisierul sub.asm
	+ `nasm.exe - fobj sub.asm`
+ Se editeaza legaturile dintre cele doua module
	+ `alink.exe main.obj, sub.obj, ...`

### Observatii useful
 + View paralel
 + Pot exista etichete cu acelasi nume in diferite module cat timp nu sunt globale
 + Preferabil sa existe un singur `global start`
 + Codul merge secvential -> o data intrat in alt program merge pana la iesire / alt apel
 + ==Adauga NASM in PATH== , altfel:
 + ==ALINK.EXE si NASM.EXE in root directory==
 + Atentie la - si - mai lung
 + ==Fiecare modificare necesita reasamblare / linkare==

#### Transmitere parametrii prin REGISTRII / STIVA
 + Registrii si stiva raman constanti intre module - parte universala
   
