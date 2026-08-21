
from utils import validator
from domain import concurent


def calc_medie_interval(concurenti, start, stop):
    """
    Calculeaza media scorurilor pentru un interval de concurenti
    :param concurenti: Lista de concurenti
    :param start: Indexul de start, int
    :param stop: Indexul de stop, int
    :return: media, float
    """

    medie = 0

    # Validarea datelor de intrare
    if not validator.valideaza_interval(concurenti, start, stop):
        print("Nu ati introdus un interval valid")
        return medie

    for index in range(start, stop+1):
        medie = medie + concurent.get_scor_concurent(concurenti[index])

    medie = medie / (stop - start + 1)
    return medie

def calc_min_interval(concurenti, start, stop):
    """
    Calculeaza minimul scorurilor pentru un interval de concurenti
    :param concurenti: Lista de concurenti
    :param start: Indexul de start, int
    :param stop: Indexul de stop, int
    :return: menimul, float
    """

    minim = 101

    # Validarea datelor de intrare
    if not validator.valideaza_interval(concurenti, start, stop):
        print("Nu ati introdus un interval valid")
        return minim

    for index in range(start, stop+1):
        if concurent.get_scor_concurent(concurenti[index]) < minim:
            minim = concurent.get_scor_concurent(concurenti[index])

    return minim

def calc_multiplu10(concurent_mult):
    """
    Determina daca concurentul are un scor multiplu de zece
    :param concurent_mult: concurentul
    :return: True daca da,
             False daca nu
    """
    return concurent.get_scor_concurent(concurent_mult) % 10 == 0
