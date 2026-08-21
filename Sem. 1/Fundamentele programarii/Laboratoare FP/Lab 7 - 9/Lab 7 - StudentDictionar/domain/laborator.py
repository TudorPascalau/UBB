
class Laborator:
    def __init__(self, numar_lab, numar_prob, descriere, an, luna, zi):
        """
        Definitia unui laborator
        :param numar_lab: int
        :param numar_prob: int
        :param descriere: str
        :param an, luna, zi: int
        """

        self.__numere = {
            "numar_lab": numar_lab,
            "numar_problema": numar_prob,
        }

        self.__descriere = descriere

        self.__deadline = {
            "an": an,
            "luna": luna,
            "zi": zi
        }

    def get_numar_laborator(self):
        """
        Getter pentru numar laborator
        :return: numar laborator
        """
        return self.__numere["numar_lab"]

    def get_numar_problema(self):
        """
        Getter pentru numar problema laborator
        :return: numamr problema
        """
        return self.__numere["numar_problema"]

    def get_numere_laborator(self):
        """
        Getter pentru numere laborator
        :return: numere laborator
        """
        return self.__numere

    def get_descriere_laborator(self):
        """
        Getter pentru descriere laborator
        :return: descrierea
        """
        return self.__descriere

    def get_deadline_laborator(self):
        """
        Getter pentru deadline laborator
        :return:
        """
        return self.__deadline

    def get_an_deadline(self):
        """
        Getter pentru an deadline
        :return: an deadline
        """
        return self.__deadline["an"]

    def get_luna_deadline(self):
        """
        Getter pentru luna deadline
        :return: luna deadline
        """
        return self.__deadline["luna"]

    def get_zi_deadline(self):
        """
        Getter pentru zi deadline
        :return: zi deadline
        """
        return self.__deadline["zi"]

    def set_descriere_laborator(self, descriere):
        """
        Setter pentru descriere laborator
        :param descriere: descrierea de inlocuit
        """
        self.__descriere = descriere

    def set_deadline_laborator(self, an, luna, zi):
        """
        Setter pentru deadline laborator
        :param an: anul deadlineului
        :param luna: luna deadlineului
        :param zi: ziua deadlineului
        """
        self.__deadline["an"] = an
        self.__deadline["luna"] = luna
        self.__deadline["zi"] = zi