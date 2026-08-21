
from domain import service_filtrare

def filtrareMultiple(concurenti, istoric_concurenti):
    """
    Implementare UI
    """

    mult = int(input("Introduceti valoarea care sa divida scorurile concurentilor: "))

    concurenti = service_filtrare.filtrare_scor_multiplu(concurenti, mult, istoric_concurenti)

    print("Lista a fost filtrata")
    return concurenti

def filtrareScorMaiMic(concurenti, istoric_concurenti):
    """
    Implementare UI
    """

    scor_filtrare = int(input("Introduceti scorul dupa care filtram: "))

    concurenti = service_filtrare.filtrare_scor_mai_mic(concurenti, scor_filtrare, istoric_concurenti)

    print("Lista a fost filtrata")
    return concurenti