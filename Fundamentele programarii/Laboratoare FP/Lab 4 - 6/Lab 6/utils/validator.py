
from domain import concurent

def valideaza_concurent(concurent_valid, concurenti):
    """
    Verifica daca concurentul 'concurent' este valid
    :param concurent_valid: concurentul de verificat
    :param concurenti: lista de concurenti in care se afla concurentul
    :return: True, daca concurentul este valid
             False, daca nu
    """

    erori = []

    # validare numar
    if concurent.get_numar_concurent(concurent_valid) <= 0:
        erori.append("Numarul nu este valid")

    # validare unicitate numar
    for index in range(1,len(concurenti)):
        if concurent.get_numar_concurent(concurenti[index]) == concurent.get_numar_concurent(concurent_valid):
            erori.append("Numarul de concurs mai apare o data")

    # validare note
    for nota in concurent.get_note_concurent(concurent_valid):
        if not 1 <= nota <= 10:
            erori.append("Notele nu sunt valide")

    if erori:
        print(erori)
        return False
    return True

def valideaza_interval(concurenti, start, stop):

     lungime = len(concurenti) - 1

     if lungime == 0:
         return False

     if start < 1 or stop < 1:
         return False

     if start > lungime or stop > lungime:
         return False

     return True