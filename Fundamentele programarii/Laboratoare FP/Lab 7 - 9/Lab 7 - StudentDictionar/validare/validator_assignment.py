from errors.eroare_validator import EroareValidator


class ValidatorAssignment:

    def valideaza_assignment(self, assignment):
        """
        Metoda care valideaza clasa de legatura assignment
        :param: assignment, assignmentul de validat
        :return: - daca assignmentul este valid
        :raises: EroareValidator, daca nu
        """

        erori = ""
        if assignment.get_studentID_assign() < 0:
            erori += "id invalid"
        if assignment.get_numere_laborator_assign()["numar_lab"] < 0:
            erori += "numar lab invalid"
        if assignment.get_numere_laborator_assign()["numar_problema"] < 0:
            erori += "numar problema invalid"
        if not (assignment.get_nota_assign() is None or 1 <= assignment.get_nota_assign() <= 10):
            erori += "numar problema invalid"

        if len(erori) != 0:
            raise EroareValidator(erori)