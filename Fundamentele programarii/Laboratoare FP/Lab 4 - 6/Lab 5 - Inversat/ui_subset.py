from wsgiref.validate import validator

import service_subset
import validator
import ui

def afisareMedieInterval(concurenti):
    """
    Implementare UI pentru afisarea mediei scorurilor unui interal de concurenti
    :param concurenti: Lista in care se cauta
    """

    start = int(input("Introduceti inceputul intervalului: "))
    stop = int(input("Introduceti sfarsitul intervalului:: "))

    medie = service_subset.calc_medie_interval(concurenti, start, stop)
    print(f"Media conncurentilor din intervalul dat este {medie}")

def afisareMinInterval(concurenti):
    """
    Implementare UI pentru afisarea minimului scorurilor unui interal de concurenti
    :param concurenti: Lista in care se cauta
    """

    start = int(input("Introduceti inceputul intervalului: "))
    stop = int(input("Introduceti sfarsitul intervalului:: "))

    minim = service_subset.calc_min_interval(concurenti, start, stop)
    print(f"Scorul minim din intervalul dat este {minim}")

def afisareMultiplu10(concurenti):
    """
    Implementare UI pentru afisarea concurentilor care au scor multiplu de 10
    :param concurenti:
    """

    start = int(input("Introduceti inceputul intervalului: "))
    stop = int(input("Introduceti sfarsitul intervalului:: "))

    if not validator.valideaza_interval(concurenti,start,stop):
        print("Nu ati introdus un interval valid")

    for index in range(start, stop + 1):
        if service_subset.calc_multiplu10(concurenti[index]):
            ui.afisareConcurent(concurenti[index])