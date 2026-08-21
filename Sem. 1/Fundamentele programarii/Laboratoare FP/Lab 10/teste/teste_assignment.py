
import unittest

from domain.assignment import Assignment
from domain.laborator import Laborator
from domain.student import Student
from repository.repository_assignments import RepositoryAssignments
from repository.repository_laboratoare import RepositoryLaboratoare
from repository.repository_student import RepositoryStudenti
from service.service_assignments import ServiceAssignments
from utils.eroare_repository import EroareRepository


class TesteDomainAssignments(unittest.TestCase):

    def setUp(self):
        pass

    def test_creeaza_assignment(self):
        assignment_id = 1
        student_id = 23
        lab_id = 101
        nota = None

        assignment = Assignment(assignment_id, student_id, lab_id, nota)

        self.assertEqual(assignment.get_assignment_id(), assignment_id)
        self.assertEqual(assignment.get_student_id(), student_id)
        self.assertEqual(assignment.get_lab_id(), lab_id)
        self.assertEqual(assignment.get_nota(), nota)

        assignment.set_nota(10)
        self.assertEqual(assignment.get_nota(), 10)

    def tearDown(self):
        pass


class TesteRepoAssignments(unittest.TestCase):

    def setUp(self):
        self.__test_repo = RepositoryAssignments()
        self.__test_assignment = Assignment(1, 23, 101, None)

    def test_adauga_assignment(self):
        """
        Metoda care testeaza adaugarea in repo de assignments
        """
        self.__test_repo.adauga_assignment(self.__test_assignment)
        self.assertEqual(len(self.__test_repo), 1)

        assignment2 = Assignment(2, 23, 101, None)
        self.assertRaises(EroareRepository, self.__test_repo.adauga_assignment, assignment2)

        assignment3 = Assignment(3, 24, 101, None)
        self.__test_repo.adauga_assignment(assignment3)
        self.assertEqual(len(self.__test_repo), 2)

    def test_get_all_assignments(self):
        """
        Metoda care testeaza get_all_assignments
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.__test_repo.adauga_assignment(self.__test_assignment)
        self.assertEqual(len(self.__test_repo), 1)

    def test_sterge_assignment(self):
        """
        Metoda care testeaza sterge_assignment
        """
        self.assertEqual(len(self.__test_repo), 0)
        self.assertRaises(EroareRepository, self.__test_repo.sterge_assignment, self.__test_assignment)

        self.__test_repo.adauga_assignment(self.__test_assignment)
        self.assertEqual(len(self.__test_repo), 1)

        self.assertEqual(self.__test_repo.sterge_assignment(self.__test_assignment), self.__test_assignment)
        self.assertEqual(len(self.__test_repo), 0)

    def test_modifica_nota_assignment(self):
        """
        Metoda care testeaza modifica_nota_assigment
        """
        # inainte de adaugare -> eroare
        self.assertRaises(EroareRepository, self.__test_repo.modifica_nota_assignment, self.__test_assignment, 9)

        # dupa adaugare -> nota se schimba
        self.__test_repo.adauga_assignment(self.__test_assignment)
        self.__test_repo.modifica_nota_assignment(self.__test_assignment, 9)

        self.assertEqual(self.__test_assignment.get_nota(), 9)

    def tearDown(self):
        del self.__test_repo


class TesteServiceAssignments(unittest.TestCase):

    def setUp(self):
        self.__repo_assignments = RepositoryAssignments()
        self.__repo_studenti = {23: "Jordan"}
        self.__repo_laboratoare = {(7,2): "Lab1"}

        self.__service = ServiceAssignments(self.__repo_assignments,
                                            self.__repo_studenti,
                                            self.__repo_laboratoare)

    def test_adauga_assignment(self):
        """
        Metoda care testeaza adaugare assignment
        """
        self.assertEqual(len(self.__repo_assignments), 0)
        self.__service.adauga_assignment(23, (7,2))
        self.assertEqual(len(self.__repo_assignments), 1)

        self.assertRaises(EroareRepository, self.__service.adauga_assignment, 999, (7,2))
        self.assertRaises(EroareRepository, self.__service.adauga_assignment, 23, (7,3))

    def test_get_assignment_by_id(self):
        """
        Metoda care testeaza get_assignment_by_id
        """
        self.__service.adauga_assignment(23, (7,2))  # va avea id 1
        assignment = self.__service.get_assignment_by_id(230702)

        self.assertEqual(assignment.get_student_id(), 23)
        self.assertEqual(assignment.get_lab_id(), (7,2))

        self.assertRaises(EroareRepository, self.__service.get_assignment_by_id, 999)

    def test_sterge_assignment(self):
        """
        Metoda care testeaza sterge_assignment
        """
        self.__service.adauga_assignment(23, (7,2))
        self.assertEqual(len(self.__repo_assignments), 1)

        assignment_sters = self.__service.sterge_assignment(230702)
        self.assertEqual(assignment_sters.get_student_id(), 23)
        self.assertEqual(len(self.__repo_assignments), 0)

    def test_noteaza_assignment(self):
        """
        Metoda care testeaza noteaza_assignment
        """
        self.__service.adauga_assignment(23, (7,2))  # id 1
        self.__service.noteaza_assignment(230702, 10)

        assignment = self.__service.get_assignment_by_id(230702)
        self.assertEqual(assignment.get_nota(), 10)

    def tearDown(self):
        del self.__repo_assignments
        del self.__service

class TesteServiceAssignmentsMedii(unittest.TestCase):

    def setUp(self):
        self.__repo_assignments = RepositoryAssignments()
        self.__repo_studenti = {
            23: Student(23, "Jordan", 323),
            14: Student(14, "Pascalau", 215)
        }

        self.__repo_laboratoare = {
            (7, 2): Laborator(7, 2, "fp", 2025, 12, 25),
            (8, 2): Laborator(8, 2, "asc", 2025, 12, 25)
        }

        self.__service = ServiceAssignments(self.__repo_assignments,
                                            self.__repo_studenti,
                                            self.__repo_laboratoare)



        self.__service.adauga_assignment(23, (7,2))
        self.__service.noteaza_assignment(230702, 9)

        self.__service.adauga_assignment(23, (8,2))
        self.__service.noteaza_assignment(230802, 8)

        self.__service.adauga_assignment(14, (7, 2))
        self.__service.noteaza_assignment(140702, 9)

        self.__service.adauga_assignment(14, (8, 2))
        self.__service.noteaza_assignment(140802, 10)


    def test_get_medii_studenti(self):

        medii = self.__service.get_medii_studenti()
        self.assertEqual(medii[0].get_student_id(), 23)
        self.assertEqual(medii[0].get_medie(), 8.5)

    def test_medii_ordonate_nume(self):

        medii_nume = self.__service.get_medii_ordonate_nume()
        self.assertEqual(medii_nume[0].get_student_id(), 23)

    def test_medii_ordonate_nota(self):
        medii_nota = self.__service.get_medii_ordonate_nota()
        self.assertEqual(medii_nota[0].get_student_id(), 14)
        self.assertEqual(medii_nota[0].get_medie(), 9.5)

    def tearDown(self):
        del self.__repo_assignments
        del self.__repo_studenti
        del self.__repo_laboratoare
        del self.__service


if __name__ == '__main__':
    unittest.main()
