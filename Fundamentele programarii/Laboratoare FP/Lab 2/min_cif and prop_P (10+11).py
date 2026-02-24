# P1: Se da un numar natural n. Sa se determine cel mai mic numar care se poate forma cu cifrele lui n.
def problema_1():
    n = input("Introduceti numarul natural n: ")

    if n.isdigit() == False:
        print("Nu ati introdus un numar natural")

    else:
        n = int(n)
        
        cifre = []
        result = 0

        while n > 0:
            cifre.append(n%10)
            n //= 10

        cifre.sort()

        index_dif_zero = 0
        while cifre[index_dif_zero] == 0:
            index_dif_zero += 1

        result = cifre[index_dif_zero]
        cifre.pop(index_dif_zero)

        for cif in cifre:
            result = result*10 + cif

        print("Cel mai mic numar care se poate forma cu cifrele lui n este",result)

# P2: Numerele n1 si n2 au proprietatea P daca scrierea lor in baza 10 foloseste aceleasi cifre. Determinati daca doua numere naturale au proprietatea P.
def problema_2():
    
    n1 = input("Introduceti primul numar natural: ")
    n2 = input("Introduceti al doilea numar natural: ")

    if n1.isdigit() == False or n2.isdigit() == False:
        print("Nu ati introdus numere naturale")
        
    else:
        n1 = int(n1)
        n2 = int(n2)
        
        if set(str(n1)) == set(str(n2)):
            print("Cele doua numere au proprietatea P")
        else:
            print("Cele doua numere nu au proprietatea P")
            

def main():
    
    cerinta = int(input("Introduceti numarul problemei pe care doriti sa o rezolvati: "))

    if cerinta == 1:
        problema_1()
        
    elif cerinta == 2:
        problema_2()
        
    else:
        print("Nu ati introdus un numar valid")
        main()

main()
