
import datetime

class Sedinta:
    def __init__(self, s_id, data_str, ora_str, subiect, extraordinar):
        self.__s_id = s_id
        self.__data_str = data_str
        self.__ora_str = ora_str
        self.__subiect = subiect
        self.__extraordinar = extraordinar

    def get_id(self):
        """
        Functie ce returneaza id (subiect si extrordinar)
        :return: id sedinta
        """
        return self.__s_id

    def get_data_str(self):
        """
        Functie ce returneaza data unei sedinte, in format string
        :return: data unei sedinte
        """
        return self.__data_str

    def get_data(self):
        """
        Functie ce returneaza data unei sedinte, in format datetime
        :return: data unei sedinte
        """
        data = datetime.datetime.strptime(self.__data_str, "%d.%m")
        return data

    def get_ora_str(self):
        """
        Functie ce returneaza ora unei sedinte, in format string
        :return: ora unei sedinte
        """
        return self.__ora_str

    def get_ora(self):
        """
        Functie ce returneaza ora unei sedinte, in format datetime
        :return: ora unei sedinte
        """
        ora = datetime.datetime.strptime(self.__ora_str, "%H:%M")
        return ora

    def get_subiect(self):
        """
        Functie ce returneaza subiect unei sedinta
        :return: subiectul unei sedinte
        """
        return self.__subiect

    def get_extraordinar(self):
        """
        Functie care determina daca o functie e extraordinara sau nu
        :return: daca functia e extraordinara sau nu
        """
        return self.__extraordinar

    def __str__(self):
        return f"Data: {self.get_data_str()}, ora: {self.get_ora_str()}, {self.get_subiect()}, tip: {self.get_extraordinar()}"