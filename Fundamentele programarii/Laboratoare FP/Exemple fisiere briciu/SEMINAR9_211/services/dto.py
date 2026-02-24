class AscultariMelodie:
    def __init__(self, titlu, artist, nr_ascultari):
        self.__titlu = titlu
        self.__artist = artist
        self.__nr_ascultari = nr_ascultari

    def get_titlu(self):
        return self.__titlu

    def get_artist(self):
        return self.__artist

    def get_nr_ascultari(self):
        return self.__nr_ascultari

    def set_nr_ascultari(self, nr):
        self.__nr_ascultari = nr

    def __str__(self):
        return f"Titlu: {self.__titlu}; Artist: {self.__artist}; Nr. ascultari{self.__nr_ascultari}"
