from domeniu.student import Student
from exceptii.eroare_repo import EroareRepo
from exceptii.eroare_validator import EroareValidator
from infrastructura.repo_studenti import RepositoryStudenti
from validare.validator_student import ValidatorStudent


class Teste:

    def ruleaza_toate_testele(self):
        print("incepem testele...")
        student = self.__ruleaza_teste_creeaza_student()
        self.__ruleaza_teste_valideaza_student(student)
        self.__ruleaza_teste_adauga_student_repo(student)

    def __ruleaza_teste_creeaza_student(self):
        print("incepem testele creeaza student...")
        id_student = 23
        nume = "Jordan"
        valoare = 9000.1
        epsilon = 0.00001
        student = Student(id_student,nume,valoare)
        assert (id_student == student.get_id_student())
        assert (abs(valoare - student.get_valoare())<epsilon)
        print("teste creeaza student finalizate cu succes...")
        return student

    def __ruleaza_teste_valideaza_student(self, student):
        validator_student = ValidatorStudent()
        validator_student.valideaza_student(student)
        assert True
        id_student_invalid = -23
        nume_invalid = ""
        valoare_invalida = 0.0
        student_invalid = Student(id_student_invalid,nume_invalid,valoare_invalida)
        try:
            validator_student.valideaza_student(student_invalid)
            assert False
        except EroareValidator as eroare_validator:
            assert str(eroare_validator) == "id invalid!\nnume invalid!\nvaloare invalida!\n"

    def __ruleaza_teste_adauga_student_repo(self, student):
        repo_studenti = RepositoryStudenti()
        assert len(repo_studenti)==0
        repo_studenti.adauga_student(student)
        assert len(repo_studenti)==1
        try:
            repo_studenti.adauga_student(student)
            assert False
        except EroareRepo as eroare_repo:
            assert str(eroare_repo) == "id student existent!\n"
