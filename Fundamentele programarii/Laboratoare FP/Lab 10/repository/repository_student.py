from domain.student import Student
from utils.eroare_repository import EroareRepository


class RepositoryStudenti:

    def __init__(self):
        self.__studenti = {}

    def __len__(self):
        return len(self.__studenti)

    def __contains__(self, student_id):
        return student_id in self.__studenti

    def __getitem__(self, student_id):
        return self.__studenti[student_id]

    def adauga_student(self, student):
        """
        Metoda ce adauga un student in repository
        :param student: studentul de adaugat
        :raises EroareRepository, daca id student deja existent
        """
        student_id = student.get_student_id()
        if student_id in self.__studenti:
            raise EroareRepository("Id student deja existent")

        self.__studenti[student_id] = student

    def get_all_studenti(self):
        """
        Metoda care returneaza toti studentii
        :return: dictionar cu toti studentii
        """
        return self.__studenti

    def sterge_student(self, student):
        """
        Metoda care sterge un student
        :param student: studentul de sters
        :return: studentul sters
        :raises EroareRepository, daca nu exista studentul
        """

        student_id = student.get_student_id()

        if student_id not in self.__studenti:
            raise EroareRepository("Nu exista student cu id dat")

        student_sters = student
        del self.__studenti[student_id]
        return student_sters

    def modifica_nume_student(self, student, nume):
        """
        Metoda care modifica numele unui student
        :param student: studentul caruia ii modificam numele
        :param nume: numele pe care il modificam
        :raises EroareRepository, daca nu exista studentul
        """
        if student not in self.__studenti.values():
            raise EroareRepository("Nu exista student cu id dat")
        student.set_nume(nume)

    def modifica_grupa_student(self, student, grupa):
        """
        Metoda care modifica grupa unui student
        :param student: studentul caruia ii modificam numele
        :param grupa: grupa pe care il modificam
        """
        if student not in self.__studenti.values():
            raise EroareRepository("Nu exista student cu id dat")
        student.set_grupa(grupa)

class RepositoryStudentiFile(RepositoryStudenti):
    def __init__(self, filepath):
        super().__init__()
        super().__len__()
        self.__filepath = filepath
        self.__load_file()

    def __load_file(self):
        """
        Metoda care incearca sa incarce datele din fisier
        :raises EroareRepository, daca exista probleme la citire date din fisier
        """

        try:
            with open(self.__filepath) as file:
                linii = file.readlines()
                for linie in linii:
                    linie = linie.strip()
                    if linie != "":
                        parti = linie.split(",")
                        student_id = int(parti[0])
                        nume = parti[1]
                        grupa = int(parti[2])

                        student = Student(student_id, nume, grupa)
                        super().adauga_student(student)

        except IOError:
            raise EroareRepository("Problema la citire din fisier")

    def adauga_student(self, student):
        super().adauga_student(student)
        self.__store()

    def sterge_student(self, student):
        student_sters = super().sterge_student(student)
        self.__store()
        return student_sters

    def get_all_studenti(self):
        return super().get_all_studenti()

    def modifica_nume_student(self, student, nume):
        super().modifica_nume_student(student, nume)
        self.__store()

    def modifica_grupa_student(self, student, grupa):
        super().modifica_grupa_student(student, grupa)
        self.__store()

    def __store(self):
        """
        Metoda care salveaza datele in fisier
        :raises EroareRepository, daca exista probleme la scriere date in fisier
        """
        try:
            with open(self.__filepath, "w") as file:
                studenti = super().get_all_studenti()

                for student in studenti.values():
                    student_str = str(student.get_student_id()) + ',' + student.get_nume() + ',' + str(student.get_grupa())
                    file.write(student_str + '\n')

        except IOError:
            raise EroareRepository("Problema la scriere in fisier")