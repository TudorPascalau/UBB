"""
Aplicatie de gestionare a participantilor la un concurs de informatica
"""

def creeaza_concurent(numar, note):
    """
    Creeaza un concurent cu numarul de concurs si lista de note data
    :param numar: int, numar concurs > 0
    :param note: lista int, 10 note de la 1 la 10
    :return: dictionar, reprezinta concurentul
    """

    # Scorul final reprezinta media aritmetica a concurentului sau 0 daca acesta nu are note
    if len(note) == 0:
        scor_final = 0
    else:
        scor_final = sum(note)/len(note)

    # Reprezentam un concurent sub forma unui dictionar
    return {
        "numar": numar,
        "note": note,
        "scor_final": scor_final
    }

def get_numar_concurent(concurent):
    return concurent["numar"] # Returneaza numarul de concurs al concurentului

def get_note_concurent(concurent):
    return concurent["note"] # Returneaza lista cu notele la cele 10 probe

def get_scor_concurent(concurent):
    return concurent["scor_final"] # Returneaza scorul final al concurentului

def get_concurent_from_numar(concurenti, numar):
    """
    Asocierea unui concurent cu un numar de concurs dat
    :param concurenti: Lista de concurenti in care cautam
    :param numar: Numarul
    :return: concurentul, daca numarul dat i se asociaza
             None, daca numarul dat nu are un concurent asociat
    """
    for concurent in concurenti[1:]:
        if get_numar_concurent(concurent) == numar:
            return concurent

    return None

def test_get_concurent_from_numar():
    """
    Functie de test pentru get_concurent_from_numar()
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti,305,[10, 9, 8, 7, 9, 10, 8, 9, 9, 10])

def get_poz_from_numar(concurenti, numar):
    """
    Asocierea pozitiei unui concurent cu un numar de concurs dat
    :param concurenti: Lista de concurenti in care cautam
    :param numar: Numarul
    :return: pozitia concurentului, daca numarul dat i se asociaza
             None, daca numarul dat nu are un concurent asociat
    """
    for index in range(1,len(concurenti)):
        if get_numar_concurent(concurenti[index]) == numar:
            return index

    return None

def test_get_poz_from_numar():
    """
    Functie de test pentru get_poz_from_numar()
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])

    assert get_poz_from_numar(concurenti, 305) == 1
    assert get_poz_from_numar(concurenti, 310) == 2
    assert get_poz_from_numar(concurenti, 999) is None

def valideaza_concurent(concurent, concurenti):
    """
    Verifica daca concurentul 'concurent' este valid
    :param concurent: concurentul de verificat
    :param concurenti: lista de concurenti in care se afla concurentul
    :return: True, daca concurentul este valid
             False, daca nu
    """

    erori = []

    # validare numar
    if get_numar_concurent(concurent) <= 0:
        erori.append("Numarul nu este valid")

    # validare unicitate numar
    for index in range(1,len(concurenti)):
        if get_numar_concurent(concurenti[index]) == get_numar_concurent(concurent):
            erori.append("Numarul de concurs mai apare o data")

    # validare note
    for nota in get_note_concurent(concurent):
        if not 1 <= nota <= 10:
            erori.append("Notele nu sunt valide")

    if erori:
        print(erori)
        return False
    return True

def test_creeaza_concurent():
    """
    Functie de test pentru creeaza_concurent()
    """
    concurent = creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert get_numar_concurent(concurent) == 305
    assert len(get_note_concurent(concurent)) == 10
    assert get_note_concurent(concurent)[0] == 10
    assert get_scor_concurent(concurent) == 8.9



def adauga_concurent(concurenti, numar, note):
    """
    Adauga un concurent in lista 'concurenti'

    :param concurenti: lista dictionare, in care va fi adaugat concurentul
    :param numar: int, numarul de concurs al concurentului
    :param note: lista int, 10 note de la 1 la 10

    :return True, daca a fost adaugat concurentul
            False, daca nu
    """

    concurent = creeaza_concurent(numar, note) # Crearea unui concurent cu numarul si notele date
    if not valideaza_concurent(concurent,concurenti): #Verificarea concurentului
        return False

    concurenti.append(concurent) # Adaugarea concurentului in lista de concurenti
    return True

def test_adauga_concurent():
    """
    Functie de test adauga_concurent()
    """
    concurenti = ["filler"]

    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])

    assert len(concurenti) == 2
    assert get_numar_concurent(concurenti[1]) == 305


