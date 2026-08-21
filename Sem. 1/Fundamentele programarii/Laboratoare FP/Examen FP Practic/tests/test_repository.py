import unittest

from domain.sedinta import Sedinta
from repository.repository_sedinte import RepositorySedinte, EroareRepository


class TestRepository(unittest.TestCase):


    def setUp(self):
        file_path = r"C:\Users\tudor\Desktop\Examen FP Practic\sources\test.txt"
        self.repository = RepositorySedinte(file_path)

        s_id = ("Discutie","normala")
        self.sedinta = Sedinta(s_id, "20.02", "08:00", "Discutie", "normal")

    def tearDown(self):
        self.repository.clear_repo()

    def testAdaugaRepository(self):
        """
        Testare adaugare sedinta in repository
        """

        self.assertEqual(len(self.repository),0)

        self.repository.adauga_repo(self.sedinta)
        self.assertEqual(len(self.repository),1)

        with self.assertRaises(EroareRepository):
            self.repository.adauga_repo(self.sedinta)

    def testGetAllRepository(self):
        """
        Testare getall sedinte in repository
        """

        repo = self.repository.get_all_repo()
        self.assertEqual(len(repo),0)

        self.repository.adauga_repo(self.sedinta)


        repo = self.repository.get_all_repo()
        self.assertEqual(len(repo),1)

    def testClearRepository(self):
        """
        Testare clear repository
        :return:
        """

        repo = self.repository.get_all_repo()
        self.assertEqual(len(repo),0)

        self.repository.adauga_repo(self.sedinta)
        repo = self.repository.get_all_repo()
        self.assertEqual(len(repo),1)

        self.repository.clear_repo()
        repo = self.repository.get_all_repo()
        self.assertEqual(len(repo),0)