from domain.student import Student
from domain.validator.student_validator import StudentValidator


class Service:
    def __init__(self, repository):
        self.__repository = repository

    def add(self, id, nume):
        student = Student(id, nume)
        StudentValidator(student).validate()
        self.__repository.add(student)
