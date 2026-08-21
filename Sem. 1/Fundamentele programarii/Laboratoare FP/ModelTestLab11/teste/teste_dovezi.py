
import unittest

from business.service_dovezi import ServiceDovezi
from domain.dovada import Dovada
from repository.repo_dovezi import RepositoryDovezi, RepositoryDoveziFile
from utils.eroare_repo import EroareRepository


class TesteDovadaDomain(unittest.TestCase):

    def setUp(self):
        pass

    def test_creaza_dovada(self):

        id_dovada = 1
        descriere = "crima"
        data = "2025/12/25"
        tip = "arma"
        suspect = "Dexter Morgan"

        dovada = Dovada(id_dovada, descriere, data, tip, suspect)

        self.assertEqual(dovada.get_id_dovada(), id_dovada)
        self.assertEqual(dovada.get_descriere(), descriere)
        self.assertEqual(dovada.get_data(), data)
        self.assertEqual(dovada.get_tip(), tip)
        self.assertEqual(dovada.get_suspect(), suspect)

    def tearDown(self):
        pass

class TesteDovadaRepo(unittest.TestCase):

    def setUp(self):
        self.__repo_test = RepositoryDovezi()
        self.__dovada_test = Dovada(1, "crima", "2025", "arma", "Dexter Morgan")

    def test_adauga_dovada(self):
        self.assertEqual(len(self.__repo_test), 0)

        self.__repo_test.adauga_dovada(self.__dovada_test)
        self.assertEqual(len(self.__repo_test), 1)

        self.assertRaises(EroareRepository, self.__repo_test.adauga_dovada, self.__dovada_test)

    def test_get_all_dovezi(self):
        self.assertEqual(len(self.__repo_test), 0)

        self.__repo_test.adauga_dovada(self.__dovada_test)
        dovezi = self.__repo_test.get_all_dovezi()
        self.assertEqual(len(dovezi), 1)
        self.assertEqual(dovezi[1], self.__dovada_test)

    def tearDown(self):
        del self.__repo_test

class TesteDovadaRepoFile(unittest.TestCase):

    def setUp(self):
        dovezi_filepath = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\ModelTestLab11\sources\dovezi.txt"
        self.__repo_dovezi = RepositoryDoveziFile(dovezi_filepath)

    def tearDown(self):
        del self.__repo_dovezi

class TesteDovadaService(unittest.TestCase):

    def setUp(self):
        self.__repo_test = RepositoryDovezi()
        self.__service_test = ServiceDovezi(self.__repo_test)

    def test_adauga_dovada(self):
        self.assertEqual(len(self.__repo_test), 0)

        self.__service_test.adauga_dovada(1, "crima", "2025", "arma", "Dexter Morgan")
        self.assertEqual(len(self.__repo_test), 1)

    def test_get_dovezi(self):
        self.assertEqual(len(self.__repo_test), 0)
        dovezi = self.__service_test.get_dovezi()
        self.assertEqual(len(dovezi), 0)

        self.__service_test.adauga_dovada(1, "crima", "2025", "arma", "Dexter Morgan")
        dovezi = self.__service_test.get_dovezi()
        self.assertEqual(len(dovezi), 1)
        self.assertEqual(dovezi[1].get_descriere(), "crima")

    def test_get_dovezi_string(self):
        self.assertEqual(len(self.__repo_test), 0)

        self.__service_test.adauga_dovada(1, "crima", "2025", "arma", "Dexter Morgan")
        self.__service_test.adauga_dovada(2, "crima", "2025", "witness", "Brian Moser")

        self.assertEqual(len(self.__repo_test), 2)

        dovezi_string = self.__service_test.get_dovezi_string("D")
        self.assertEqual(len(dovezi_string), 1)

        dovezi_string = self.__service_test.get_dovezi_string("M")
        self.assertEqual(len(dovezi_string), 2)


    def tearDown(self):
        del self.__repo_test
        del self.__service_test