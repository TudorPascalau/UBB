from errors.eroare_repo import EroareRepository


class RepositoryAssignments():

    def __init__(self):
        self.__assignments = []

    def __len__(self):
        return len(self.__assignments)

    def adauga_assignment(self, assignment):
        """
        Metoda care adauga un assignment in lista de assingment-uri
        :param assignment: assignment-ul de adaugat
        """

        assignments = self.__assignments
        for assign in assignments:
            if assign == assignment:
                raise EroareRepository("Studentul are deja asignata acea problema")

        self.__assignments.append(assignment)

    def get_all_assignments(self):
        return self.__assignments

    def modifica_nota_assignment(self, assignment, nota):
        assignment.set_nota(nota)

    def sterge_assignment(self, assignment):
        if len(self.__assignments) == 0:
            raise EroareRepository("Nu exista assignment-uri")

        self.__assignments.remove(assignment)