def inserare_concurent(concurenti,poz, numar, note):
    """
    Inserare in lista 'concurenti' pe pozitia 'poz' a unui concurent
    :param concurenti: lista dictionare
    :param poz: int, pozitia in lista in care va fi inserat concurentul
    :param numar: int, numarul de concurs
    :param note: lista int, note de la 1 la 10
    :return: Noul sir de concurenti
    """

    concurent_nou = creeaza_concurent(numar, note)
    if valideaza_concurent(concurent_nou,concurenti):

        lungime = len(concurenti) - 1 # Lungimea sirului de concurenti, fara elementul de filler
        concurenti.append(concurenti[lungime]) #Copierea ultimului concurent, intr-o noua pozitie

        for index in range(lungime, poz, -1): #Mutarea concurentilor cu o pozitie mai in fata
            concurenti[index] = concurenti[index - 1]

        concurenti[poz] = concurent_nou #Inserarea unui concurent pe noua pozitie

    else:
        print("Eroare la inserare")

    return concurenti

def test_inserare_concurent():
    """
    Functie de test pentru inserare_concurent()
    """
    concurenti = ["filler"]

    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1])
    assert get_numar_concurent(concurenti[1]) == 305

    concurenti = inserare_concurent(concurenti,1, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1])
    assert get_numar_concurent(concurenti[1]) == 310

def adaugaConcurent(concurenti):
    """
    UI pt adaugare concurent
    """
    numar = int(input("Numar: ")) #Numarul de concurs
    valori_probe = input("Valori probe: ") #Notele la cele 10 probe
    note = [int(nota) for nota in valori_probe.split()] #Transformare string note in lista

    concurent = creeaza_concurent(numar, note) #Creare concurent cu informatiile date

    #Validare si adaugare concurent
    if valideaza_concurent(concurent,concurenti):
        adauga_concurent(concurenti, numar, note)
        print(f"Concurentul a fost adaugat pe pozitia {get_poz_from_numar(concurenti,numar)}.")

    else:
        print("Eroare la adaugare concurent!")


def inserareConcurent(concurenti):
    """
    UI pt inserare concurent
    """

    numar = int(input("Numar: ")) #Numarul de concurs
    valori_probe = input("Valori probe: ") #Notele la cele 10 probe
    note = [int(nota) for nota in valori_probe.split()] #Transformare string note in lista
    poz = int(input("Pozitie: ")) #Pozitia de inserare

    concurent = creeaza_concurent(numar, note) #Creare concurent cu informatiile date

    #Validare si inserare concurent
    if valideaza_concurent(concurent,concurenti):
        print(f"Concurentul a fost inserat pe pozitia {poz}")
        concurenti = inserare_concurent(concurenti, poz, numar, note)

    else:
        print("Eroare la inserare concurent!")

    return concurenti

def afisareConcurent(concurent):
    """
    UI pt afisare concurent
    """
    print(f"Numar: {get_numar_concurent(concurent)}")
    print(f"Note: {get_note_concurent(concurent)}")
    print(f"Scor: {get_scor_concurent(concurent)}")
    print()

def comparare_scor(concurent, scor_comp, ineg):
    """
    Compara scorul unui concurent cu un scor dat
    :param concurent: concurentul dat
    :param scor_comp: scorul de comparat
    :param ineg: -1, daca comparam pt scor concurent < scor dat
                 1, daca comparam pt scor concurent > scor dat
    :return: True, daca comparatia e adevarata
             False, altfel
    """

    if ineg == -1: #Compara daca scor concurent < scor dat
        if not get_scor_concurent(concurent) < scor_comp:
            return False

    elif ineg == 1: #Compara daca scor concurent > scor dat
        if not get_scor_concurent(concurent) > scor_comp:
            return False

    return True

def test_comparare_scor():
    """
    Functie de test pentru comparare scor
    """

    concurent = creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert comparare_scor(concurent,8.5,1)
    assert comparare_scor(concurent,9.5,-1)

def afisareConcurentiComparareScor(concurenti):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mic decat un scor dat
    :param concurenti: lista dictionare, retine concurentii
    """

    scor = float(input("Introduceti scorul: ")) # Preluarea de la utilizator a scorului
    for concurent in concurenti[1:]:
        if comparare_scor(concurent, scor, -1): #Apelarea functiei de comparatie pentru scor concurent < scor dat
            afisareConcurent(concurent) #Afisarea concurentiilor care au un scor mai mic decat cel dat


def sortare_scor(concurenti):
    """
    Sortarea concurentilor in ordine crescatoare a scorului
    :param concurenti: Lista de concurenti
    :return: Lista de concurenti sortata
    """

    # Pastreaza concurenti[0] == "filler" si sorteaza restul dupa scor
    return [concurenti[0]] + sorted(concurenti[1:], key = lambda x: x["scor_final"], reverse=True)


def test_sortare_scor():
    """
    Functie de test pentru sortare_scor
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 10, 10])

    assert get_numar_concurent(concurenti[1]) == 305

    concurenti = sortare_scor(concurenti)
    assert get_numar_concurent(concurenti[1]) == 310

