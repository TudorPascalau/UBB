import unittest

from domain.laborator import Laborator
from repository.repository_laboratoare import RepositoryLaboratoare
from service.service_laboratoare import ServiceLaboratoare
from utils.eroare_repository import EroareRepository


class TesteDomainLaboratoare(unittest.TestCase):

    def setUp(self):
        pass

    def test_creeaza_laborator(self):
        numar_lab = 1
        numar_problema = 2
        descriere = "Problema cu liste"
        an = 2024
        luna = 10
        zi = 15

        laborator = Laborator(numar_lab, numar_problema, descriere, an, luna, zi)

        self.assertEqual(laborator.get_numar_lab(), numar_lab)
        self.assertEqual(laborator.get_numar_problema(), numar_problema)
        self.assertEqual(laborator.get_descriere(), descriere)
        self.assertEqual(laborator.get_an(), an)
        self.assertEqual(laborator.get_luna(), luna)
        self.assertEqual(laborator.get_zi(), zi)

    def tearDown(self):
        pass


class TesteRepoLaboratoare(unittest.TestCase):

    def setUp(self):
        self.__test_repo = RepositoryLaboratoare()
        self.__test_laborator = Laborator(1, 1, "Problema 1", 2024, 10, 15)

    def test_adauga_laborator(self):
        """
        Metoda care testeaza adaugarea in repo de laboratoare
        """
        self.__test_repo.adauga_laborator(self.__test_laborator)
        self.assertEqual(len(self.__test_repo), 1)
        self.assertRaises(EroareRepository, self.__test_repo.adauga_laborator, self.__test_laborator)

        laborator = Laborator(1, 2, "Problema 2", 2024, 11, 20)
        self.__test_repo.adauga_laborator(laborator)
        self.assertEqual(len(self.__test_repo), 2)

    def test_get_all_laboratoare(self):
        """
        Metoda care testeaza get_all_laboratoare
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.__test_repo.adauga_laborator(self.__test_laborator)
        self.assertEqual(len(self.__test_repo), 1)

    def test_sterge_laborator(self):
        """
        Metoda care testeaza sterge_laborator
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.assertRaises(EroareRepository, self.__test_repo.sterge_laborator, self.__test_laborator)

        self.__test_repo.adauga_laborator(self.__test_laborator)
        self.assertEqual(len(self.__test_repo), 1)

        self.assertEqual(self.__test_repo.sterge_laborator(self.__test_laborator), self.__test_laborator)
        self.assertEqual(len(self.__test_repo), 0)

    def test_modifica_descriere_laborator(self):
        """
        Metoda care testeaza modifica_descriere_laborator
        """
        self.assertRaises(EroareRepository, self.__test_repo.modifica_descriere_laborator,
                          self.__test_laborator, "Noua descriere")

        self.__test_repo.adauga_laborator(self.__test_laborator)
        self.__test_repo.modifica_descriere_laborator(self.__test_laborator, "Noua descriere")

        self.assertEqual(self.__test_laborator.get_descriere(), "Noua descriere")

    def test_modifica_deadline_laborator(self):
        """
        Metoda care testeaza modifica_deadline_laborator
        """
        self.assertRaises(EroareRepository, self.__test_repo.modifica_deadline_laborator,
                          self.__test_laborator, 2025, 1, 10)

        self.__test_repo.adauga_laborator(self.__test_laborator)
        self.__test_repo.modifica_deadline_laborator(self.__test_laborator, 2025, 1, 10)

        self.assertEqual(self.__test_laborator.get_an(), 2025)
        self.assertEqual(self.__test_laborator.get_luna(), 1)
        self.assertEqual(self.__test_laborator.get_zi(), 10)

    def tearDown(self):
        del self.__test_repo


class TesteServiceLaboratoare(unittest.TestCase):

    def setUp(self):
        self.__test_repo = RepositoryLaboratoare()
        self.__test_service = ServiceLaboratoare(self.__test_repo)

        self.__test_laborator = Laborator(1, 1, "Problema 1", 2024, 10, 15)

    def test_adauga_laborator(self):
        """
        Metoda care testeaza adaugare laborator
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.__test_service.adauga_laborator(1, 1, "Problema 1", 2024, 10, 15)
        self.assertEqual(len(self.__test_repo), 1)

    def test_get_laborator_from_numar(self):
        """
        Metoda care testeaza get_laborator_from_numar
        """
        self.__test_service.adauga_laborator(1, 1, "Problema 1", 2024, 10, 15)
        laborator = self.__test_service.get_laborator_from_numar(1, 1)
        self.assertEqual(laborator.get_descriere(), "Problema 1")

    def test_sterge_laborator(self):
        """
        Metoda care testeaza stergere laborator
        """
        self.__test_service.adauga_laborator(1, 1, "Problema 1", 2024, 10, 15)
        self.assertEqual(len(self.__test_repo), 1)

        laborator_sters = self.__test_service.sterge_laborator(1, 1)
        self.assertEqual(laborator_sters.get_descriere(), "Problema 1")
        self.assertEqual(len(self.__test_repo), 0)

    def test_modifica_descriere_laborator(self):
        """
        Metoda care testeaza modifica_descriere_laborator
        """
        self.__test_service.adauga_laborator(1, 1, "Problema 1", 2024, 10, 15)
        self.__test_service.modifica_descriere_laborator(1, 1, "Noua descriere")
        laborator = self.__test_service.get_laborator_from_numar(1, 1)
        self.assertEqual(laborator.get_descriere(), "Noua descriere")

    def test_modifica_deadline_laborator(self):
        """
        Metoda care testeaza modifica_deadline_laborator
        """
        self.__test_service.adauga_laborator(1, 1, "Problema 1", 2024, 10, 15)
        self.__test_service.modifica_deadline_laborator(1, 1, 2025, 1, 10)
        laborator = self.__test_service.get_laborator_from_numar(1, 1)
        self.assertEqual(laborator.get_an(), 2025)
        self.assertEqual(laborator.get_luna(), 1)
        self.assertEqual(laborator.get_zi(), 10)

    def tearDown(self):
        del self.__test_repo
        del self.__test_service


if __name__ == '__main__':
    unittest.main()
