from domain.entities import Melodie, Persoana, Rating
from domain.validator import ValidatorMelodie, ValidatorPersoana


# TO DO: test creare Melodie, getters, setters
# TO DO: test validare rating
def test_melodie():
    pass


def test_validation():
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    val = ValidatorMelodie()
    val.validate(m)

    #melodie invalida - gen invalid
    m1 = Melodie(1324, "Perfect Strangers", "Deep Purple", "alt gen", 2.44)
    try:
        val.validate(m1)
        assert False
    except ValueError:
        assert True

    #melodie invalida - durata invalida
    m1 = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 23.97)
    try:
        val.validate(m1)
        assert False
    except ValueError:
        assert True




def test_persoana():
    p = Persoana("1234567890123", "Andrei Popescu")
    assert (p.cnp == "1234567890123")
    assert (p.nume == "Andrei Popescu")

    p.nume = "Valentin Popescu"
    assert (p.nume == "Valentin Popescu")


def test_equal_persoana():
    p1 = Persoana("1234567890123", "Andrei Popescu")
    p2 = Persoana("1234567890123", "Andrei Pop")
    assert (p1 == p2)

    p3 = Persoana("2134567890123", "Maria Pop")
    assert (p1 != p3)


def test_validare_persoana():
    validator = ValidatorPersoana()
    p1 = Persoana("123", "Andrei Popescu")
    try:
        validator.validate(p1)
        assert False
    except ValueError:
        assert True

    p2 = Persoana("2234567890123", "Daniel")
    try:
        validator.validate(p2)
        assert False
    except ValueError:
        assert True

    p3 = Persoana("123", "Andrei")
    try:
        validator.validate(p3)
        assert False
    except ValueError:
        assert True

#TO DO: test create rating

def test_equal_rating():
    melodie1 = Melodie(1, "Highway Star", "Deep Purple", "rock",4.32)
    persoana1 = Persoana('2970103123456', 'Marcel')

    rating1 = Rating(persoana1, melodie1, 10)
    rating2 = Rating(persoana1, melodie1, 8.55)
    assert (rating1 == rating2)

    melodie2 = Melodie(2, "Perfect Strangers", "Deep Purple", "rock",3.32)
    rating3 = Rating(persoana1, melodie2, 3)
    assert (rating3 != rating2)

if __name__ == "__main__":
    test_melodie()
    test_validation()
    test_persoana()
    test_equal_persoana()
    test_validare_persoana()
    test_equal_rating()
