def creeaza_baller(id_baller, nume, valoare):
    """
    Functie care creeaza un baller cu:
    :param id_baller: intreg, >= 0
    :param nume: string, nevid
    :param valoare: float, > 0.0
    :return: un baller cu id-ul 'id_baller', numele 'nume' si valorarea 'valoare'
    """

    return {
        "id": id_baller,
        "nume": nume,
        "valoare": valoare,
    }

def get_baller_id(baller):
    """
    Functie care returneaza id-ul unui baller
    :param baller: baller cu id-ul 'id_baller', intreg >= 0
    :return: id_baller, intreg pozitiv, idul ballerului baller
    """

    return baller("id")