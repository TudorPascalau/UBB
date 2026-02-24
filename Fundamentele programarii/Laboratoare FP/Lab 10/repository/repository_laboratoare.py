from domain.laborator import Laborator
from utils.eroare_repository import EroareRepository


class RepositoryLaboratoare:

    def __init__(self):
        self.__laboratoare = {}

    def __len__(self):
        return len(self.__laboratoare)

    def __contains__(self, lab_id):
        return lab_id in self.__laboratoare

    def adauga_laborator(self, laborator):
        """
        Metoda ce adauga un laborator in repository
        :param laborator: laboratorul de adaugat
        :raises EroareRepository, daca laboratorul deja existent
        """
        id_lab = (laborator.get_numar_lab(), laborator.get_numar_problema())
        if id_lab in self.__laboratoare:
            raise EroareRepository("Laborator deja existent")

        self.__laboratoare[id_lab] = laborator

    def get_all_laboratoare(self):
        """
        Metoda care returneaza toate laboratoarele
        :return: dictionar cu toate laboratoarele
        """
        return self.__laboratoare

    def sterge_laborator(self, laborator):
        """
        Metoda care sterge un laborator
        :param laborator: laboratorul de sters
        :return: laboratorul sters
        :raises EroareRepository, daca nu exista laboratorul
        """
        key = (laborator.get_numar_lab(), laborator.get_numar_problema())

        if key not in self.__laboratoare:
            raise EroareRepository("Nu exista laborator cu numar dat")

        laborator_sters = laborator
        del self.__laboratoare[key]
        return laborator_sters

    def modifica_descriere_laborator(self, laborator, descriere):
        """
        Metoda care modifica descrierea unui laborator
        :param laborator: laboratorul caruia ii modificam descrierea
        :param descriere: descrierea pe care o setam
        :raises EroareRepository, daca nu exista laboratorul
        """
        if laborator not in self.__laboratoare.values():
            raise EroareRepository("Nu exista laborator cu numar dat")
        laborator.set_descriere(descriere)

    def modifica_deadline_laborator(self, laborator, an, luna, zi):
        """
        Metoda care modifica deadline-ul unui laborator
        :param laborator: laboratorul caruia ii modificam deadline-ul
        :param an: noul an
        :param luna: noua luna
        :param zi: noua zi
        :raises EroareRepository, daca nu exista laboratorul
        """
        if laborator not in self.__laboratoare.values():
            raise EroareRepository("Nu exista laborator cu numar dat")
        laborator.set_deadline(an, luna, zi)

class RepositoryLaboratoareFile(RepositoryLaboratoare):

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
            with open(self.__filepath, "r") as file:
                linii = file.readlines()
                for linie in linii:
                    linie = linie.strip()
                    if linie != "":
                        parti = linie.split(",")
                        numar_lab = int(parti[0])
                        numar_prob = int(parti[1])
                        descriere = parti[2]
                        an = int(parti[3])
                        luna = int(parti[4])
                        zi = int(parti[5])

                        laborator = Laborator(numar_lab, numar_prob, descriere, an, luna, zi)
                        super().adauga_laborator(laborator)

        except IOError:
            raise EroareRepository("Eroare la citirea din fisier")

    def adauga_laborator(self, laborator):
        super().adauga_laborator(laborator)
        self.__store()

    def get_all_laboratoare(self):
        return super().get_all_laboratoare()

    def sterge_laborator(self, laborator):
        super().sterge_laborator(laborator)
        self.__store()

    def modifica_descriere_laborator(self, laborator, descriere):
        super().modifica_descriere_laborator(laborator, descriere)
        self.__store()

    def modifica_deadline_laborator(self, laborator, an, luna, zi):
        super().modifica_deadline_laborator(laborator, an, luna, zi)
        self.__store()


    def __store(self):
        """
        Metoda care salveaza datele in fisier
        :raises EroareRepository, daca exista probleme la scriere date in fisier
        """

        try:
            with open(self.__filepath, "w") as file:
                laboratoare = self.get_all_laboratoare()

                for laborator in laboratoare.values():
                    laborator_str = (str(laborator.get_numar_lab()) + "," + str(laborator.get_numar_problema()) + ","
                                     + laborator.get_descriere() + "," + str(laborator.get_an()) + ","
                                     + str(laborator.get_luna()) + "," + str(laborator.get_zi()))

                    file.write(laborator_str + '\n')

        except IOError:
            raise EroareRepository("Eroare la scrierea in fisier")