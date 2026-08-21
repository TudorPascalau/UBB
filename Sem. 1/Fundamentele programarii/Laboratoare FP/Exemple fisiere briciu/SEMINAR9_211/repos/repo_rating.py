from domain.entities import Rating


class RatingMemoryRepository:
    def __init__(self):
        self.__ratings = []

    def find(self, rating):
        """
        Cauta un rating in colectia de rating-uri
        :param rating: rating-ul care este cautat
        :return: True daca un rating realizat de aceeasi persoana si pentru aceeasi melodie ca
                    si in cel dat ca parametru exista deja in colectie
                 False altfel
        """
        for existing_rating in self.__ratings:
            if rating == existing_rating:
                return True
        return False

    def store(self, rating):
        """
        Adauga un rating in colectia de rating-uri
        :param rating: rating-ul de adaugat
        :return: -; colectia se modifica prin adaugarea rating-ului
        :raises: ValueError daca exista deja o evaluare pentru melodia si persoana data
        """
        if self.find(rating):
            raise ValueError("Exista deja evaluare pentru melodia si persoana data.")
        self.__ratings.append(rating)

    def get_all(self):
        """
        Returneaza intreaga colectie de rating-uri
        """
        return self.__ratings

#adaugat in seminarul 9 - RepoFile cu mostenire

class RepoRatingFile(RatingMemoryRepository):
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
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                parts = line.split(',')
                melodie_id, cnp, scor = parts
                melodie_id = int(melodie_id)
                scor = float(scor)
                rating = Rating(cnp, melodie_id, scor)
                super().store(rating)

    def __save_to_file(self):
        with open(self.__filename, 'w') as f:
            for rating in super().get_all():
                rating_str = str(rating.get_melodie_id()) + "," + \
                             rating.get_persoana_cnp() + "," + str(rating.get_scor()) + "\n"
                f.write(rating_str)

    def store(self, rating):
        super().store(rating)
        self.__save_to_file()
