
class Dovada:

    def __init__(self, id_dovada, descriere, data, tip, suspect):
        self.__id_dovada = id_dovada
        self.__descriere = descriere
        self.__data = data
        self.__tip = tip
        self.__suspect = suspect

    def get_id_dovada(self):
        """
        Getter pentru id_dovada
        """
        return self.__id_dovada

    def get_descriere(self):
        """
        Getter pentru descrire
        """
        return self.__descriere

    def get_data(self):
        """
        Getter pentru data
        """
        return self.__data

    def get_tip(self):
        """
        Getter pentru tip
        """
        return self.__tip

    def get_suspect(self):
        """
        Getter pentru suspect
        """
        return self.__suspect

    def __str__(self):
        return f"Dovada {self.__id_dovada}, {self.__descriere}, data: {self.__data}, tip: {self.__tip}, suspect: {self.__suspect}"