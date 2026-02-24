from baller import creeaza_baller, get_baller_id

def test_creeaza_baller():
    id_baller = 23
    nume = "Jordan"
    valoarea = 9000.1

    baller = creeaza_baller(id_baller, nume, valoarea)

    assert get_baller_id(baller) == id_baller

def ruleaza_teste():
    test_creeaza_baller()