class Student:
    def __init__(self,id_student,nume,valoare):
        '''
        functie care creeaza un student
        :param id_student: int
        :param nume: string
        :param valoare: float
        '''
        self.__id_student = id_student
        self.__nume = nume
        self.__valoare = valoare

    def get_id_student(self):
        return self.__id_student

    def get_nume(self):
        return self.__nume

    def get_valoare(self):
        return self.__valoare

    def set_nume(self,nume):
        self.__nume = nume

    def set_valoare(self,valoare):
        self.__valoare = valoare
