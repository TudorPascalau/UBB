from domain.entities import Melodie
from exceptions.exceptions import RepositoryException


class RepoMelodieMemory:
    """
    Pure fabrication - Repository Pattern
    """

    def __init__(self):
        # cheie=id: valoare=melodie
        self.__melodii = {}
        # self.__melodii = []

    def add(self, melodie: Melodie):
        """
        Adauga o melodie la colectia de melodii
        :param melodie: melodie de adaugat
        :return: -; melodia data a fost adaugata la colectia de melodii
        :raises: ValueError daca exista deja melodie cu id dat
        """
        if melodie.get_id() in self.__melodii:
            raise ValueError("Exista deja melodie cu id dat")
        self.__melodii[melodie.get_id()] = melodie

    def remove(self, m_id: int) -> Melodie:
        """
        Sterge melodie cu id dat
        :param m_id: id-ul melodiei de sters
        :return: melodia stearsa
        :raises: ValueError daca nu exista melodie cu id-ul dat
        """
        if not m_id in self.__melodii:
            raise ValueError(f"Nu exista melodie cu id-ul {m_id}")
        melodie_stearsa = self.__melodii[m_id]
        del self.__melodii[m_id]
        return melodie_stearsa

    def update(self, m_id: int, melodie_noua: Melodie) -> Melodie:
        """
        Actualizeaza o melodie
        :param m_id: id-ul melodiei de actualizat
        :param melodie_noua: melodia cu informatia actualizata
        :return: melodia veche
        :raises: ValueError daca nu exista melodie cu id = m_id
        """
        melodie_veche = self.remove(m_id)
        self.add(melodie_noua)
        return melodie_veche

    def find(self, m_id: int):
        """
        Cauta melodia cu id-ul m_id
        :param m_id: id-ul cautat
        :return: melodia cu id m_id, daca aceasta exista, None altfel
        """
        if not m_id in self.__melodii:
            return None
        return self.__melodii[m_id]

    def size(self):
        """
        Returneaza numarul de melodii
        """
        return len(self.__melodii)

    def get_all(self):
        """
        Returneaza lista de melodii
        :return:
        """
        return self.__melodii.values()




class RepoMelodieFile(RepoMelodieMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        """
        Incarca datele din fisier
        :return: -; datele din fisier sunt incarcate si in memorie
        :raises: RepositoryException daca exista probleme la citirea datelor din fisier
        """
        try:
            with open(self.__filename, "r", encoding="utf-8") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    if line:
                        id_melodie, titlu, artist, gen, durata = line.split(",")
                        m = Melodie(int(id_melodie), titlu.strip(), artist.strip(), gen.strip(), float(durata))
                        super().add(m)
        except IOError:
            raise RepositoryException("Nu s-au putut citi datele din fisierul:" + self.__filename)

    def add(self, melodie: Melodie):
        super().add(melodie)
        # SongMemoryRepository.store(self, melodie)
        self.__save_to_file()

    def remove(self, id: int):
        mel_stearsa = super().remove(id)
        self.__save_to_file()
        return mel_stearsa

    def update(self,m_id, melodie_actualizata):
        super().update(m_id, melodie_actualizata)
        self.__save_to_file()

    def __save_to_file(self):
        """
        Salveaza datele in fisier
        :return: -; fisierul cu numele self.__filename va contine datele in formatul specificat
        :raises: RepositoryException daca exista probleme la scrierea in fisier
        """
        try:
            with open(self.__filename, "w", encoding="utf-8") as file:
                melodii = super().get_all()
                # print(len(melodii))
                for melodie in melodii:
                    melodie_str = str(
                        melodie.get_id()) + "," + melodie.get_titlu() + "," + melodie.get_artist() + "," + melodie.get_gen() + "," + str(
                        melodie.get_durata())
                    melodie_str += '\n'
                    file.write(melodie_str)
        except IOError:
            raise RepositoryException("Nu s-au putut salva datele in fisierul " + self.__filename)
