from domain.student import Student
from utils.eroare_repository import EroareRepository


class ServiceStudenti:

    def __init__(self, repo_stundeti):
        self.__repo_studenti = repo_stundeti

    def adauga_student(self, student_id, nume, grupa):
        """
        Metoda care adauga un student
        :param student_id: id student
        :param nume: nume student
        :param grupa: grupa student
        """
        student = Student(student_id, nume, grupa)
        self.__repo_studenti.adauga_student(student)

    def get_studenti(self):
        """
        Metoda care returneaza toti studentii
        :return: dictionar studenti
        """
        return self.__repo_studenti.get_all_studenti()

    def get_student_from_id(self, student_id):
        """
        Metoda care returneaz studentul cu id dat
        :param student_id: id student
        :return: student cu id, daca exista
        :raises EroareRepository, daca nu
        """

        studenti = self.get_studenti()
        for student in studenti.values():
            if student.get_student_id() == student_id:
                return student

        raise EroareRepository("Nu exista student cu id dat")

    def get_student_from_id_rec(self, student_id):
        """
        Varianta recurisva a metodei get_student_from_id
        :param student_id: id student
        :return: student cu id, daca exista
        :raises EroareRepository, daca nu
        """

        studenti = list(self.get_studenti().values())
        return self.__get_student_from_id_rec_aux(student_id, studenti, 0)

    def __get_student_from_id_rec_aux(self, student_id, studenti, index):
        """
        Varianta recursiva a metodei get_student_from_id - functie auxiliara
        :param student_id: id student
        :param studenti: lista studentilor
        :param index: al catelea student
        :return: studentul cu id dat, daca exista
        :raises EroareRepository: daca nu

        De apelat initial cu student_id, lista studenti din get_studenti.values(), index = 0
        T(n) = T(n-1) + 1 => O(n)
        """

        if index == len(studenti):
            raise EroareRepository("Nu exista student cu id dat")

        if studenti[index].get_student_id() == student_id:
            return studenti[index]

        return self.__get_student_from_id_rec_aux(student_id, studenti, index + 1)

    def sterge_student(self, student_id):
        """
        Metoda care sterge un student
        :param student_id: studentul de sters
        :return: studentul sters
        """
        student = self.get_student_from_id(student_id)
        return self.__repo_studenti.sterge_student(student)

    def modifica_nume_student(self, student_id, nume):
        """
        Metoda care modifica numele unui student
        :param student_id: id_ul studentului caruia ii modificam numele
        :param nume: numele pe care il modificam
        :raises EroareRepository, daca nu exista studentul
        """
        student = self.get_student_from_id(student_id)
        self.__repo_studenti.modifica_nume_student(student,nume)

    def modifica_grupa_student(self, student_id, grupa):
        """
        Metoda care modifica grupa unui student
        :param student_id: id_ul studentului caruia ii modificam numele
        :param grupa: grupa pe care il modificam
        """
        student = self.get_student_from_id(student_id)
        self.__repo_studenti.modifica_grupa_student(student, grupa)

    def gaseste_studenti_grupa(self, grupa):
        """
        Metoda care returneaza o lista cu toti studentii unei grupe
        :param grupa: grupa caruia ii apartin studentii
        :return: lista cu studentii grupei
        """
        studenti_grupa = []

        studenti = self.get_studenti()
        for student in studenti.values():
            if student.get_grupa() == grupa:
                studenti_grupa.append(student)

        return studenti_grupa

    def gaseste_studenti_grupa_rec(self, grupa):
        """
        Varianta recursiva a metodei gaseste_studenti_grupa
        :param grupa: grupa cautata
        :return: lista cu studentii care apartin grupei
        """

        studenti = list(self.get_studenti().values())
        return self.__gaseste_studenti_grupa_rec_aux(studenti, grupa, 0, [])

    def __gaseste_studenti_grupa_rec_aux(self, studenti, grupa, index, rezultat):
        """
        Varianta recursiva a metodei gaseste_studenti_grupa - functie auxiliara
        :param studenti: lista de studenti
        :param grupa: grupa in care s-ar afla
        :param index: index student curent
        :param rezultat: lista cu stundetii apartinand grupei date
        :return: rezultat
        """
        if index == len(studenti):
            return rezultat

        if studenti[index].get_grupa() == grupa:
            rezultat.append(studenti[index])

        return self.__gaseste_studenti_grupa_rec_aux(studenti, grupa, index+1, rezultat)