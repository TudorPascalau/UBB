
from utils import validator
from domain import concurent
import copy


def adauga_concurent(concurenti, numar, note, istoric_concurenti):
    """
    Adauga un concurent in lista 'concurenti'

    :param concurenti: lista dictionare, in care va fi adaugat concurentul
    :param numar: int, numarul de concurs al concurentului
    :param note: lista int, 10 note de la 1 la 10
    :param istoric_concurenti: stiva de liste de concurenti, folosita pentru undo-uri

    :return True, daca a fost adaugat concurentul
            False, daca nu
    """

    concurent_nou = concurent.creeaza_concurent(numar, note) # Crearea unui concurent cu numarul si notele date
    if not validator.valideaza_concurent(concurent_nou, concurenti): #Verificarea concurentului
        return False

    #Stiva de liste de concurenti
    istoric_concurenti.append([
        copy.copy(concurent_copiat) for concurent_copiat in concurenti
    ])

    concurenti.append(concurent_nou) # Adaugarea concurentului in lista de concurenti
    return True

def inserare_concurent(concurenti,poz, numar, note, istoric_concurenti):
    """
    Inserare in lista 'concurenti' pe pozitia 'poz' a unui concurent
    :param concurenti: lista dictionare
    :param poz: int, pozitia in lista in care va fi inserat concurentul
    :param numar: int, numarul de concurs
    :param note: lista int, note de la 1 la 10
    :param istoric_concurenti: stiva de liste de concurenti, folosita pentru undo-uri
    :return: Noul sir de concurenti
    """

    #Stiva de liste de concurenti
    istoric_concurenti.append([
        copy.copy(concurent_copiat) for concurent_copiat in concurenti
    ])

    concurent_nou = concurent.creeaza_concurent(numar, note)
    if validator.valideaza_concurent(concurent_nou, concurenti):

        lungime = len(concurenti) - 1 # Lungimea sirului de concurenti, fara elementul de filler
        concurenti.append(concurenti[lungime]) #Copierea ultimului concurent, intr-o noua pozitie

        for index in range(lungime, poz, -1): #Mutarea concurentilor cu o pozitie mai in fata
            concurenti[index] = concurenti[index - 1]

        concurenti[poz] = concurent_nou #Inserarea unui concurent pe noua pozitie

    else:
        print("Eroare la inserare")

    return concurenti

def adauga_exemple_concurenti(concurenti, istoric_concurenti):

    istoric_concurenti.append([
        copy.copy(concurent_copiat) for concurent_copiat in concurenti
    ])

    adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 8, 7], istoric_concurenti)
    adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)
    adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 6, 8, 9, 9, 10], istoric_concurenti)
    adauga_concurent(concurenti, 204, [10, 9, 8, 8, 9, 8, 8, 8, 9, 10], istoric_concurenti)