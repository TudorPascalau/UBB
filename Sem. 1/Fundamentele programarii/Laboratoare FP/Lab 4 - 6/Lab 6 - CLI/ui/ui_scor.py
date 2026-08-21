
from domain import service_scor, concurent
from ui import ui


def afisareConcurentiOrdonareScor(concurenti):
    """
    Implementare UI I/O pentru afisarea concurentilor ordonati dupa valoarea scorului
    :param concurenti:
    """

    concurenti = service_scor.sortare_scor(concurenti) #Sortarea concurentilor
    for concurent_afis in concurenti[1:]:
        ui.afisareConcurent(concurent_afis)

def afisareConcurentiOrdonareComparare(concurenti, param):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mare decat un scor dat, sortati dupa valoarea scorului
    """

    scor = int(param[0]) # Preluarea de la utilizator a scorului

    concurenti = service_scor.sortare_scor(concurenti)  #Ordonarea concurentilor dupa scor
    for concurent_afis in concurenti[1:]:
        if service_scor.comparare_scor(concurent_afis, scor, 1): #Apelarea functiei de comparatie pentru scor concurent > scor dat
            ui.afisareConcurent(concurent_afis) #Afisarea concurentiilor care au un scor mai mare decat cel dat

def afisareConcurentiComparareScor(concurenti, param):
    """
    Implementare UI pentru afisarea concurentilor cu un scor mai mic decat un scor dat
    """

    try:
        scor = int(param[0]) # Preluarea de la utilizator a scorului
        for concurent_comparare in concurenti[1:]:
            if service_scor.comparare_scor(concurent_comparare, scor, -1): #Apelarea functiei de comparatie pentru scor concurent < scor dat
                ui.afisareConcurent(concurent_comparare) #Afisarea concurentiilor care au un scor mai mic decat cel dat

    except:
        print("Parametrii comenzii nu sunt corecti!")

def modificaScorConcurent(concurenti, istoric_concurenti):

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

    concurenti = service_scor.modifica_scor_concurenti(concurenti, numar, note_noi, istoric_concurenti)
    return concurenti

def stergeScorConcurent(concurenti, istoric_concurenti, param):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    try:
        numar = int(param[0])

        concurent_nou = concurent.get_concurent_from_numar(concurenti, numar)
        if concurent_nou is None:
            print("Nu ati introdus un numar valid")
            return concurenti

        concurenti = service_scor.sterge_scor_concurent(concurenti, numar, istoric_concurenti)
        return concurenti
    except:
        print("Parametrii comenzii nu sunt corecti!")

def stergeScorInterval(concurenti, istoric_concurenti):
    """
    Implementare UI pentru modificarea listei de concurenti
    :return: Faciliteaza modificarea la nivelul de baza (run())
    """

    start = int(input("Introduceti pozitia primului concurent caruia ii stergem scorul: "))
    stop = int(input("Introduceti pozitia ultimului concurent caruia ii stergem scorul: "))

    concurenti_noi = service_scor.sterge_interval_concurenti(concurenti, start, stop, istoric_concurenti)
    return concurenti_noi