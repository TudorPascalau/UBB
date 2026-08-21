import unittest

from domain.student import Student
from repository.repository_student import RepositoryStudenti
from service.service_studenti import ServiceStudenti
from utils.eroare_repository import EroareRepository

class TesteDomainStudenti(unittest.TestCase):

    def setUp(self):
        pass

    def test_creeaza_student(self):
        student_id = 23
        nume = "Jordan"
        grupa = 323

        student = Student(student_id, nume, grupa)

        self.assertEqual(student.get_student_id(), student_id)
        self.assertEqual(student.get_nume(), nume)
        self.assertEqual(student.get_grupa(), grupa)

    def tearDown(self):
        pass


class TesteRepoStudenti(unittest.TestCase):

    def setUp(self):
        self.__test_repo = RepositoryStudenti()
        self.__test_student = Student(23, "Jordan", 323)

    def test_adauga_student(self):
        """
        Metoda care testeaza adaugarea in repo de studenti
        """
        self.__test_repo.adauga_student(self.__test_student)
        self.assertEqual(len(self.__test_repo), 1)
        self.assertRaises(EroareRepository, self.__test_repo.adauga_student, self.__test_student)

        student = Student(14, "Pascalau", 215)
        self.__test_repo.adauga_student(student)
        self.assertEqual(len(self.__test_repo), 2)

    def test_get_all_studenti(self):
        """
        Metoda care testeaza ca get_all_studenti
        """

        self.assertEqual(len(self.__test_repo), 0)
        self.__test_repo.adauga_student(self.__test_student)
        self.assertEqual(len(self.__test_repo), 1)


    def test_sterge_studenti(self):
        """
        Metoda care testeaza ca sterge_studenti
        """

        self.assertEqual(len(self.__test_repo), 0)
        self.assertRaises(EroareRepository, self.__test_repo.sterge_student, self.__test_student)

        self.__test_repo.adauga_student(self.__test_student)
        self.assertEqual(len(self.__test_repo), 1)

        self.assertEqual(self.__test_repo.sterge_student(self.__test_student), self.__test_student)
        self.assertEqual(len(self.__test_repo), 0)

    def test_modifica_nume_student(self):
        """
        Metoda care testeaza modifica_nume_student
        """

        self.assertRaises(EroareRepository, self.__test_repo.modifica_nume_student, self.__test_student, "Ion")

        self.__test_repo.adauga_student(self.__test_student)
        self.__test_repo.modifica_nume_student(self.__test_student, "Ion")

        self.assertEqual(self.__test_student.get_nume(), "Ion")

    def test_modifica_grupa_student(self):
        """
        Metoda care testeaza modifica_grupa_student
        """

        self.assertRaises(EroareRepository, self.__test_repo.modifica_grupa_student, self.__test_student, 215)

        self.__test_repo.adauga_student(self.__test_student)
        self.__test_repo.modifica_grupa_student(self.__test_student, 215)

        self.assertEqual(self.__test_student.get_grupa(), 215)

    def tearDown(self):
        del self.__test_repo

class TesteServiceStudenti(unittest.TestCase):

    def setUp(self):
        self.__test_repo = RepositoryStudenti()
        self.__test_service = ServiceStudenti(self.__test_repo)

        self.__test_student = Student(23, "Jordan", 323)

    def test_adauga_student(self):
        """
        Metoda care testeaza adaugare student
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(len(self.__test_repo), 1)

    def test_get_student_from_id(self):
        """
        Metoda care testeaza get_student_from_id
        """

        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(self.__test_service.get_student_from_id(23).get_nume(), "Jordan")

    def test_get_student_from_id_rec(self):
        """
        Metoda care testeaza get_student_from_id_rec
        :return:
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(self.__test_service.get_student_from_id_rec(23).get_nume(), "Jordan")

    def test_sterge_studenti(self):
        """
        Metoda care testeaza adaugare student
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(len(self.__test_repo), 1)

        self.assertEqual(self.__test_service.sterge_student(23).get_nume(), "Jordan")
        self.assertEqual(len(self.__test_repo), 0)

    def test_modifica_nume_student(self):
        """
        Metoda care testeaza modifica_nume_student
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.__test_service.modifica_nume_student(23, "Ion")
        self.assertEqual(self.__test_service.get_student_from_id(23).get_nume(), "Ion")

    def test_modifica_grupa_student(self):
        """
        Metoda care testeaza modifica_nume_student
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.__test_service.modifica_grupa_student(23, 215)
        self.assertEqual(self.__test_service.get_student_from_id(23).get_grupa(), 215)

    def test_get_studenti_grupa(self):
        """
        Metoda care testeaza get_studenti_grupa
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(len(self.__test_service.gaseste_studenti_grupa(323)), 1)
        self.assertEqual(len(self.__test_service.gaseste_studenti_grupa(215)), 0)


    def test_get_studenti_grupa_rec(self):
        """
        Metoda care testeaza get_studenti_grupa_rec
        """
        self.__test_service.adauga_student(23, "Jordan", 323)
        self.assertEqual(len(self.__test_service.gaseste_studenti_grupa_rec(323)), 1)
        self.assertEqual(len(self.__test_service.gaseste_studenti_grupa_rec(215)), 0)

    def tearDown(self):
        del self.__test_repo
        del self.__test_service

if __name__ == '__main__':
    unittest.main()
