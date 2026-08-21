
import copy
from domain import concurent, service_scor


def filtrare_scor_mai_mic(concurenti,scor,istoric_concurenti):
    """
    Filtrarea concurentilor care au scorul mai mic decat un scor dat
    :param concurenti: Lista de concurenti
    :param scor: Scorul de comparat
    :param istoric_concurenti: Stiva de liste de concurenti, folosita la undo-uri
    :return: Lista cu concurentii filtrati
    """
    #Stiva de liste de concurenti
    istoric_concurenti.append([
        copy.copy(concurent_copiat) for concurent_copiat in concurenti
    ])

    concurenti_filtrati = ["filler"]
    for concurent_filtrare in concurenti[1:]:
        if service_scor.comparare_scor(concurent_filtrare, scor, 1):
            concurenti_filtrati.append(concurent_filtrare)

    return concurenti_filtrati


def filtrare_scor_multiplu(concurenti, mult, istoric_concurenti):
    """
    Filtrarea concurentilor care au scorul un multiplu al unui numar dat
    :param concurenti: Lista de concurenti
    :param mult: Numarul care sa fie divizor al scorului
    :param istoric_concurenti: Stiva de de liste de concurenti, folosita la undo-uri
    :return: Lista cu concurentii filtrati
    """

    #Stiva de liste de concurenti
    istoric_concurenti.append([
        copy.copy(concurent_copiat) for concurent_copiat in concurenti
    ])

    concurenti_filtrati = concurenti[:]
    for concurent_filtrare in concurenti_filtrati[1:]:
        if concurent.get_scor_concurent(concurent_filtrare) % mult != 0:
            concurenti_filtrati = service_scor.sterge_scor_concurent(concurenti_filtrati,
                                                                     concurent.get_numar_concurent(concurent_filtrare),
                                                                     istoric_concurenti)

    return concurenti_filtrati