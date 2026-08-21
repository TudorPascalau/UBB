class Laborator:

    def __init__(self, numar_lab, numar_problema, descriere, an, luna, zi):
        self.__numar_lab = numar_lab
        self.__numar_problema = numar_problema
        self.__descriere = descriere
        self.__an = an
        self.__luna = luna
        self.__zi = zi

    def get_numar_lab(self):
        """
        Getter pentru numarul laboratorului
        """
        return self.__numar_lab

    def get_numar_problema(self):
        """
        Getter pentru numarul problemei
        """
        return self.__numar_problema

    def get_descriere(self):
        """
        Getter pentru descriere laborator
        """
        return self.__descriere

    def get_an(self):
        """
        Getter pentru anul deadline-ului
        """
        return self.__an

    def get_luna(self):
        """
        Getter pentru luna deadline-ului
        """
        return self.__luna

    def get_zi(self):
        """
        Getter pentru ziua deadline-ului
        """
        return self.__zi

    def set_descriere(self, descriere):
        """
        Setter pentru descriere laborator
        """
        self.__descriere = descriere

    def set_deadline(self, an, luna, zi):
        """
        Setter pentru deadline laborator
        :param an: anul noului deadline
        :param luna: luna noului deadline
        :param zi: ziua noului deadline
        """
        self.__an = an
        self.__luna = luna
        self.__zi = zi

    def __str__(self):
        return (f"Laboratorul {self.get_numar_lab()}.{self.get_numar_problema()}, "
                f"Descriere: {self.get_descriere()}, "
                f"Deadline: {self.get_zi()}-{self.get_luna()}-{self.get_an()}")
