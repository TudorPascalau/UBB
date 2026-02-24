
from domain.automobil import Automobil

class EroareRepository(Exception):
    pass

class RepositoryAutomobile:
    def __init__(self, file_path):
        self.__file_path = file_path
        self.__automobile = {}
        self.__read_from_file()

    def __len__(self):
        return len(self.__automobile)

    def __read_from_file(self):
        try:
            with open(self.__file_path, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    parti = line.split(',')
                    a_id = int(parti[0])
                    marca = parti[1]
                    pret = int(parti[2])
                    model = parti[3]
                    data_revizie_str = parti[4]

                    automobil = Automobil(a_id, marca, pret, model, data_revizie_str)
                    self.adauga(automobil)

        except IOError:
            raise EroareRepository("Eroare la citirea din fisier")

    def __write_to_file(self):
        try:
            with open(self.__file_path, "w") as file:
                for automobil in self.__automobile.values():
                    automobil_line = f"{automobil.get_id()},{automobil.get_marca()},{automobil.get_pret()},{automobil.get_model()},{automobil.get_data_revizie_str()}\n"
                    file.write(automobil_line)

        except IOError:
            raise EroareRepository("Eroare la scrierea in fisier")


    def adauga(self, automobil):
        a_id = automobil.get_id()
        if a_id in self.__automobile:
            raise EroareRepository(f"Automobil cu id {a_id} deja existent")

        self.__automobile[a_id] = automobil
        self.__write_to_file()

    def clear(self):
        self.__automobile = {}
        self.__write_to_file()

    def get_all(self):
        return self.__automobile
