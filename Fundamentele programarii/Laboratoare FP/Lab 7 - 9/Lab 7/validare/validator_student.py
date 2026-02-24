from errors.eroare_validator import EroareValidator


class ValidatorStudent:

    def valideaza_student(self,student):
        """
        Metoda care valideaza studentul
        :param student:
        :return: - , daca studentul este valid
        :raises: EroareValidator cu mesajul:
                id invalid!\n, daca idul <0
                nume invalid!\n, daca numele este vid
                grupa invalida!\n, daca nu 100 <= valoare <= 999
        """

        erori = ""
        if student.get_studentID() < 0:
            erori += "id invalid!\n"
        if student.get_nume() == "":
            erori += "nume invalid!\n"
        if not 100 <= student.get_grupa() <= 999:
            erori += "grupa invalida!\n"

        #Aruncarea erorilor de validare in caz ca exista
        if len(erori) > 0:
            raise EroareValidator(erori)