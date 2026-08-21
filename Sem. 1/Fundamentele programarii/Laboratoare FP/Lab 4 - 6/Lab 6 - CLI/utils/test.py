
from domain import concurent, service, service_filtrare, service_scor, service_subset, service_undo

def test_get_concurent_from_numar():
    """
    Functie de test pentru get_concurent_from_numar()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)

def test_get_poz_from_numar():
    """
    Functie de test pentru get_poz_from_numar()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)

    assert concurent.get_poz_from_numar(concurenti, 305) == 1
    assert concurent.get_poz_from_numar(concurenti, 310) == 2
    assert concurent.get_poz_from_numar(concurenti, 999) is None


def test_creeaza_concurent():
    """
    Functie de test pentru creeaza_concurent()
    """
    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert concurent.get_numar_concurent(concurent_nou) == 305
    assert len(concurent.get_note_concurent(concurent_nou)) == 10
    assert concurent.get_note_concurent(concurent_nou)[0] == 10
    assert concurent.get_scor_concurent(concurent_nou) == 89


def test_adauga_concurent():
    """
    Functie de test adauga_concurent()
    """
    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)

    assert len(concurenti) == 2
    assert concurent.get_numar_concurent(concurenti[1]) == 305

def test_inserare_concurent():
    """
    Functie de test pentru inserare_concurent()
    """
    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1], istoric_concurenti)
    assert concurent.get_numar_concurent(concurenti[1]) == 305

    concurenti = service.inserare_concurent(concurenti, 1, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1], istoric_concurenti)
    assert concurent.get_numar_concurent(concurenti[1]) == 310


def test_sortare_scor():
    """
    Functie de test pentru sortare_scor
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 10, 10], istoric_concurenti)

    assert concurent.get_numar_concurent(concurenti[1]) == 305

    concurenti = service_scor.sortare_scor(concurenti)
    assert concurent.get_numar_concurent(concurenti[1]) == 310


def test_modifica_scor():
    """
    Functie de test pentru modifica_scor
    """
    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert concurent.get_note_concurent(concurent_nou)[0] == 10

    concurent_nou = service_scor.modifica_scor(concurent_nou, [9, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert concurent.get_note_concurent(concurent_nou)[0] == 9

def test_comparare_scor():
    """
    Functie de test pentru comparare scor
    """

    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert service_scor.comparare_scor(concurent_nou, 85, 1)
    assert service_scor.comparare_scor(concurent_nou, 95, -1)

def test_modifica_scor_concurenti():
    """
    Functie de test pentru modifica_scor_concurenti()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)

    service_scor.modifica_scor_concurenti(concurenti, 305, [9, 9, 8, 7, 9, 10, 8, 9, 9, 10],istoric_concurenti)
    assert concurent.get_note_concurent(concurenti[1]) == [9, 9, 8, 7, 9, 10, 8, 9, 9, 10]

def test_sterge_note():
    """
    Functie de test pentru sterge_note
    """

    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    concurent_nou = service_scor.sterge_note(concurent_nou)
    assert concurent.get_note_concurent(concurent_nou) == []

def test_sterge_scor_concurent():
    """
    Functie de test pentru sterge_scor_concurent()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)

    concurenti = service_scor.sterge_scor_concurent(concurenti, 305, istoric_concurenti)
    assert concurent.get_note_concurent(concurenti[1]) == []


def test_sterge_interval_concurenti():
    """
    Functie de test pentru sterge_interval_concurenti()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1], istoric_concurenti)
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 9, 9, 1], istoric_concurenti)

    concurenti = service_scor.sterge_interval_concurenti(concurenti, 1, 2, istoric_concurenti)
    assert concurent.get_note_concurent(concurenti[1]) == []
    assert concurent.get_note_concurent(concurenti[2]) == []



def test_calc_medie_interval():
    """
    Functie de test pentru calc_medie_interval()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)  # Scor = 89
    service.adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 8, 8, 10], istoric_concurenti)  # Scor = 87

    medie = service_subset.calc_medie_interval(concurenti, 1, 2)
    assert medie == 88

def test_calc_min_interval():
    """
    Functie de test pentru calc_min_interval()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10], istoric_concurenti)  # Scor = 89
    service.adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 8, 8, 10], istoric_concurenti)  # Scor = 87

    minim = service_subset.calc_min_interval(concurenti, 1, 2)
    assert minim == 87

def test_calc_multiplu10():
    """
    Functie de test pentru calc_multiplu10()
    """

    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10])
    assert service_subset.calc_multiplu10(concurent_nou) == False

    concurent_nou = concurent.creeaza_concurent(305, [10, 9, 8, 7, 9, 10, 8, 9, 10, 10])
    assert service_subset.calc_multiplu10(concurent_nou) == True

def test_filtrare_scor_mai_mic():
    """
    Functie de test pentru filtrare_scor_mai_mic()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10],istoric_concurenti) # Scor = 89
    service.adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 8, 8, 10],istoric_concurenti) # Scor = 87
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 6, 6, 10],istoric_concurenti) # Scor = 85

    concurenti = service_filtrare.filtrare_scor_mai_mic(concurenti, 88,istoric_concurenti)

    assert concurent.get_numar_concurent(concurenti[1]) == 305

def test_filtrare_scor_multiplu():
    """
    Functie de test pentru filtrare_scor_multiplu()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 10, 10],istoric_concurenti) # Scor = 90
    service.adauga_concurent(concurenti, 306, [10, 9, 8, 7, 9, 10, 8, 8, 8, 10],istoric_concurenti) # Scor = 89
    service.adauga_concurent(concurenti, 310, [10, 9, 8, 7, 9, 10, 8, 7, 7, 10],istoric_concurenti) # Scor = 85

    concurenti = service_filtrare.filtrare_scor_multiplu(concurenti, 5,istoric_concurenti)
    assert concurent.get_scor_concurent(concurenti[1]) == 90
    assert concurent.get_scor_concurent(concurenti[2]) == 0
    assert concurent.get_scor_concurent(concurenti[3]) == 85

def test_undo_last():
    """
    Functie de test pentru undo_last()
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    service.adauga_concurent(concurenti, 305, [10, 9, 8, 7, 9, 10, 8, 9, 9, 10],istoric_concurenti)
    concurenti = service_undo.undo_last(istoric_concurenti)

    assert concurenti[0] == "filler"

def test_all():
    test_creeaza_concurent()
    test_adauga_concurent()
    test_inserare_concurent()
    test_comparare_scor()
    test_sortare_scor()
    test_modifica_scor()
    test_modifica_scor_concurenti()
    test_sterge_note()
    test_sterge_interval_concurenti()
    test_get_poz_from_numar()
    test_sterge_scor_concurent()
    test_calc_medie_interval()
    test_calc_min_interval()
    test_calc_multiplu10()
    test_filtrare_scor_mai_mic()
    test_filtrare_scor_multiplu()
    test_undo_last()