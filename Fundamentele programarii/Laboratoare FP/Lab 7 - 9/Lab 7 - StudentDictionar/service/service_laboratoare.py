from domain.laborator import Laborator
from errors.eroare_repo import EroareRepository


class ServiceLaboratoare:

    def __init__(self, repo_laboratoare, validator_laborator):
        self.__repo_laboratoare = repo_laboratoare
        self.__validator_laborator = validator_laborator

    def adauga_laborator(self, numar_lab, numar_prob, descriere, an, luna, zi):
        """
        Metoda care adauga un laborator
        :param numar_lab: numarul laboratorului
        :param numar_prob: numarul problemei
        :param descriere: descrierea laboratorului
        :param an: anul deadlineului
        :param luna: luna deadlineului
        :param zi: ziua deadlineului
        """
        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laboratoare.adauga_laborator(laborator)

    def access_laboratoare(self):
        """
        Metoda care accesseaza toate laboratoarele
        :return: toate laboratoarele din repository
        """
        return self.__repo_laboratoare.get_all_laboratoare()

    def get_lab_by_numere(self, numar_lab, numar_prob):
        """
        Metoda care cauta un laborator dupa numerele sale
        :param numar_lab: numar laborator
        :param numar_prob: numar problema
        :return: laboratorul asociat, daca exista
        :raises: EroareRepository, daca nu exista
        """
        laboratoare = self.__repo_laboratoare.get_all_laboratoare()
        if len(laboratoare) == 0:
            raise EroareRepository("Nu exista laboratoare!")

        for laborator in laboratoare:
            if laborator.get_numar_laborator() == numar_lab and laborator.get_numar_problema() == numar_prob:
                return laborator

        raise EroareRepository("Nu exista laborator cu numarul dat!")

    def sterge_laborator(self, numar_lab, numar_prob):
        """
        Metoda care sterge un laborator
        :param numar_lab: Numarul laboratorului
        :param numar_prob: Numarul problemei
        """
        laborator = self.get_lab_by_numere(numar_lab, numar_prob)
        self.__repo_laboratoare.sterge_laborator(laborator)

    def modifica_descriere_laborator(self, numar_lab, numar_prob, descriere):
        """
        Metoda care modifica descrierea unui laborator
        :param numar_lab: Numarul laboratorului
        :param numar_prob: Numarul problemei
        :param descriere: Descrierea in care modificam
        """
        laborator = self.get_lab_by_numere(numar_lab, numar_prob)
        self.__repo_laboratoare.modifica_descriere_laborator(laborator, descriere)
        self.__validator_laborator.valideaza_laborator(laborator)

    def modifica_deadline_laborator(self, numar_lab, numar_prob, an, luna, zi):
        """
        Metoda care modifica deadline laborator
        :param numar_lab: Numarul laboratorului
        :param numar_prob: Numarul problemei
        :param an: Anul deadlineului
        :param luna: Luna deadlineului
        :param zi: Ziua deadlineului
        """
        deadline = {"an": an, "luna": luna, "zi": zi}
        laborator = self.get_lab_by_numere(numar_lab, numar_prob)
        self.__repo_laboratoare.modifica_deadline_laborator(laborator, deadline)
        self.__validator_laborator.valideaza_laborator(laborator)