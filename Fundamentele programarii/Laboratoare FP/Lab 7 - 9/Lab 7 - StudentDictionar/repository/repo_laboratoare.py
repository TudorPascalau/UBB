from errors.eroare_repo import EroareRepository


class RepositoryLaboratoare:
    """
    Operatii CRUD
    """
    def __init__(self):
        """
        Repository pentru stocat laboratoare
        """
        self.__laboratoare = [] # Totalitatea laboratoarelor

    def __len__(self):
        return len(self.__laboratoare) # Numarul de laboratoare

    def adauga_laborator(self, laborator):
        """
        Metoda care adauga un laborator in repository
        :param laborator: laboratorul de adaugat
        :raises EroareRepository, daca numerele laboratorului deja exista
        """
        # Verificarea unicitatii laboratorului
        numar_lab = laborator.get_numar_laborator()
        numar_prob = laborator.get_numar_problema()

        for prev_lab in self.__laboratoare:
            if numar_lab == prev_lab.get_numar_laborator() and numar_prob == prev_lab.get_numar_problema():
                raise EroareRepository("numere problema deja existente!")

        # Adaugarea laboratorului
        self.__laboratoare.append(laborator)

    def get_all_laboratoare(self):
        """
        Metoda care returneaza lista de laboratoare
        :return:
        """
        return self.__laboratoare

    def sterge_laborator(self, laborator):
        """
        Metoda care sterge un laborator din repository
        :param laborator: laboratorul de sters
        :raises EroareRepository, daca nu exista laboratoare
        """
        if len(self.__laboratoare) == 0:
            raise EroareRepository("Nu exista laboratoare de sters!")
        self.__laboratoare.remove(laborator)

    def modifica_descriere_laborator(self, laborator, descriere):
        """
        Metoda care modifica descrierea unui laborator
        :param laborator: laboratorul de modificat
        :param descriere: Descrierea in care modificam
        """
        laborator.set_descriere_laborator(descriere)

    def modifica_deadline_laborator(self, laborator, deadline):
        """
        Metoda care modifica deadline laborator
        :param laborator: laboratorul de modificat
        :param deadline: descrirea in care modificam
        """
        laborator.set_deadline_laborator(deadline)
