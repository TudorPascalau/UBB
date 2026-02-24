from domain.laborator import Laborator
from errors.eroare_repo import EroareRepository
from errors.eroare_validator import EroareValidator
from repository.repo_laboratoare import RepositoryLaboratoare
from service.service_laboratoare import ServiceLaboratoare
from validare.validator_laborator import ValidatorLaborator


class TesteLaborator:

    def test_all(self):
        """
        Metoda care apeleaza toate testele ce tin de laboratoare
        """
        print("incepem testarea laboratoarelor ...")
        self.__test_creaza_laborator()
        self.__test_valideaza_laborator()
        self.__test_adauga_laborator()
        self.__test_get_lab_by_numere()
        self.__test_sterge_laborator()
        self.__test_modifica_descriere_laborator()
        print("teste finalizate cu succes !!! \n")

    def __test_creaza_laborator(self):
        print("incepem testul creaza laborator ...")
        numar_lab = 7
        numar_prob = 2
        descriere = "Aplicatie studenti si note"
        an = 2025
        luna = 11
        zi = 17
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        assert laborator.get_numar_laborator() == numar_lab
        assert laborator.get_numar_problema() == numar_prob
        assert laborator.get_descriere_laborator() == descriere
        assert laborator.get_an_deadline() == an
        assert laborator.get_luna_deadline() == luna
        assert laborator.get_zi_deadline() == zi
        print("test finalizat cu succes")

    def __test_valideaza_laborator(self):

        laborator = Laborator(7,2,"Aplicatie studenti si note",2025,11,17)
        print("incepem testul valideaza laborator ...")

        validator_laborator = ValidatorLaborator()
        validator_laborator.valideaza_laborator(laborator)

        numar_lab = 0
        numar_prob = -1
        descriere = ""
        an = 0
        luna = 14
        zi = -15

        laborator_invalid = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)

        try:
            validator_laborator.valideaza_laborator(laborator_invalid)
            assert False
        except EroareValidator as eroare_validator:
            assert str(eroare_validator) == "numar laborator invalid!\nnumar problema invalida!\ndescriere invalida!\nan deadline invalid!\nluna deadline invalida!\nzi deadline invalida!\n"

        print("test finalizat cu succes")

    def __test_adauga_laborator(self):

        laborator = Laborator(7, 2, "Aplicatie studenti si note", 2025, 11, 17)
        print("incepem testul adauga laborator ...")

        repo_laboratoare = RepositoryLaboratoare()
        assert len(repo_laboratoare) == 0

        repo_laboratoare.adauga_laborator(laborator)
        assert len(repo_laboratoare) == 1

        try:
            repo_laboratoare.adauga_laborator(laborator)
            assert False
        except EroareRepository as eroare_repo:
            assert str(eroare_repo) == "numere problema deja existente!"

        print("test finalizat cu succes")

    def __test_get_lab_by_numere(self):

        laborator = Laborator(7, 2, "Aplicatie studenti si note", 2025, 11, 17)
        print("incepem testul get lab by numere ...")

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        try:
            service_laboratoare.get_lab_by_numere(7,2)
            assert False

        except EroareRepository as eroare_repo:
            assert str(eroare_repo) == "Nu exista laboratoare!"

        repo_laboratoare.adauga_laborator(laborator)
        assert laborator == service_laboratoare.get_lab_by_numere(7,2)

        try:
            service_laboratoare.get_lab_by_numere(7,3)
            assert False

        except EroareRepository as eroare_repo:
            assert str(eroare_repo) == "Nu exista laborator cu numarul dat!"

        print("test finalizat cu succes")

    def __test_sterge_laborator(self):

        laborator = Laborator(7, 2, "Aplicatie studenti si note", 2025, 11, 17)
        print("incepem testul sterge laborator ...")

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        assert len(repo_laboratoare) == 0

        try:
            service_laboratoare.sterge_laborator(7,2)
            assert False
        except EroareRepository as eroare_repo:
            assert str(eroare_repo) == "Nu exista laboratoare!"


        repo_laboratoare.adauga_laborator(laborator)
        assert len(repo_laboratoare) == 1

        try:
            service_laboratoare.sterge_laborator(7,3)
            assert False
        except EroareRepository as eroare_repo:
            assert str(eroare_repo) == "Nu exista laborator cu numarul dat!"

        service_laboratoare.sterge_laborator(7,2)
        assert len(repo_laboratoare) == 0

        print("test finalizat cu succes")

    def __test_modifica_descriere_laborator(self):
        laborator = Laborator(7, 2, "Aplicatie studenti si note", 2025, 11, 17)
        print("incepem testul modifica descriere laborator ...")

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        repo_laboratoare.adauga_laborator(laborator)

        try:
            service_laboratoare.modifica_descriere_laborator(7,2, "")
            assert False
        except EroareValidator as eroare_validator:
            assert str(eroare_validator) == "descriere invalida!\n"

        service_laboratoare.modifica_descriere_laborator(7,2, "Descriere laborator")
        assert laborator.get_descriere_laborator() == "Descriere laborator"

        print("test finalizat cu succes")

    def __test_modifica_deadline_laborator(self):
        laborator = Laborator(7, 2, "Aplicatie studenti si note", 2025, 11, 17)
        print("incepem testul modifica deadline laborator ...")

        repo_laboratoare = RepositoryLaboratoare()
        validator_laborator = ValidatorLaborator()
        service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)

        repo_laboratoare.adauga_laborator(laborator)

        try:
            service_laboratoare.modifica_deadline_laborator(7,2, 2000, 13, 40)
            assert False
        except EroareValidator as eroare_validator:
            assert str("eroare_validator") == "an deadline invalid!\nluna deadline invalida!\nzi deadline invalida!\n"

        service_laboratoare.modifica_deadline_laborator(7,2, 2025, 12, 1)
        assert laborator.get_an_deadline() == 2025
        assert laborator.get_luna_deadline() == 12
        assert laborator.get_zi_deadline() == 1

        print("test finalizat cu succes")