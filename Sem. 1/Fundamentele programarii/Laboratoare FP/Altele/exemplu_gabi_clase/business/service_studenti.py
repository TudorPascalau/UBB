from domeniu.student import Student


class ServiceStudenti:
    def __init__(self,repo_studenti,validator_student):
        self.__repo_studenti = repo_studenti
        self.__validator_student = validator_student

    def adauga_student(self,id_student,nume,valoare):
        student = Student(id_student,nume,valoare)
        self.__validator_student.valideaza_student(student)
        self.__repo_studenti.adauga_student(student)
