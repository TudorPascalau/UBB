import datetime

from domain.sedinta import Sedinta


class EroareRepository(Exception):
    """
    Clasa de erori ce tin de repository
    """
    pass

class RepositorySedinte:

    def __init__(self, file_path):
        self.__file_path = file_path
        self.__repo = {}
        self.__read_from_file()

    def __len__(self):
        return len(self.__repo)

    def __read_from_file(self):
        """
        Functie ce faciliteaza citirea in fisier
        """
        try:
            with open(self.__file_path, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    parti = line.split(",")
                    data_str = parti[0]
                    data = datetime.datetime.strptime(data_str, "%d.%m")
                    ora_str = parti[1]
                    ora = datetime.datetime.strptime(ora_str, "%H:%M")
                    subiect = parti[2]
                    extraordinar = parti[3]

                    s_id = (subiect, extraordinar)

                    sedinta = Sedinta(s_id, data_str, ora_str, subiect, extraordinar)
                    self.adauga_repo(sedinta)


        except IOError:
            raise EroareRepository("Eroare la citirea din fisier")

    def __write_to_file(self):
        """
        Functie ce faciliteaza scrirea in fisier
        """
        try:
            with open(self.__file_path, "w") as file:
                for sedinta in self.__repo.values():
                    sedinta_line = f"{sedinta.get_data_str()},{sedinta.get_ora_str()},{sedinta.get_subiect()},{sedinta.get_extraordinar()}\n"
                    file.write(sedinta_line)

        except IOError:
            raise EroareRepository("Eroare la scrierea in fisier")

    def adauga_repo(self, sedinta):
        """
        Functie ce adauga o sedinta in repository
        :param sedinta: sedinta de adaugat
        :raises: EroareRepository, daca exista deja o sedinta cu acelasi subiect si tip de extraordinar
        """
        s_id = sedinta.get_id()
        if s_id in self.__repo:
            raise EroareRepository(f"Sedinta cu acelasi subiect si extraordinaritate deja existent")

        self.__repo[s_id] = sedinta
        self.__write_to_file()

    def get_all_repo(self):
        """
        Functie care returneaza repo = dictionar de sedinte
        :return: repository
        """
        return self.__repo

    def clear_repo(self):
        """
        Functie care goleste repository - folosita in testa
        """
        self.__repo = {}
        self.__write_to_file()