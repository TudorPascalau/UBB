import ui
import service_scor
import concurent

def afisareConcurentiOrdonareScor(concurenti):
    """
    Implementare UI I/O pentru afisarea concurentilor ordonati dupa valoarea scorului
    :param concurenti:
    """

    concurenti = service_scor.sortare_scor(concurenti) #Sortarea concurentilor
    for concurent_afis in concurenti[1:]:
        ui.afisareConcurent(concurent_afis)

def afisareConcurentiOrdonareComparare(concurenti):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mare decat un scor dat, sortati dupa valoarea scorului
    """

    scor = float(input("Introduceti scorul: "))  # Preluarea de la utilizator a scorului

    concurenti = service_scor.sortare_scor(concurenti)  #Ordonarea concurentilor dupa scor
    for concurent_afis in concurenti[1:]:
        if service_scor.comparare_scor(concurent_afis, scor, 1): #Apelarea functiei de comparatie pentru scor concurent > scor dat
            ui.afisareConcurent(concurent_afis) #Afisarea concurentiilor care au un scor mai mare decat cel dat

def modificaScorConcurent(concurenti):

    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    numar = int(input("Introduceti numarul concurentului caruia ii modificam scorul: "))

    concurent_nou = concurent.get_concurent_from_numar(concurenti, numar)
    if concurent_nou is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    valori_probe = input("Introduceti noile valori de probe: ")
    note_noi = [int(nota) for nota in valori_probe.split()]

    concurenti = service_scor.modifica_scor_concurenti(concurenti, numar, note_noi)
    return concurenti

def afisareConcurentiComparareScor(concurenti):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mic decat un scor dat
    :param concurenti: lista dictionare, retine concurentii
    """

    scor = float(input("Introduceti scorul: ")) # Preluarea de la utilizator a scorului
    for concurent_comparare in concurenti[1:]:
        if service_scor.comparare_scor(concurent_comparare, scor, -1): #Apelarea functiei de comparatie pentru scor concurent < scor dat
            ui.afisareConcurent(concurent_comparare) #Afisarea concurentiilor care au un scor mai mic decat cel dat

def stergeScorConcurent(concurenti):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    numar = int(input("Introduceti numarul concurentului caruia ii stergem scorul: "))

    concurent_nou = concurent.get_concurent_from_numar(concurenti, numar)
    if concurent_nou is None:
        print("Nu ati introdus un numar valid")
        return concurenti

    concurenti = service_scor.sterge_scor_concurent(concurenti, numar)
    return concurenti

def stergeScorInterval(concurenti):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    start = int(input("Introduceti pozitia primului concurent caruia ii stergem scorul: "))
    stop = int(input("Introduceti pozitia ultimului concurent caruia ii stergem scorul: "))

    concurenti_noi = service_scor.sterge_interval_concurenti(concurenti, start, stop)
    return concurenti_noi