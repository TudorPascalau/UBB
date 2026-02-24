import unittest

from domain import automobil
from domain.automobil import Automobil
from repository.repository_automobile import RepositoryAutomobile, EroareRepository


class TestRepository(unittest.TestCase):
    def setUp(self):
        file_path = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Examen-practic-automobile\sources\automobile_test.txt"
        self.repo = RepositoryAutomobile(file_path)
        self.repo.clear()

        self.automobil = Automobil(1,"Ford",20000,"Mustang","22:03:2025")

    def tearDown(self):
        pass

    def testAccessFisier(self):
        temp_path = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Examen-practic-automobile\sources\automobile_test.txt"
        with open(temp_path, "w") as file:
            file.write("1,Ford,20000,Mustang,22:03:2025")

        try:
            repo = RepositoryAutomobile(temp_path)
            automobile = repo.get_all()

            self.assertEqual(len(automobile), 1)

        finally:
            pass

    def testAdauga(self):
        self.assertEqual(len(self.repo), 0)

        self.repo.adauga(self.automobil)
        self.assertEqual(len(self.repo), 1)

        with self.assertRaises(EroareRepository):
            self.repo.adauga(self.automobil)

    def testClear(self):
        self.assertEqual(len(self.repo), 0)

        self.repo.adauga(self.automobil)
        self.assertEqual(len(self.repo), 1)

        self.repo.clear()
        self.assertEqual(len(self.repo), 0)

    def testGetAll(self):
        automobile = self.repo.get_all()
        self.assertEqual(len(automobile), 0)

        self.repo.adauga(self.automobil)
        automobile = self.repo.get_all()
        self.assertEqual(len(automobile), 1)

        self.repo.clear()
        automobile = self.repo.get_all()
        self.assertEqual(len(automobile), 0)