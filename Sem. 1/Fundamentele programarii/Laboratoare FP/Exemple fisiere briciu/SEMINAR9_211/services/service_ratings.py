from collections import defaultdict

from domain.entities import Rating
from exceptions.exceptions import SongDoesNotExistException, PersonDoesNotExistException
from services.dto import AscultariMelodie


class ServiceRatings:
    def __init__(self, repo_melodii, repo_persoane, repo_ratings, validator_rating):
        self.__repo_melodii = repo_melodii
        self.__repo_persoane = repo_persoane
        self.__repo_ratings = repo_ratings
        self.__validator = validator_rating

    def add_rating(self, id_melodie, cnp_persoana, scor_evaluare):
        """
        Adauga evaluare (=rating)
        :param id_melodie: id-ul melodiei pentru care se adauga evaluare
        :param cnp_persoana: CNP-ul persoanei care realizeaza evaluarea
        :param scor_evaluare: scorul evaluarii
        :return: -; colectia de rating-uri se modifica prin adaugarea evaluarii
        :raises: ValueError daca nu exista melodia cu id_melodie
                 ValueError daca nu exista persoana cu CNP cnp_persoana
                 ValueError daca rating-ul este invalid (scorul evaluarii este invalid)
                 ValueError daca mai exista o evaluare pentru melodia data realizata de persoana cu cnp_persoana
        """
        """
                Adauga evaluare (=rating)
                :param id_melodie: id-ul melodiei pentru care se adauga evaluare
                :param cnp_persoana: CNP-ul persoanei care realizeaza evaluarea
                :param scor_evaluare: scorul evaluarii
                :return: -; colectia de rating-uri se modifica prin adaugarea evaluarii
                :raises: SongDoesNotExistException daca nu exista melodia cu id_melodie
                         PersonDoesNotExistException daca nu exista persoana cu CNP cnp_persoana
                         ValidationException daca rating-ul este invalid (scorul evaluarii este invalid)
                         RatingAlreadyExistsException daca mai exista o evaluare pentru melodia data realizata de persoana cu cnp_persoana
                """
        melodie = self.__repo_melodii.find(id_melodie)
        if melodie is None:
            raise SongDoesNotExistException()
        person = self.__repo_persoane.find(cnp_persoana)
        if person is None:
            raise PersonDoesNotExistException()

        r = Rating(cnp_persoana, id_melodie, scor_evaluare)
        self.__validator.validate(r)
        self.__repo_ratings.store(r)

    def most_listened_to(self, n=5):
        """
        Returneaza informatii despre cele mai ascultate n melodii
        :param n: numarul de melodii de afisat
        :return: lista de obiecte AscultariMelodie
        """
        # 1 ascultare = 1 rating
        ratings = self.__repo_ratings.get_all()
        d = {}
        #modificat in seminar 9, folosire DTO
        # cheie = id melodie
        # valoare = obiect DTO
        #am putea crea dto-urile in repo (completand
        #doar ce campuri cunoastem)?
        for rating in ratings:
            id_m = rating.get_melodie_id()
            if id_m not in d:
                melodie = self.__repo_melodii.find(id_m)
                d[id_m] = AscultariMelodie(melodie.get_titlu(),
                                           melodie.get_artist(),
                                           1)
            else:
                d[id_m].set_nr_ascultari(d[id_m].get_nr_ascultari() + 1)

        dto_list = list(d.values())
        dto_list = sorted(dto_list, key=lambda dto: dto.get_nr_ascultari(), reverse=True)
        dto_list = dto_list[:n]
        return dto_list

    def get_all(self):
        return self.__repo_ratings.get_all()
