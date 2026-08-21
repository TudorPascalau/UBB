from domain.dovada import Dovada
from utils.eroare_repo import EroareRepository


class RepositoryDovezi:

    def __init__(self):
        self.__repository = {}

    def __len__(self):
        return len(self.__repository)

    def adauga_dovada(self, dovada):

        id_dovada = dovada.get_id_dovada()
        if id_dovada in self.__repository:
            raise EroareRepository("Id dovada deja existent")

        self.__repository[id_dovada] = dovada

    def get_all_dovezi(self):
        return self.__repository

class RepositoryDoveziFile(RepositoryDovezi):

    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_file()

    def __load_file(self):

        try:
            with open(self.__filename, "r") as file:
                linii = file.readlines()
                for linie in linii:
                    linie = linie.strip()
                    if linie != "":
                        parti = linie.split(",")
                        id_dovada = int(parti[0])
                        descriere = parti[1]
                        data = parti[2]
                        tip = parti[3]
                        suspect = parti[4]

                        dovada = Dovada(id_dovada, descriere, data, tip, suspect)
                        super().adauga_dovada(dovada)

        except IOError:
            raise EroareRepository("Eroare la citire din fisier")

    def __store(self):

        try:
            with open(self.__filename, "w") as file:
                dovezi = super().get_all_dovezi()
                for dovada in dovezi.values():
                    dovada_str = (str(dovada.get_id_dovada()) + ',' + dovada.get_descriere() + ','
                                    + dovada.get_data() + ',' + dovada.get_tip() + ',' + dovada.get_suspect() + '\n')

                    file.write(dovada_str +'\n')

        except IOError:
            raise EroareRepository("Eroare la scriere in fisier")

    def adauga_dovada(self, dovada):
        super().adauga_dovada(dovada)
        self.__store()

    def get_all_dovezi(self):
        return super().get_all_dovezi()