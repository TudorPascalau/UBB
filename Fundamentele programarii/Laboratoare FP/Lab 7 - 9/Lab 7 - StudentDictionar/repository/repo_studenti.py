from errors.eroare_repo import EroareRepository


class RepositoryStudenti:
    """
    Operatii CRUD
    """

    def __init__(self):
        """
        Repository-uri pentru stocat studenti
        """
        self.__studenti = [] #Totalitatea studentilor

    def __len__(self):
        return len(self.__studenti) #Numarului de studenti

    def adauga_student(self, student):
        """
        Metoda pentru adaugare de student in repository
        :param student: studentul de adaugat
        :raises EroareRepository, daca studentID al studentului deja exista
        """
        # Verificare daca ID-ul este deja existent
        studentID = student.get_studentID()
        for prev_student in self.__studenti:
            if studentID == prev_student.get_studentID():
                raise EroareRepository("id student existent!")

        # Adaugare studentului
        self.__studenti.append(student)

    def get_all_studenti(self):
        """
        Metoda care returneaza lista de studenti
        :return:
        """
        return self.__studenti

    def sterge_student(self, student):
        """
        Metoda care sterge un student din repository
        :param student: studentul de sters
        :raises EroareRepository, daca nu exista studenti
        """
        if len(self.__studenti) == 0:
            raise EroareRepository("nu exista studenti!")
        self.__studenti.remove(student)

    def modifica_nume_student(self, student, nume):
        """
        Metoda care modifica numele unui student din repository
        :param student: studentul caruia ii modificam numele
        :param nume: numele in care modificam
        """
        student.set_nume(nume)

    def modifica_grupa_student(self, student, grupa):
        """
        Metoda care modifica grupa unui student din repository
        :param student: studentul caruia ii modificam grupa
        :param grupa: grupa in care modificam
        """
        student.set_grupa(grupa)




