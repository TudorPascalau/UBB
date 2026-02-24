
def creeaza_concurent(numar, note):
    """
    Creeaza un concurent cu numarul de concurs si lista de note data
    :param numar: int, numar concurs > 0
    :param note: lista int, 10 note de la 1 la 10
    :return: dictionar, reprezinta concurentul
    """

    # Scorul final reprezinta suma notelor concurentului sau 0 daca acesta nu are note
    if len(note) == 0:
        scor_final = 0
    else:
        scor_final = sum(note)

    # Reprezentam un concurent sub forma unui dictionar
    return {
        "numar": numar,
        "note": note,
        "scor_final": scor_final
    }

def get_numar_concurent(concurent):
    return concurent["numar"] # Returneaza numarul de concurs al concurentului

def get_note_concurent(concurent):
    return concurent["note"] # Returneaza lista cu notele la cele 10 probe

def get_scor_concurent(concurent):
    return concurent["scor_final"] # Returneaza scorul final al concurentului

def get_concurent_from_numar(concurenti, numar):
    """
    Asocierea unui concurent cu un numar de concurs dat
    :param concurenti: Lista de concurenti in care cautam
    :param numar: Numarul
    :return: concurentul, daca numarul dat i se asociaza
             None, daca numarul dat nu are un concurent asociat
    """
    for concurent in concurenti[1:]:
        if get_numar_concurent(concurent) == numar:
            return concurent

    return None

def get_poz_from_numar(concurenti, numar):
    """
    Asocierea pozitiei unui concurent cu un numar de concurs dat
    :param concurenti: Lista de concurenti in care cautam
    :param numar: Numarul
    :return: pozitia concurentului, daca numarul dat i se asociaza
             None, daca numarul dat nu are un concurent asociat
    """
    for index in range(1,len(concurenti)):
        if get_numar_concurent(concurenti[index]) == numar:
            return index

    return None