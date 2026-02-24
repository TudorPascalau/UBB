
class Assignment:

    def __init__(self, assignment_id, student_id, lab_id, nota):
        self.__assignment_id = assignment_id
        self.__student_id = student_id
        self.__lab_id = lab_id
        self.__nota = nota

    def get_assignment_id(self):
        return self.__assignment_id

    def get_student_id(self):
        return self.__student_id

    def get_lab_id(self):
        return self.__lab_id

    def get_nota(self):
        return self.__nota

    def set_nota(self, nota):
        self.__nota = nota

    def __str__(self):
        return f"Assignment {self.__assignment_id}, asignat studentului cu id {self.__student_id}, lab id {self.__lab_id}, nota {self.__nota}"