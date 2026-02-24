
def print_menu():
    """
    Afiseaza meniul principal al aplicatiei
    """
    print(" ---Gestionare concurenti---")
    print("     1. Adaugare concurent")
    print("     2. Inserare concurent")
    print("     3. Afisare concurenti")
    print("     4. Modificari concurenti")
    print("     5. Operatii subset")
    print("     6. Operatii filtrare")
    print("     7. Adauga exemple concurenti")
    print("     8. Undo")
    print("     x. Iesire din aplicatie")

def print_menu_afisare():
    """
    Afiseaza submeniul pentru operatii de afisari
    """
    print("     1.Tiparire concurenti care au un scor mai mic decat un scor dat")
    print("     2.Tiparire concurenti ordonati dupa scor")
    print("     3.Tiparire participanti care au un scor mai mare decat un scor dat, ordonat dupa scor")

def print_menu_modif():
    """
    Afiseaza submeniul pentru operatii de modificare
    """
    print("     1. Modificare scor concurent")
    print("     2. Stergere note concurent")
    print("     3. Stergere note interval concurenti")

def print_menu_subset():
    """
    Afiseaza submeniul pentru operatii pe un subset de concurenti
    """
    print("     1. Calculeaza media scorurilor unui interval de concurenti")
    print("     2. Calculeaza scorul minim unui interval de concurenti")
    print("     3. Tipareste participantii care au scorul multiplu de 10")

def print_menu_filtrare():
    """
    Afiseaza submeniul pentru filtrari
    """
    print("     1. Filtrare participanti cu scorul multiplu de un numar dat")
    print("     2. Filtrare participanti cu scorul mai mic decat un scor dat")