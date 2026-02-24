import service_filtrare

def filtrareMultiple(concurenti):
    """
    Implementare UI
    """

    mult = int(input("Introduceti valoarea care sa divida scorurile concurentilor: "))

    concurenti = service_filtrare.filtrare_scor_multiplu(concurenti, mult)

    print("Lista a fost filtrata")
    return concurenti

def filtrareScorMaiMic(concurenti):
    """
    Implementare UI
    """

    scor_filtrare = int(input("Introduceti scorul dupa care filtram: "))

    concurenti = service_filtrare.filtrare_scor_mai_mic(concurenti, scor_filtrare)

    print("Lista a fost filtrata")
    return concurenti