from domain.validator import ValidatorMelodie
from repos.repo_melodii import RepoMelodieMemory
from services.service_melodii import ServiceMelodii


def test_add_melodie_srv():
    test_repo = RepoMelodieMemory()
    test_val = ValidatorMelodie()
    test_srv = ServiceMelodii(test_repo, test_val)
    test_srv.add_melodie(1, "Kashmir", "Led Zeppelin", "rock", 4.3)

    assert test_srv.get_numar_melodii() == 1

    try:
        #melodia mai exista
        test_srv.add_melodie(1, "Kashmir", "Led Zeppelin", "rock", 4.3)
        assert False
    except ValueError as e:
        assert True

    try:
        #eroare la validare
        test_srv.add_melodie(2, "", "", "rap", 24.3)
        assert False
    except ValueError as e:
        assert True


def test_delete_melodie_srv():
    # to do
    pass


def test_filter_srv():
    # to do
    pass


def test_update_melodie_srv():
    # to do
    pass


if __name__ == "__main__":
    test_add_melodie_srv()
    test_delete_melodie_srv()
    test_filter_srv()
    test_update_melodie_srv()
