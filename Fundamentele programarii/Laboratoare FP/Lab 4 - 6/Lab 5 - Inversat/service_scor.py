import concurent
import validator

def comparare_scor(concurent_comparare, scor_comp, ineg):
    """
    Compara scorul unui concurent cu un scor dat
    :param concurent_comparare: concurentul dat
    :param scor_comp: scorul de comparat
    :param ineg: -1, daca comparam pt scor concurent < scor dat
                 1, daca comparam pt scor concurent > scor dat
    :return: True, daca comparatia e adevarata
             False, altfel
    """

    if ineg == -1: #Compara daca scor concurent < scor dat
        if not concurent.get_scor_concurent(concurent_comparare) < scor_comp:
            return False

    elif ineg == 1: #Compara daca scor concurent > scor dat
        if not concurent.get_scor_concurent(concurent_comparare) > scor_comp:
            return False

    return True

def sortare_scor(concurenti):
    """
    Sortarea concurentilor in ordine crescatoare a scorului
    :param concurenti: Lista de concurenti
    :return: Lista de concurenti sortata
    """

    # Pastreaza concurenti[0] == "filler" si sorteaza restul dupa scor
    return [concurenti[0]] + sorted(concurenti[1:], key = lambda x: x[2], reverse=True)

def modifica_scor(concurent_modif, note_noi):
    """
    Modifica notele concurentului 'concurent' cu notele din note_noi
    :param concurent_modif: dictionar concurent
    :param note_noi: lista int, 10 note de la 1 la 10
    :return: Noul concurent
    """

    concurent_modif[1] = note_noi
    concurent_modif[2] = sum(note_noi)
    return concurent_modif

def modifica_scor_concurenti(concurenti, numar, note_noi):
    """
    Updateaza sirul 'concurenti' dupa modificarea unui concurent
    :param concurenti: Lista de concurenti
    :param numar: Numarul concurentului caruia i se modifica notele
    :param note_noi: Notele ale concurentului
    :return: Lista de concurenti modificata
    """

    # Determinarea pozitiei in lista a conncurentului in functie de numar
    poz = concurent.get_poz_from_numar(concurenti, numar)
    if poz is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti_noi = concurenti[:] #Copierea listei de concurenti

    #Modificarea listei cu noul concurent
    concurent_modif = concurenti_noi[poz]
    concurent_modif = modifica_scor(concurent_modif, note_noi)
    concurenti_noi[poz] = concurent_modif

    return concurenti_noi

def sterge_note(concurent_sters):
    """
    Sterge notele din lista de note a concurentului 'concurent'
    :param concurent_sters: Concurentul caruia ii stergem notele
    :return: Noul concurent, cu lista de note goala
    """

    concurent_sters_nou  = concurent.creeaza_concurent(concurent.get_numar_concurent(concurent_sters), [])
    return concurent_sters_nou

def sterge_scor_concurent(concurenti, numar):
    """
    Stergerea notelor din lista de note a unui concurent
    :param concurenti: Lista de concurenti
    :param numar: Numarul concurentului caruia ii stergem nota
    :return: Lista de concurenti modificata
    """

    #Determinarea pozitiei in lista a conncurentului in functie de numar
    poz = concurent.get_poz_from_numar(concurenti, numar)
    if poz is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti_noi = concurenti[:] #Copierea listei

    #Crearea unei noi liste cu concurentul cu note sterse
    concurent_sters = concurenti_noi[poz]
    concurent_sters = sterge_note(concurent_sters)
    concurenti_noi[poz] = concurent_sters

    return concurenti_noi

def sterge_interval_concurenti(concurenti, start, stop):
    """
    Functie ce sterge notele concurentilor intr-un interval de pozitii
    :param concurenti: Lista de concurenti
    :param start: Prima pozitie
    :param stop: Ultima pozitie
    :return: Lista modificata cu notele sterse
    """

    #Validarea datelor de intrare
    if not validator.valideaza_interval(concurenti, start, stop):
        print("Nu ati introdus un interval valid")
        return concurenti

    #Stergea notelor din interval
    for index in range(start, stop+1):
        numar = concurent.get_numar_concurent(concurenti[index])
        concurenti = sterge_scor_concurent(concurenti, numar)

    return concurenti

