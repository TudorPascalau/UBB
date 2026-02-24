from domain.sedinta import Sedinta
from domain.validator_sedinta import EroareValidator
from ui.ui import EroareUI


class ServiceSedinte:

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator
        self.__filtru = False

    def adauga_sedinta(self, data_str, ora_str, subiect, extraordinar):
        """
        Functie pentru adaugarea unei sedinte
        :param data_str: data sedintei, in format string
        :param ora_str: ora sedintei, in format string
        :param subiect: subiect sedintei, in format string
        :param extraordinar: daca sedinta este normala sau extraordinara
        :raises: EroareValidator, daca datele nu sunt valide
        """
        try:
            self.__validator.valideaza_date_sedinta(data_str, ora_str, extraordinar)

        except EroareValidator as eroare:
            raise EroareValidator(eroare)

        if self.__validator.valideaza_date_sedinta(data_str, ora_str, extraordinar) == True:
            s_id = (subiect, extraordinar)
            sedinta = Sedinta(s_id, data_str, ora_str, subiect, extraordinar)
            self.__repo.adauga_repo(sedinta)

    def get_lista_sedinte(self):
        """
        Functie care returneaza valorile sedintelor sub forma de lista
        :return: lista cu valorile sedintelor
        """
        sedinte = self.__repo.get_all_repo()
        sedinta_lista = list(sedinte.values())

        return sedinta_lista

    def sorteaza_sedinte_dupa_ora(self, sedinte):
        """
        Functie care sorteaza o lista de sedinte dupa ora
        """

        sedinte.sort(key=lambda sedinta: sedinta.get_ora())

    def get_sedinte_zi(self, zi):
        """
        Functie care returneaza o lista cu toate sedintele care au loc intr-o anumita zi
        :param zi: ziua anume
        :return: lista cu valorile sedintelor care au data o anumita zi
        """
        sedinte_zi = []
        sedinta_lista = self.get_lista_sedinte()
        for sedinta in sedinta_lista:
            if sedinta.get_data().day == zi.day and sedinta.get_data().month == zi.month:
                sedinte_zi.append(sedinta)

        return sedinte_zi

    def get_sedinte_zi_ora(self, zi):
        """
        Functie care returneaza o lista cu toate sedintele care au data intr-o anumita zi, ordonate dupa ora
        :param zi: ziua respectiva
        :return: lista ordonata
        """
        sedinte_zi = self.get_sedinte_zi(zi)
        sedinte_zi.sort(key=lambda sedinta: sedinta.get_ora())

        return sedinte_zi

    def seteaza_filtru(self, filtru):
        """
        Functie care seteaza filtrul de data
        :param filtru: filtrul pe care il setam
        """
        self.__filtru = filtru

    def get_filtru(self):
        """
        Functie care returneaza filtrul de data actual
        :return: filtrul de data
        """
        return self.__filtru

    def get_sedinte_export(self, key):
        """
        Functie care returneaza o lista ordonata care contine in subiect un sir de caractere
        :param key: sirul de caractere
        :return: lista ordonata
        """
        sedinte_export = []
        sedinta_lista = self.get_lista_sedinte()
        for sedinta in sedinta_lista:
            if key in sedinta.get_subiect():
                sedinte_export.append(sedinta)

        sedinte_export.sort(key=lambda sedinta: (sedinta.get_data(), sedinta.get_ora()))
        return sedinte_export

    def export(self, filename, key):
        """
        Functie care realizeaza exportul in fisierul cu numele filename si care contin sirul de caractere
        :param filename: numele fisierului
        :param key: sirul de caractere
        """

        filename = filename + ".txt"

        sedinte_export = self.get_sedinte_export(key)
        try:
            with open(filename, "w") as file:
                for sedinta in sedinte_export:
                    sedinta_line = f"{sedinta.get_data_str()},{sedinta.get_ora_str()},{sedinta.get_subiect()},{sedinta.get_extraordinar()}\n"
                    file.write(sedinta_line)

        except IOError:
            raise EroareUI("Eroare la scrierea in fisier")

