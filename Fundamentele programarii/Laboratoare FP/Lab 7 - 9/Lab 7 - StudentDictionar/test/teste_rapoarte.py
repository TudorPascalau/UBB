from repository.repo_assignment import RepositoryAssignments
from repository.repo_laboratoare import RepositoryLaboratoare
from repository.repo_studenti import RepositoryStudenti
from service.service_assignment import ServiceAssignment
from service.service_laboratoare import ServiceLaboratoare
from service.service_rapoarte import ServiceRapoarte
from service.service_studenti import ServiceStudenti
from validare.validator_assignment import ValidatorAssignment
from validare.validator_laborator import ValidatorLaborator
from validare.validator_student import ValidatorStudent


class TesteRapoarte:

    def test_all(self):
        """
        Metoda care apeleaza toate testele legate de rapoarte
        """

        print("incepem testarea rapoartelor ...")
        self.__test_get_studenti_ordonat_alfabetic()
        self.__test_get_studenti_ordonat_nota()
        print("teste finalizate cu success !!! \n")

    def __test_get_studenti_ordonat_alfabetic(self):
        """
        Metoda care testeaza get_studenti_ordonat_alfabetic
        """
        print("incepem test get studenti ordonat alfabetic")

        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        repo_assigments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assigments, validator_assignment, repo_studenti, repo_laboratoare)

        service_rapoarte = ServiceRapoarte(service_studenti, service_laboratoare, service_assignment)

        service_studenti.adauga_student(23, "Jordan", 323)
        service_studenti.adauga_student(25, "Pascalau", 323)
        service_laboratoare.adauga_laborator(9, 2, "desc", 2025, 12, 1)

        numere_laborator = {
            "numar_lab": 9,
            "numar_problema": 2,
        }
        service_assignment.adauga_assignment(23, numere_laborator)
        service_assignment.adauga_assignment(25, numere_laborator)

        studenti_si_note = service_rapoarte.get_studenti_ordonat_alfabetic(numere_laborator)

        assert studenti_si_note[0][0].get_nume() == "Jordan"
        assert studenti_si_note[0][1] is None

        print("test finalizat cu succes")

    def __test_get_studenti_ordonat_nota(self):
        """
        Metoda care testeaza get_studenti_ordonat_nota
        """
        print("incepem testul get studenti ordonat nota")

        repo_studenti = RepositoryStudenti()
        validator_student = ValidatorStudent()
        service_studenti = ServiceStudenti(repo_studenti, validator_student)

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        repo_assigments = RepositoryAssignments()
        validator_assignment = ValidatorAssignment()
        service_assignment = ServiceAssignment(repo_assigments, validator_assignment, repo_studenti, repo_laboratoare)

        service_rapoarte = ServiceRapoarte(service_studenti, service_laboratoare, service_assignment)

        service_studenti.adauga_student(23, "Jordan", 323)
        service_studenti.adauga_student(25, "Pascalau", 323)
        service_laboratoare.adauga_laborator(9, 2, "desc", 2025, 12, 1)

        numere_laborator = {
            "numar_lab": 9,
            "numar_problema": 2,
        }
        service_assignment.adauga_assignment(23, numere_laborator)
        service_assignment.adauga_assignment(25, numere_laborator)

        service_assignment.notare_assignment(23, numere_laborator, 7)
        service_assignment.notare_assignment(25, numere_laborator, 10)

        studenti_si_note = service_rapoarte.get_studenti_ordonat_nota(numere_laborator)

        assert studenti_si_note[0][0].get_nume() == "Pascalau"
        assert studenti_si_note[0][1] == 10

        print("test finalizat cu succes")