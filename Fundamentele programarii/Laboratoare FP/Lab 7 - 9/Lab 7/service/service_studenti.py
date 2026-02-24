from domain.student import Student
from errors.eroare_repo import EroareRepository


class ServiceStudenti:
    def __init__(self, repo_studenti, validator_student):
        self.__repo_studenti = repo_studenti
        self.__validator_student = validator_student

    def adauga_student(self, studentID, nume, grupa):
        """
        Metoda pentru adaugarea unui student
        :param studentID: int > 0
        :param nume: str != ""
        :param grupa: int , 100 <= grupa <= 999
        :return:
        """
        student = Student(studentID, nume, grupa) # Creare student cu parametrii dati
        self.__validator_student.valideaza_student(student) # Validare student
        self.__repo_studenti.adauga_student(student) #Adaugare in repository

    def access_studenti(self):
        """
        Metoda pentru a accessa toti studentii
        :return: lista de studenti
        """
        return self.__repo_studenti.get_all_studenti()

    def sterge_student(self, studentID):
        """
        Metoda pentru a sterge un student
        :param studentID: id student pe care il stergem
        """
        student = self.__repo_studenti.get_student_by_id(studentID)
        self.__repo_studenti.sterge_student(student)

    def modifica_nume_student(self, studentID, nume):
        """
        Metoda pentru a modifica numele unui student
        :param studentID: id-ul studentului caruia ii modificam numele
        :param nume: numele in care modificam
        """
        student = self.__repo_studenti.get_student_by_id(studentID)
        self.__repo_studenti.modifica_nume_student(student, nume)

    def modifica_grupa_student(self, studentID, grupa):
        """
        Metoda pentru a modifica grupa unui student
        :param studentID: id-ul studentului caruia ii modificam grupa
        :param grupa: grupa in care modificam
        """
        student = self.__repo_studenti.get_student_by_id(studentID)
        self.__repo_studenti.modifica_grupa_student(student, grupa)

    def cauta_studenti_grupa(self, grupa):
        """
        Metoda pentru a cauta studenti unei grupe
        :param grupa: Grupa din care fac parte studentii
        """
        return self.__repo_studenti.get_studenti_grupa(grupa)

    def get_student_by_id(self, studentID):
        """
        Metoda care returneaza un student bazat pe studentID-ul sau
        :param studentID: studentID-ul dupa care cautam
        :return: studentul cu studentID
        :raises EroareRepository, daca nu exista studenti
                EroareRepository, daca nu exista student asociat studentID
        """
        # Verificare existenta studenti
        studenti = self.__repo_studenti.get_all_studenti()
        if len(studenti) == 0:
            raise EroareRepository("nu exista studenti!")

        # Gasirea studentului
        for student in studenti:
            if studentID == student.get_studentID():
                return student

        # Daca nu exista studentID asociat
        raise EroareRepository("id student inexistent!")

    def get_studenti_grupa(self, grupa):
        """
        Metoda care returneaza toti studentii ce apartin unei anumite grupe
        :param grupa: Grupa de care apartin studentii
        :return: Lista de studenti din grupa respectiva
        """
        # Cautarea studentilor din grupa respectiva
        studenti = self.__repo_studenti.get_all_studenti()
        studenti_grupa = []
        for student in studenti:
            if student.get_grupa() == grupa:
                studenti_grupa.append(student)

        # Returnare grupa
        return studenti_grupa