def afisareConcurentiOrdonareScor(concurenti):
    """
    Implementare UI I/O pentru afisarea concurentilor ordonati dupa valoarea scorului
    :param concurenti:
    """

    concurenti = sortare_scor(concurenti) #Sortarea concurentilor
    for concurent in concurenti[1:]:
        afisareConcurent(concurent)

def afisareConcurentiOrdonareComparare(concurenti):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mare decat un scor dat, sortati dupa valoarea scorului
    """

    scor = float(input("Introduceti scorul: "))  # Preluarea de la utilizator a scorului

    concurenti = sortare_scor(concurenti)  #Ordonarea concurentilor dupa scor
    for concurent in concurenti[1:]:
        if comparare_scor(concurent, scor, 1): #Apelarea functiei de comparatie pentru scor concurent > scor dat
            afisareConcurent(concurent) #Afisarea concurentiilor care au un scor mai mare decat cel dat

def modifica_scor(concurent, note_noi):
    """
    Modifica notele concurentului 'concurent' cu notele din note_noi
    :param concurent: dictionar concurent
    :param note_noi: lista int, 10 note de la 1 la 10
    :return: Noul concurent
    """

    concurent["note"] = note_noi
    concurent["scor_final"] = sum(note_noi) / len(note_noi)

    return concurent

def test_modifica_scor():
    """
    Functie de test pentru modifica_scor
    """
    concurent = creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert get_note_concurent(concurent)[0] == 10

    concurent = modifica_scor(concurent, [9, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert get_note_concurent(concurent)[0] == 9

def modifica_scor_concurenti(concurenti, numar, note_noi):
    """
    Updateaza sirul 'concurenti' dupa modificarea unui concurent
    :param concurenti: Lista de concurenti
    :param numar: Numarul concurentului caruia i se modifica notele
    :param note_noi: Notele ale concurentului
    :return: Lista de concurenti modificata
    """

    # Determinarea pozitiei in lista a conncurentului in functie de numar
    poz = get_poz_from_numar(concurenti, numar)
    if poz is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti_noi = concurenti[:] #Copierea listei de concurenti

    #Modificarea listei cu noul concurent
    concurent = concurenti_noi[poz]
    concurent = modifica_scor(concurent, note_noi)
    concurenti_noi[poz] = concurent

    return concurenti_noi

def test_modifica_scor_concurenti():
    """
    Functie de test pentru modifica_scor_concurenti()
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])

    modifica_scor_concurenti(concurenti, 305, [9, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert get_note_concurent(concurenti[1]) == [9, 9, 8, 7, 9, 10, 8, 9, 9, 10]

def modificaScorConcurent(concurenti):

    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    numar = int(input("Introduceti numarul concurentului caruia ii modificam scorul: "))

    concurent = get_concurent_from_numar(concurenti, numar)
    if concurent is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    valori_probe = input("Introduceti noile valori de probe: ")
    note_noi = [int(nota) for nota in valori_probe.split()]

    concurenti = modifica_scor_concurenti(concurenti, numar, note_noi)
    return concurenti

def sterge_note(concurent):
    """
    Sterge notele din lista de note a concurentului 'concurent'
    :param concurent:
    :return: Noul concurent, cu lista de note goala
    """

    concurent_sters  = creeaza_concurent(get_numar_concurent(concurent), [])
    return concurent_sters

def test_sterge_note():
    """
    Functie de test pentru sterge_note
    """

    concurent = creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    concurent = sterge_note(concurent)
    assert get_note_concurent(concurent) == []

def sterge_scor_concurent(concurenti, numar):
    """
    Stergerea notelor din lista de note a unui concurent
    :param concurenti: Lista de concurenti
    :param numar: Numarul concurentului caruia ii stergem nota
    :return: Lista de concurenti modificata
    """

    #Determinarea pozitiei in lista a conncurentului in functie de numar
    poz = get_poz_from_numar(concurenti, numar)
    if poz is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti_noi = concurenti[:] #Copierea listei

    #Crearea unei noi liste cu concurentul cu note sterse
    concurent = concurenti_noi[poz]
    concurent = sterge_note(concurent)
    concurenti_noi[poz] = concurent

    return concurenti_noi

def test_sterge_scor_concurent():
    """
    Functie de test pentru sterge_scor_concurent()
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])

    concurenti = sterge_scor_concurent(concurenti, 305)
    assert get_note_concurent(concurenti[1]) == []

def stergeScorConcurent(concurenti):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    numar = int(input("Introduceti numarul concurentului caruia ii stergem scorul: "))

    concurent = get_concurent_from_numar(concurenti, numar)
    if concurent is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti = sterge_scor_concurent(concurenti, numar)
    return concurenti


def sterge_interval_concurenti(concurenti, start, stop):
    """
    Functie ce sterge notele concurentilor intr-un interval de pozitii
    :param concurenti: Lista de concurenti
    :param start: Prima pozitie
    :param stop: Ultima pozitie
    :return: Lista modificata cu notele sterse
    """

    #Validarea datelor de intrare
    if len(concurenti) - 1 > stop or len(concurenti) - 1 < start or len(concurenti) == 1:
        print("Nu ati introdus un interval valid")
        return concurenti

    #Stergea notelor din interval
    for index in range(start, stop+1):
        numar = get_numar_concurent(concurenti[index])
        concurenti = sterge_scor_concurent(concurenti, numar)

    return concurenti

def test_sterge_interval_concurenti():
    """
    Functie de test pentru sterge_interval_concurenti()
    """

    concurenti = ["filler"]
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1])
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1])

    concurenti = sterge_interval_concurenti(concurenti, 1, 2)
    assert get_note_concurent(concurenti[1]) == []
    assert get_note_concurent(concurenti[2]) == []

def stergeScorInterval(concurenti):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    start = int(input("Introduceti pozitia primului concurent caruia ii stergem scorul: "))
    stop = int(input("Introduceti pozitia ultimului concurent caruia ii stergem scorul: "))

    concurenti_noi = sterge_interval_concurenti(concurenti, start, stop)
    return concurenti_noi

def filtrare_scor_mai_mic(concurenti,scor):
    """
    Filtrarea concurentilor care au scorul mai mic decat un scor dat
    :param concurenti: Lista de concurenti
    :param scor: Scorul de comparat
    :return: Lista cu concurentii filtrati
    """
    concurenti_filtrati = []
    for concurent in concurenti:
        if comparare_scor(concurent, scor, 1):
            concurenti_filtrati.append(concurent)

    return concurenti_filtrati

def test_filtrare_scor_mai_mic():
    """
    Functie de test pentru filtrare_scor_mai_mic()
    """

    concurenti = []
    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10]) #Scor = 8.9
    adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 8, 8, 10]) #Scor = 8.7
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 6, 6, 10]) #Scor = 8.5

    concurenti = filtrare_scor_mai_mic(concurenti, 8.8)

    assert get_numar_concurent(concurenti[0]) == 305

def print_menu():
    """
    Afiseaza meniul principal al aplicatiei
    """
    print(" ---Gestionare concurenti---")
    print("     1. Adaugare concurent")
    print("     2. Inserare concurent")
    print("     3. Afisare concurenti")
    print("     4. Modificari concurenti")
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


def run():
    """
    Implementare interfata utilizator
    """

    concurenti = ["filler"]

    while True:
        print_menu()
        option = input().strip()

        if option == "1":
            adaugaConcurent(concurenti)
        elif option == "2":
            concurenti = inserareConcurent(concurenti)
        elif option == "3":
            print_menu_afisare()
            option_afis = input().strip()

            if option_afis == "1":
                afisareConcurentiComparareScor(concurenti)
            elif option_afis == "2":
                afisareConcurentiOrdonareScor(concurenti)
            elif option_afis == "3":
                afisareConcurentiOrdonareComparare(concurenti)

        elif option == "4":
            print_menu_modif()
            option_modif = input().strip()

            if option_modif == "1":
                concurenti = modificaScorConcurent(concurenti)

            if option_modif == "2":
                concurenti = stergeScorConcurent(concurenti)

            if option_modif == "3":
                concurenti = stergeScorInterval(concurenti)

        elif option == "x":
            break

        else:
            print("Nu inteleg comanda")

    print("La revedere!")

def test_all():
    test_creeaza_concurent()
    test_adauga_concurent()
    test_inserare_concurent()
    test_comparare_scor()
    test_sortare_scor()
    test_modifica_scor()
    test_modifica_scor_concurenti()
    test_sterge_note()
    test_sterge_interval_concurenti()
    test_get_poz_from_numar()
    test_sterge_scor_concurent()
    test_filtrare_scor_mai_mic()


test_all()
run()


"""
Exemple date de intrare:

305
10 9 8 7 9 10 8 9 8 7
306
10 9 8 7 9 10 8 9 9 10
310
10 9 8 7 9 6 8 9 9 10
204
10 9 8 8 9 8 8 8 9 10
"""