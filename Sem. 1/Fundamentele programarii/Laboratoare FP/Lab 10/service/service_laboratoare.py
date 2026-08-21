from domain.laborator import Laborator
from repository.repository_laboratoare import RepositoryLaboratoare
from utils.eroare_repository import EroareRepository


class ServiceLaboratoare:

    def __init__(self, repo_laboratoare):
        self.__repo_laboratoare = repo_laboratoare

    def adauga_laborator(self, numar_lab, numar_problema, descriere, an, luna, zi):
        """
        Metoda care adauga un laborator
        :param numar_lab: numarul laboratorului
        :param numar_problema: numarul problemei
        :param descriere: descriere laborator
        :param an: anul deadline-ului
        :param luna: luna deadline-ului
        :param zi: ziua deadline-ului
        """
        laborator = Laborator(numar_lab, numar_problema, descriere, an, luna, zi)
        self.__repo_laboratoare.adauga_laborator(laborator)

    def get_laboratoare(self):
        """
        Metoda care returneaza toate laboratoarele
        :return: dictionar laboratoare
        """
        return self.__repo_laboratoare.get_all_laboratoare()

    def get_laborator_from_numar(self, numar_lab, numar_problema):
        """
        Metoda care returneaza laboratorul cu perechea (numar_lab, numar_problema) data
        :param numar_lab: numarul laboratorului
        :param numar_problema: numarul problemei
        :return: laborator cu perechea data
        :raises EroareRepository, daca nu exista laboratorul
        """
        laboratoare = self.get_laboratoare()
        for laborator in laboratoare.values():
            if (laborator.get_numar_lab() == numar_lab and
                    laborator.get_numar_problema() == numar_problema):
                return laborator

        raise EroareRepository("Nu exista laborator cu numere date")

    def sterge_laborator(self, numar_lab, numar_problema):
        """
        Metoda care sterge un laborator
        :param numar_lab: numarul laboratorului
        :param numar_problema: numarul problemei
        :return: laboratorul sters
        """
        laborator = self.get_laborator_from_numar(numar_lab, numar_problema)
        return self.__repo_laboratoare.sterge_laborator(laborator)

    def modifica_descriere_laborator(self, numar_lab, numar_problema, descriere):
        """
        Metoda care modifica descrierea unui laborator
        :param numar_lab: numarul laboratorului
        :param numar_problema: numarul problemei
        :param descriere: noua descriere
        :raises EroareRepository, daca nu exista laboratorul
        """
        laborator = self.get_laborator_from_numar(numar_lab, numar_problema)
        self.__repo_laboratoare.modifica_descriere_laborator(laborator, descriere)

    def modifica_deadline_laborator(self, numar_lab, numar_problema, an, luna, zi):
        """
        Metoda care modifica deadline-ul unui laborator
        :param numar_lab: numarul laboratorului
        :param numar_problema: numarul problemei
        :param an: noul an
        :param luna: noua luna
        :param zi: noua zi
        :raises EroareRepository, daca nu exista laboratorul
        """
        laborator = self.get_laborator_from_numar(numar_lab, numar_problema)
        self.__repo_laboratoare.modifica_deadline_laborator(laborator, an, luna, zi)

