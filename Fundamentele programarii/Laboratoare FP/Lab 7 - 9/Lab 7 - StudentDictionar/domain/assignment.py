
class Assignment:

    """
    Clasa de legatura intre studenti si laboratoare
    """

    def __init__(self, nota, studentID, numere_laborator):
        self.__nota = nota
        self.__studentID = studentID
        self.__numere_laborator = numere_laborator

    def get_nota_assign(self):
        return self.__nota

    def get_studentID_assign(self):
        return self.__studentID

    def get_numere_laborator_assign(self):
        return self.__numere_laborator

    def set_nota_assign(self, nota):
        self.__nota = nota

    def set_studentID_assign(self, studentID):
        self.__studentID = studentID

    def set_numere_laborator_assign(self, numere_laborator):
        self.__numere_laborator = numere_laborator