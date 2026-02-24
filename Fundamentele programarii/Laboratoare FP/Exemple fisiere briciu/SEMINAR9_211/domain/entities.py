class Melodie:
    def __init__(self, m_id: int, titlu: str, artist: str, gen: str, durata: float):
        self.__id = m_id
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_id(self):
        return self.__id

    def get_artist(self):
        return self.__artist

    def get_gen(self):
        return self.__gen

    def get_titlu(self):
        return self.__titlu

    def get_durata(self):
        return self.__durata

    # TO DO: add the other setters
    def set_titlu(self, titlu_nou):
        self.__titlu = titlu_nou

    def __eq__(self, other):
        return self.__id == other.__id

    def __str__(self):
        return f"Melodie #{self.__id} (titlu = {self.__titlu}; artist = {self.__artist}; gen = {self.get_gen()}; durata = {self.get_durata()})"

    # @property
    # def id_melodie(self):
    #     print("ID melodie property")
    #     return self.__id


# m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
# print(m)
# info = "Info"+str(m)
# print(info)

# TO-DO:
# add tests for entities (create, getters, setters)

class Persoana:
    def __init__(self, cnp: str, name: str):
        self.__cnp = cnp
        self.__name = name

    @property
    def cnp(self):
        return self.__cnp

    @property
    def nume(self):
        return self.__name

    @nume.setter
    def nume(self, new_name):
        self.__name = new_name

    def __eq__(self, other):
        if type(self) != type(other):
            return False
        return self.__cnp == other.__cnp

    def __str__(self):
        return "[" + str(
            self.__cnp) + "] Persoana: Nume = " + self.__name


class Rating:
    def __init__(self, cnp_persoana, id_melodie, scor):
        self.__persoana_cnp = cnp_persoana
        self.__melodie_id = id_melodie
        self.__scor = scor

    def get_melodie_id(self):
        return self.__melodie_id

    def get_persoana_cnp(self):
        return self.__persoana_cnp

    def get_scor(self):
        return self.__scor

    def __str__(self):
        return f"Melodia cu ID # {self.__melodie_id} a fost evaluata de persoana cu CNP{self.__persoana_cnp}"

    def __eq__(self, other):
        return self.__melodie_id == other.__melodie_id and self.__persoana_cnp == other.__persoana_cnp
# p = Persoana("124135345", "ahghs rgsd")
# m1 = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 23.97)
#
# r = Rating(p, m1, 3.4)
# print(r)
