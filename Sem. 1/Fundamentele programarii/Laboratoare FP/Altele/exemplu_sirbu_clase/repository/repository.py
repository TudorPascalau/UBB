from repository.repository_exception import RepositoryException


class Repository:
    """
    CRUD
    C - create
        - add
    R - read
        - get_all
    U - update
        - modify
    D - delete
        - remove
    """
    def __init__(self):
        self.__students = []

    def add(self, student):
        for local_student in self.__students:
            if local_student.get_id() == student.get_id():
                raise RepositoryException(f"Student with id {student.get_id()} already exists!")
        self.__students.append(student)

    def get_all(self):
        return self.__students

    def update(self, student):
        for local_student in self.__students:
            if local_student.get_id() == student.get_id():
                local_student.set_nume(student.get_nume())

    def delete(self, student_id):
        pass
