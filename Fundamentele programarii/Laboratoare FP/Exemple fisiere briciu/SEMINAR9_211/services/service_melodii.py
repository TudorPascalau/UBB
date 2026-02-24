from domain.entities import Melodie


class ServiceMelodii:
    """
    GRASP Controller
    """

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__val = validator

    def add_melodie(self, m_id: int, titlu: str, artist: str, gen: str, durata: float):
        """
        Adauga o melodie (creare + validare + stocare)
        :param m_id: id-ul melodiei de salvat
        :param titlu: titlul melodiei de salvat
        :param artist: artistul melodiei de salvat
        :param gen: genul melodiei de salvat
        :param durata: durata melodiei de salvat
        :raises: ValueError daca melodia este invalida
                 ValueError daca exista deja melodie cu id dat
        """
        m = Melodie(m_id, titlu, artist, gen, durata)
        self.__val.validate(m)
        self.__repo.add(m)

    def delete_melodie(self, m_id: int):
        """
        Sterge melodie cu id-ul dat
        :param m_id: id-ul melodiei de sters
        :return: melodia stearsa, Melodie
        :raises: ValueError daca nu exista melodie cu id dat
        """
        return self.__repo.remove(m_id)

    def filter_by_durata(self, durata_lower_bound: float, durata_upper_bound: float):
        """
        Cauta melodii cu durata intre 2 durate date
        :param durata_lower_bound: limita inferioara a duratei
        :param durata_upper_bound: limita superioara a duratei
        :return: lista cu melodii care au durata intre cele 2 durate
        """
        melodii_all = self.__repo.get_all()
        lista_filtrata = []
        for melodie in melodii_all:
            if durata_lower_bound < melodie.get_durata() < durata_upper_bound:
                lista_filtrata.append(melodie)
        # sau
        # lista_filtrata = [melodie for melodie in melodii_all if
        #                   durata_lower_bound < melodie.get_durata() < durata_upper_bound]
        return lista_filtrata

    def update_melodie(self, m_id: int, titlu: str, artist: str, gen: str, durata: float):
        """
        Actualizeaza o melodie data
        :param m_id: id-ul melodiei de actualizat
        :param titlu: titlul nou al melodiei
        :param artist: artistul nou al melodiei
        :param gen: genul nou al melodiei
        :param durata: durata noua a melodiei
        :return: melodia veche
        :raises: ValueError daca nu exista melodie cu id-ul m_id
                 ValueError daca melodia noua este invalida
        """
        melodie_actualizata = Melodie(m_id, titlu, artist, gen, durata)
        self.__val.validate(melodie_actualizata)
        melodie_veche = self.__repo.find(m_id)
        self.__repo.update(m_id, melodie_actualizata)
        return melodie_veche

    def get_melodii(self):
        """
        Returneaza lista de melodii
        """
        return self.__repo.get_all()

    def get_numar_melodii(self):
        """
        Returneaza numarul de melodii
        :return:
        """
        return self.__repo.size()

    def add_default(self):
        self.add_melodie(101, "Perfect Strangers", "Deep Purple", "rock", 5.11)
        self.add_melodie(102, "Comfortably Numb", "Pink Floyd", "rock", 8.2)
        self.add_melodie(103, "Lose yourself", "Eminem", "hip-hop", 4.01)
        self.add_melodie(104, "Pe Corso", "Pasarea Colibri", "folk", 3.23)
