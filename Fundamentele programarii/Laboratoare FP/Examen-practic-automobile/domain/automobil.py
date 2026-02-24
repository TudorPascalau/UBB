
from datetime import datetime

class Automobil:
    def __init__(self, a_id, marca, pret, model, data_revizie_str):
        self.__id = a_id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data_revizie_str = data_revizie_str
        self.__data_revizie = datetime.strptime(data_revizie_str, "%d:%m:%Y")

    def get_id(self):
        return self.__id

    def get_marca(self):
        return self.__marca

    def get_pret(self):
        return self.__pret

    def get_model(self):
        return self.__model

    def get_data_revizie_str(self):
        return self.__data_revizie_str

    def get_data_revizie(self):
        return self.__data_revizie

    def __str__(self):
        return (f"Id: {self.get_id()}, marca: {self.get_marca()}, pret: {self.get_pret()}, "
                f"model: {self.get_model()}, data revizie: {self.get_data_revizie_str()}")