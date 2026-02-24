from domain.assignment import Assignment
from domain.laborator import Laborator
from errors.eroare_repo import EroareRepository
from repository.repo_laboratoare import RepositoryLaboratoare
from repository.repo_studenti import RepositoryStudenti
from repository.repo_assignment import RepositoryAssignments
from service.service_assignment import ServiceAssignment
from service.service_laboratoare import ServiceLaboratoare
from service.service_studenti import ServiceStudenti
from validare.validator_laborator import ValidatorLaborator
from validare.validator_student import ValidatorStudent
from validare.validator_assignment import ValidatorAssignment


class TesteAssignment:

    def test_all(self):
        """
        Metoda care apeleaza toate testele ce tin de assignment uri
        """
        print("incepem testarea assignmenturilor ...")
        self.__test_creaza_assignment()
        self.__test_adauga_assignment()
        self.__test_get_assignment_by_ids()
        self.__test_notare_assignment()
        self.__test_sterge_assignment()
        print("teste finalizate cu succes !!! \n")


    def __test_creaza_assignment(self):
        """
        Metoda care testeaza creeaza assignment
        """
        print("incepem testul creeaza assignment...")

        studentID = 23

        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 12
        zi = 1
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        numere_lab = laborator.get_numere_laborator()

        nota = 10
        assignment = Assignment(nota, studentID, numere_lab)

        assert assignment.get_nota_assign() == nota
        assert assignment.get_studentID_assign() == studentID
        assert assignment.get_numere_laborator_assign() == numere_lab

        print("test finalizat cu succes")

    def __test_adauga_assignment(self):
        """
        Metoda care testeaza adauga assignment
        """
        print("incepem testul adauga assignment...")

        studentID = 23
        nume = "Jordan"
        grupa = 323
        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)
        service_studenti.adauga_student(studentID, nume, grupa)

        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 12
        zi = 1
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        numere_laborator = laborator.get_numere_laborator()
        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)
        service_laboratoare.adauga_laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        repo_assignments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assignments, validator_assignment, repo_studenti, repo_laboratoare)

        assert len(repo_assignments) == 0

        service_assignment.adauga_assignment(studentID, numere_laborator)
        assert len(repo_assignments) == 1


        try:
            service_assignment.adauga_assignment(20, numere_laborator)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "Nu exista student cu ID-ul dat"

        print("test finalizat cu succes")

    def __test_get_assignment_by_ids(self):
        """
        Metoda care testeaza get assignment by ids
        """
        print("incepem testul get assignment by ids...")

        studentID = 23
        nume = "Jordan"
        grupa = 323
        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)
        service_studenti.adauga_student(studentID, nume, grupa)

        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 12
        zi = 1
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        numere_laborator = laborator.get_numere_laborator()
        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)
        service_laboratoare.adauga_laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        repo_assignments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assignments, validator_assignment, repo_studenti, repo_laboratoare)

        service_assignment.adauga_assignment(studentID, numere_laborator)
        assert service_assignment.get_assignment_by_ids(studentID, numere_laborator).get_studentID_assign() == studentID
        assert service_assignment.get_assignment_by_ids(studentID, numere_laborator).get_numere_laborator_assign() == numere_laborator

        try:
            assignment = service_assignment.get_assignment_by_ids(30, numere_laborator)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "Nu exista assignment cu id-urile date"

        print("test finalizat cu succes")

    def __test_notare_assignment(self):
        """
        Metoda care testeaza notare assignment
        """
        print("incepem testul notare assignment...")
        studentID = 23
        nume = "Jordan"
        grupa = 323
        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)
        service_studenti.adauga_student(studentID, nume, grupa)

        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 12
        zi = 1
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        numere_laborator = laborator.get_numere_laborator()
        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)
        service_laboratoare.adauga_laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        repo_assignments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assignments, validator_assignment, repo_studenti, repo_laboratoare)

        service_assignment.adauga_assignment(studentID, numere_laborator)
        assert service_assignment.get_assignment_by_ids(studentID, numere_laborator).get_nota_assign() is None

        service_assignment.notare_assignment(studentID, numere_laborator, 10)
        assert service_assignment.get_assignment_by_ids(studentID, numere_laborator).get_nota_assign() == 10

        print("test finalizat cu succes")

    def __test_sterge_assignment(self):
        """
        Metoda care testeaza sterge assignment
        """
        print("incepem testul sterge assignment...")

        studentID = 23
        nume = "Jordan"
        grupa = 323
        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)
        service_studenti.adauga_student(studentID, nume, grupa)

        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 12
        zi = 1
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        numere_laborator = laborator.get_numere_laborator()
        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)
        service_laboratoare.adauga_laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        repo_assignments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assignments, validator_assignment, repo_studenti, repo_laboratoare)

        assert len(repo_assignments) == 0

        service_assignment.adauga_assignment(studentID, numere_laborator)
        assert len(repo_assignments) == 1

        service_assignment.sterge_assignment(studentID, numere_laborator)
        assert len(repo_assignments) == 0

        print("test finalizat cu succes")