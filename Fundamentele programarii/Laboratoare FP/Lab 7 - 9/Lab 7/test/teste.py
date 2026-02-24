from domain.student import Student
from errors.eroare_repo import EroareRepository
from errors.eroare_validator import EroareValidator
from repository.repo_studenti import RepositoryStudenti
from service.service_studenti import ServiceStudenti
from validare.validator_student import ValidatorStudent


class Teste:

    def test_all(self):
        """
        Metoda care apeleaza toate testele
        """
        print("incepem testele ...")
        self.__test_creeaza_student()
        self.__test_valideaza_student()
        self.__test_adauga_student()
        self.__test_sterge_student()
        self.__test_modifica_nume_student()
        self.__test_modifica_grupa_student()
        self.__test_get_student_by_id()
        self.__test_get_studenti_grupa()
        print("teste finalizate cu succes !!! \n")

    def __test_creeaza_student(self):
        """
        Metoda care testeaza daca un student a fost creat cu succes
        """
        print("incepem testul creeaza student ...")
        studentID = 23
        nume = "Jordan"
        grupa = 323
        student = Student(studentID, nume, grupa)

        assert student.get_studentID() == studentID
        assert student.get_nume() == nume
        assert student.get_grupa() == grupa
        print("test finalizat cu succes")

    def __test_valideaza_student(self):
        """
        Metoda care testeaza daca un student este valid
        """
        student = Student(23, "Jordan", 323)

        print("incepem testul valideaza student ...")
        validator_student = ValidatorStudent()
        validator_student.valideaza_student(student)
        #assert True

        studentID_invalid = -23
        nume_invalid = ""
        grupa_invalida = 5
        student_invalid = Student(studentID_invalid, nume_invalid, grupa_invalida)
        try:
            validator_student.valideaza_student(student_invalid)
            assert False
        except EroareValidator as eroare_validator:
            assert str(eroare_validator) == "id invalid!\nnume invalid!\ngrupa invalida!\n"

        print("test finalizat cu succes")


    def __test_adauga_student(self):
        """
        Metoda care testeaza daca un student este adaugat cu succes in repository
        """
        print("incepem testul adauga student ...")

        student = Student(23, "Jordan", 323)
        repo_studenti = RepositoryStudenti()
        assert len(repo_studenti) == 0

        repo_studenti.adauga_student(student)
        assert len(repo_studenti) == 1

        try:
            repo_studenti.adauga_student(student)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "id student existent!"

        print("test finalizat cu succes")

    def __test_sterge_student(self):
        """
        Metoda care testeaza daca un student este sters din repository
        """
        print("incepem testul sterge student ...")
        student = Student(23, "Jordan", 323)
        repo_studenti = RepositoryStudenti()
        try:
            repo_studenti.sterge_student(student)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "nu exista studenti!"

        assert len(repo_studenti) == 0

        repo_studenti.adauga_student(student)
        assert len(repo_studenti) == 1

        repo_studenti.sterge_student(student)
        assert len(repo_studenti) == 0

        print("test finalizat cu succes")

    def __test_modifica_nume_student(self):
        """
        Metoda care testeaza modificarea numelui unui student
        """
        print("incepem testul modifica nume student ...")
        student = Student(23, "Jordan", 323)
        assert student.get_nume() == "Jordan"
        repo_studenti = RepositoryStudenti()
        repo_studenti.adauga_student(student)
        repo_studenti.modifica_nume_student(student, "LeBron")
        assert student.get_nume() == "LeBron"
        print("test finalizat cu succes")

    def __test_modifica_grupa_student(self):
        """
        Metoda care testeaza modificarea grupei unui student
        """
        print("incepem testul modifica grupa student ...")
        student = Student(23, "Jordan", 323)
        assert student.get_grupa() == 323
        repo_studenti = RepositoryStudenti()
        repo_studenti.adauga_student(student)
        repo_studenti.modifica_grupa_student(student, 215)
        assert student.get_grupa() == 215
        print("test finalizat cu succes")

    def __test_get_student_by_id(self):
        """
        Metoda care testeaza get student by id
        """

        print("incepem testul get student by id ...")
        student = Student(23, "Jordan", 323)
        repo_studenti = RepositoryStudenti()
        validator_studenti = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_studenti)

        try:
            service_studenti.get_student_by_id(215)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "nu exista studenti!"

        repo_studenti.adauga_student(student)

        try:
            service_studenti.get_student_by_id(215)
            assert False
        except EroareRepository as eroare_repository:
            assert str(eroare_repository) == "id student inexistent!"

        assert student == service_studenti.get_student_by_id(23)
        print("test finalizat cu succes")

    def __test_get_studenti_grupa(self):
        """
        Metoda care testeaza get studenti grupa
        """
        print("incepem testul get studenti grupa ...")
        student = Student(23, "Jordan", 323)
        repo_studenti = RepositoryStudenti()
        validator_studenti = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_studenti)

        studenti_grupa = service_studenti.get_studenti_grupa(323)
        assert len(studenti_grupa) == 0

        repo_studenti.adauga_student(student)
        studenti_grupa = service_studenti.get_studenti_grupa(323)
        assert len(studenti_grupa) == 1

        print("test finalizat cu succes")
