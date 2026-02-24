from domain.assignment import Assignment
from errors.eroare_repo import EroareRepository


class ServiceAssignment:
    def __init__(self, repo_assignment, validator_assignment, repo_studenti, repo_laboratoare):
        self.__repo_assignment = repo_assignment
        self.__validator_assignment = validator_assignment
        self.__repo_studenti = repo_studenti
        self.__repo_laboratoare = repo_laboratoare

    def adauga_assignment(self, studentID, numere_laborator):
        """
        Metoda pentru adaugarea unui assingment
        :param studentID:
        :param numere_laborator:
        :return:
        """
        assignment = Assignment(None, studentID, numere_laborator)
        self.__validator_assignment.valideaza_assignment(assignment)

        studenti = self.__repo_studenti.get_all_studenti()
        student_gasit = False
        for student in studenti:
            if student.get_studentID() == studentID:
                student_gasit = True

        if not student_gasit:
            raise EroareRepository("Nu exista student cu ID-ul dat")

        laboratoare = self.__repo_laboratoare.get_all_laboratoare()
        laborator_gasit = False
        for laboratoare in laboratoare:
            if laboratoare.get_numere_laborator() == numere_laborator:
                laborator_gasit = True

        if not laborator_gasit:
            raise EroareRepository("Nu exista laborator cu numarul dat")

        self.__repo_assignment.adauga_assignment(assignment)


    def get_assignment_by_ids(self, studentID, numere_laborator):
        """
        Metoda care gaseste un assignment pe baza id-urilor asociate
        :param studentID: studentul caruia ii este asignat
        :param numere_laborator: laboratorul asignat
        :return: assignmentul, daca exista
        :raises: EroareRepository, daca nu exista
        """

        assignments = self.__repo_assignment.get_all_assignments()
        for assignment in assignments:
            if assignment.get_studentID_assign() == studentID and assignment.get_numere_laborator_assign() == numere_laborator:
                return assignment

        raise EroareRepository("Nu exista assignment cu id-urile date")

    def notare_assignment(self, studentID, numere_laborator, nota):
        """
        Metoda care asociaza o nota unui assignment
        :param studentID: studentul caruia ii este asignat
        :param numere_laborator: laboratorul asignat
        """

        assignment = self.get_assignment_by_ids(studentID, numere_laborator)
        self.__repo_assignment.modifica_nota_assignment(assignment, nota)

    def sterge_assignment(self, studentID, numere_laborator):
        """
        Metoda care sterge un assignment
        :param studentID: studentul caruia ii este asignat
        :param numere_laborator: laboratorul asignat
        """
        assignment = self.get_assignment_by_ids(studentID, numere_laborator)
        self.__repo_assignment.sterge_assignment(assignment)

    def access_assignments(self):
        """
        Metoda care accesseaza toate assignmenturile
        """
        return self.__repo_assignment.get_all_assignments()