import concurent
import service_scor

def filtrare_scor_mai_mic(concurenti,scor):
    """
    Filtrarea concurentilor care au scorul mai mic decat un scor dat
    :param concurenti: Lista de concurenti
    :param scor: Scorul de comparat
    :return: Lista cu concurentii filtrati
    """
    concurenti_filtrati = ["filler"]
    for concurent_filtrare in concurenti[1:]:
        if service_scor.comparare_scor(concurent_filtrare, scor, 1):
            concurenti_filtrati.append(concurent_filtrare)

    return concurenti_filtrati


def filtrare_scor_multiplu(concurenti, mult):
    """
    Filtrarea concurentilor care au scorul un multiplu al unui numar dat
    :param concurenti: Lista de concurenti
    :param mult: Numarul care sa fie divizor al scorului
    :return: Lista cu concurentii filtrati
    """

    concurenti_filtrati = concurenti[:]
    for concurent_filtrare in concurenti_filtrati[1:]:
        if concurent.get_scor_concurent(concurent_filtrare) % mult != 0:
            concurenti_filtrati = service_scor.sterge_scor_concurent(concurenti_filtrati,
                                                                     concurent.get_numar_concurent(concurent_filtrare))

    return concurenti_filtrati