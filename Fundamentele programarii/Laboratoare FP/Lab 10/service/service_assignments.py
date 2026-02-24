from domain.assignment import Assignment
from domain.student_medie_dto import StudentMedieDTO
from utils.eroare_repository import EroareRepository
from utils.utilitate_sortari import selection_sort


class ServiceAssignments:

    def __init__(self, repo_assignments, repo_studenti, repo_laboratoare):
        self.__repo_assignments = repo_assignments
        self.__repo_studenti = repo_studenti
        self.__repo_laboratoare = repo_laboratoare

    def adauga_assignment(self, student_id, lab_id):
        """
        Metoda care adauga un assignment
        :param student_id: id student cu assingment
        :param lab_id: id lab cu assignment
        """

        if student_id not in self.__repo_studenti:
            raise EroareRepository("Nu exista student cu id dat!")

        if lab_id not in self.__repo_laboratoare:
            raise EroareRepository("Nu exista lab cu id dat!")

        assignment_id = (student_id * 100 + lab_id[0])*100 + lab_id[1]
        assignment = Assignment(assignment_id, student_id, lab_id, None)

        self.__repo_assignments.adauga_assignment(assignment)

    def get_assignments(self):
        """
        Metoda care returneaza toate assignments
        :return: toate assignmentsurile
        """
        return self.__repo_assignments.get_all_assignments()

    def get_assignment_by_id(self, assignment_id):
        """
        Metoda care gaseste un assignment dupa id-ul sau
        :param assignment_id: id-ul assignmentului
        :return: assignmentul, daca exista
        """

        assignments = self.get_assignments()
        for assignment in assignments.values():
            if assignment.get_assignment_id() == assignment_id:
                return assignment

        raise EroareRepository("Nu exista assignment cu id dat")

    def sterge_assignment(self, assignment_id):
        """
        Metoda care sterge assignment cu id dat
        :param assignment_id: id assignment
        :return: assignmentul sters
        """
        assignment = self.get_assignment_by_id(assignment_id)
        return self.__repo_assignments.sterge_assignment(assignment)

    def noteaza_assignment(self, assignment_id, nota):
        """
        Metoda care noteaza un assignment
        :param assignment_id: id assignment de notat
        :param nota: nota ce trebuie pusa
        """
        assignment = self.get_assignment_by_id(assignment_id)
        self.__repo_assignments.modifica_nota_assignment(assignment, nota)


    def get_medii_studenti(self):
        """
        Metoda care genereaza o lista cu toate obiectele student/medie
        :return: lista de studenti/medie

        Analiza complexitate:
            fie n - numar assignments si m - numar note
            parcurgere assignments -> theta(n)
            parcurgere student_nota -> theta(m)

            T(n) = theta(n+m), cu n >= m => theta(n)

            Caz favorabil: theta(n)
            Caz defavorabil: theta(n) #Se parcurge tot indiferent

            -> Complexitate theta(n)
        """

        student_nota = {}
        medii = []

        assignments = self.get_assignments()
        for assignment in assignments.values():

            student_id = assignment.get_student_id()
            nota = assignment.get_nota()

            if nota is None:
                continue

            if student_id not in student_nota:
                student_nota[student_id] = [0,0]

            student_nota[student_id][0] += nota
            student_nota[student_id][1] += 1

        for student_id in student_nota:
            medie = student_nota[student_id][0] / student_nota[student_id][1]
            nume_student = self.__repo_studenti[student_id].get_nume()
            student_medie_dto = StudentMedieDTO(student_id, nume_student, medie)

            medii.append(student_medie_dto)

        return medii

    def get_medii_ordonate_nume(self):
        """
        Metoda care ordoneaza mediile dupa nume
        :return: lista cu mediile sortate
        """

        medii = self.get_medii_studenti()
        medii.sort(key = lambda x: x.get_nume())

        return medii

    def get_medii_ordonate_nota(self):
        """
        Metoda care ordoneaza mediile dupa nota
        :return: lista cu mediile sortate
        """

        medii = self.get_medii_studenti()
        medii.sort(key = lambda x: x.get_medie(), reverse=True)

        return medii

    def get_top20_medii(self):
        """
        Metoda care arata primii 20% de studenti
        :return: lista cu cei 20%
        """

        medii = self.get_medii_ordonate_nota()

        lung = len(medii)
        lung_20 = 20*lung//100

        if lung > 0 and lung_20 == 0:
            lung_20 = 1

        medii = medii[:lung_20]
        return medii

    def get_medii_ordonate_bubble(self):
        """
        Metoda care sorteaza mediile folosind BubbleSort
        :return: lista cu mediile sortate
        """

        medii = self.get_medii_studenti()

        n = len(medii)
        swapped = True
        while swapped:
            swapped = False
            for index in range (0, n-1):
                if medii[index].get_medie() < medii[index+1].get_medie():
                    medii[index], medii[index+1] = medii[index+1], medii[index]
                    swapped = True
            n -= 1

        return medii

    def get_medii_ordonate_shell(self):
        """
        Metoda care ordoneaza mediile folosind ShellSort
        :return: lista cu mediile sortate
        """
        medii = self.get_medii_studenti()

        n = len(medii)
        gap = n//2
        while gap > 0:
            for i in range(gap,n):
                temp = medii[i]
                j = i

                while j >= gap and medii[j-gap].get_medie() < temp.get_medie():
                    medii[j] = medii [j-gap]
                    j -= gap

                medii[j] = temp

            gap //= 2

        return medii

    def get_assignments_ordonate(self):
        """
        Metoda care sorteaza assignments-urile dupa id-lab, apoi dupa student_id
        :return:
        """

        assignments = list(self.get_assignments().values())
        assign_sortate = selection_sort(assignments, key=lambda a: (a.get_lab_id()[0], a.get_lab_id()[1] , a.get_student_id()))
        return assign_sortate