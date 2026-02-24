from domain.assignment import Assignment
from utils.eroare_repository import EroareRepository

class RepositoryAssignments:

    def __init__(self):
        self.__repo_assignments = {}

    def __len__(self):
        return len(self.__repo_assignments)

    def adauga_assignment(self, assignment):
        """
        Metoda care adauga un assignment in repository
        :param assignment: assignmentul de adaugat
        """
        student_id = assignment.get_student_id()
        lab_id = assignment.get_lab_id()
        assignment_id = assignment.get_assignment_id()

        for prev_assignment in self.__repo_assignments.values():
            if prev_assignment.get_student_id() == student_id and prev_assignment.get_lab_id() == lab_id:
                raise EroareRepository("Studentul are deja asignat acest laborator")

        self.__repo_assignments[assignment_id] = assignment

    def get_all_assignments(self):
        return self.__repo_assignments

    def sterge_assignment(self, assignment):
        """
        Metoda care sterge un assignment in repository
        :param assignment: assignmentul de sters
        :return: assignmentul sters
        :raises EroareRepository, daca nu exista assignmentul
        """
        assignment_id = assignment.get_assignment_id()
        if assignment_id not in self.__repo_assignments:
            raise EroareRepository("Assignmentul nu exista")

        assignment_sters = assignment
        del self.__repo_assignments[assignment_id]
        return assignment_sters

    def modifica_nota_assignment(self, assignment, nota):
        """
        Metoda care noteaza un assignment in repository
        :param assignment: assignment de notat
        :param nota: nota
        :raises EroareRepository, daca nu exista assignmentul
        """
        if assignment not in self.__repo_assignments.values():
            raise EroareRepository("Assignmentul nu exista")

        assignment.set_nota(nota)

class RepositoryAssignmentsFile(RepositoryAssignments):

    def __init__(self, filepath):
        super().__init__()
        super().__len__()
        self.__filepath = filepath
        self.__load_file()

    def __load_file(self):
        """
        Metoda care incearca sa incarce datele din fisier
        :raises EroareRepository, daca exista probleme la citire date din fisier
        """

        try:
            with open(self.__filepath, "r") as file:
                linii = file.readlines()
                for linie in linii:
                    linie = linie.strip()
                    if linie != "":
                        parti = linie.split(",")
                        assignment_id = int(parti[0])
                        student_id = int(parti[1])
                        numar_lab = int(parti[2])
                        numar_problema = int(parti[3])
                        if parti[4] == "None":
                            nota = None
                        else:
                            nota = float(parti[4])

                        lab_id = (numar_lab, numar_problema)

                        assignment = Assignment(assignment_id, student_id, lab_id, nota)
                        super().adauga_assignment(assignment)


        except IOError:
            raise EroareRepository("Eroare la citirea din fisier")

    def adauga_assignment(self, assignment):
        super().adauga_assignment(assignment)
        self.__store()

    def get_all_assignments(self):
        return super().get_all_assignments()

    def sterge_assignment(self, assignment):
        super().sterge_assignment(assignment)
        self.__store()

    def modifica_nota_assignment(self, assignment, nota):
        super().modifica_nota_assignment(assignment, nota)
        self.__store()

    def __store(self):
        """
        Metoda care salveaza datele in fisier
        :raises EroareRepository, daca exista probleme la scriere date in fisier
        """

        try:

            with open(self.__filepath, "w") as file:
                assignments = self.get_all_assignments()

                for assignment in assignments.values():
                    if assignment.get_nota() is None:
                        assignment_str = (str(assignment.get_assignment_id()) + "," + str(assignment.get_student_id())
                                          + "," + str(assignment.get_lab_id()[0]) + "," + str(assignment.get_lab_id()[1])
                                          + "," + "None")

                    else:
                        assignment_str = (str(assignment.get_assignment_id()) + "," + str(assignment.get_student_id())
                                          + "," + str(assignment.get_lab_id()[0]) + "," + str(assignment.get_lab_id()[1])
                                          + "," + str(assignment.get_nota()))

                    file.write(assignment_str + '\n')

        except IOError:
            raise EroareRepository("Eroare la citirea din fisier")