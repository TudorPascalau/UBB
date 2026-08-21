from domain.entities import Melodie
from repos.repo_melodii import RepoMelodieMemory


def test_add_repo():
    test_repo = RepoMelodieMemory()
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    test_repo.add(m)
    assert test_repo.size() == 1
    try:
        test_repo.add(m)
        assert False
    except ValueError:
        assert True

    m2 = Melodie(124, "Child in Time", "Deep Purple", "rock", 12.44)
    test_repo.add(m2)
    assert test_repo.size() == 2


def test_find_repo():
    test_repo = RepoMelodieMemory()
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    test_repo.add(m)
    assert test_repo.size() == 1
    m2 = Melodie(124, "Child in Time", "Deep Purple", "rock", 12.44)
    test_repo.add(m2)
    assert test_repo.size() == 2
    m3 = Melodie(145, "Brothers in Arms", "Dire Straits", "rock", 8.32)
    test_repo.add(m3)
    assert test_repo.size() == 3

    assert test_repo.find(2743) is None
    # is tests that we have the same object
    # should we test for equality between fields instead?
    assert test_repo.find(124) is m2
    assert test_repo.find(1324) is m
    assert test_repo.find(145) is m3


def test_delete_repo():
    test_repo = RepoMelodieMemory()
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    test_repo.add(m)
    assert test_repo.size() == 1
    m2 = Melodie(124, "Child in Time", "Deep Purple", "rock", 12.44)
    test_repo.add(m2)
    assert test_repo.size() == 2

    melodie_stearsa = test_repo.remove(124)
    assert test_repo.size() == 1
    assert melodie_stearsa.get_titlu() == "Child in Time"
    assert melodie_stearsa.get_artist() == "Deep Purple"

    try:
        # nu exista melodie cu id = 524
        test_repo.remove(524)
        assert False
    except ValueError:
        assert True


def test_update_repo():
    test_repo = RepoMelodieMemory()
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    test_repo.add(m)
    assert test_repo.size() == 1
    m2 = Melodie(1324, "Child in Time", "Deep Purple", "rock", 12.44)

    melodie_veche = test_repo.update(1324, m2)
    assert test_repo.size() == 1
    assert melodie_veche.get_titlu() == "Perfect Strangers"
    assert melodie_veche.get_artist() == "Deep Purple"

    melodie_actualizata = test_repo.find(1324)
    assert melodie_actualizata.get_titlu() == "Child in Time"
    assert melodie_actualizata.get_artist() == "Deep Purple"

    try:
        test_repo.update(524, m)
        assert False
    except ValueError:
        assert True


import unittest


class TestRepoMelodii(unittest.TestCase):
    def setUp(self) -> None:
        print("setUp called")
        self.__test_repo = RepoMelodieMemory()

    def test_add(self):
        print("test add")
        m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
        self.__test_repo.add(m)
        self.assertEqual(self.__test_repo.size(), 1)
        self.assertRaises(ValueError, self.__test_repo.add, m)

        m2 = Melodie(124, "Child in Time", "Deep Purple", "rock", 12.44)
        self.__test_repo.add(m2)
        self.assertEqual(self.__test_repo.size(), 2)

    def test_2(self):
        print("test2")
    def tearDown(self) -> None:
        print("tearDown")
        del self.__test_repo


if __name__ == "__main__":
    unittest.main(verbosity=2)