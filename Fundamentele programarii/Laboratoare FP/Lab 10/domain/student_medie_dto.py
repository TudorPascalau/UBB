
class StudentMedieDTO:

    def __init__(self, student_id, nume, medie):
        self.__student_id = student_id
        self.__nume = nume
        self.__medie = medie

    def get_student_id(self):
        return self.__student_id

    def get_nume(self):
        return self.__nume

    def get_medie(self):
        return self.__medie

    def __str__(self):
        return f"Studentul {self.__nume}, id {self.__student_id}: media {self.__medie}"