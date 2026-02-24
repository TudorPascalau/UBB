from errors.eroare_ui import EroareUI


class UILaboratoare:

    def __init__(self, service_laboratoare):
        self.__service_laboratoare = service_laboratoare

    def _ui_adauga_laborator(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru adaugare laborator
        :raises EroareUI: daca nu are 6 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 6:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Numar laborator invalid!")

        try:
            numar_prob = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numar problema invalid!")

        descriere = parametri_comanda[2]

        try:
            an = int(parametri_comanda[3])
            luna = int(parametri_comanda[4])
            zi = int(parametri_comanda[5])

        except ValueError:
            raise EroareUI("Deadline invalid!")

        self.__service_laboratoare.adauga_laborator(numar_lab, numar_prob, descriere, an, luna, zi)
        print("Laborator adaugat cu succes!")


    def _ui_afiseaza_laboratoare(self, parametri_comanda):
        """
        Metoda care afiseaza laboratoarele
        :raises EroareUI: daca nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        laboratoare = self.__service_laboratoare.access_laboratoare()

        if len(laboratoare) == 0:
            print("Nu exista laboratoare")

        else:
            print("Laboratoare: \n")
            for laborator in laboratoare:
                print(f"Laboratorul {laborator.get_numar_laborator()}, problema {laborator.get_numar_problema()}")
                print(f"Descriere: {laborator.get_descriere_laborator()}")
                print(f"Deadline: an {laborator.get_an_deadline()}, luna {laborator.get_luna_deadline()}, zi {laborator.get_zi_deadline()}")
                print("---------------------")

    def _ui_sterge_laborator(self, parametri_comanda):
        """
        Metoda care sterge un laborator
        :raises EroareUI, daca nu are 2 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
            numar_prob = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        self.__service_laboratoare.sterge_laborator(numar_lab, numar_prob)
        print("Laborator sters cu succes!")

    def _ui_modifica_descriere_laborator(self, parametri_comanda):
        """
        Metoda care modifica descriere laborator
        :raises EroareUI, daca nu are 3 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 3:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
            numar_prob = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        descriere = parametri_comanda[2]

        self.__service_laboratoare.modifica_descriere_laborator(numar_lab, numar_prob, descriere)
        print("Descrierea modificata cu succes!")

    def _ui_modifica_deadline_laborator(self, parametri_comanda):
        """
        Metoda care modifica deadline laborator
        :raises EroareUI, daca nu are 5 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 5:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
            numar_prob = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        try:
            an = int(parametri_comanda[2])
            luna = int(parametri_comanda[3])
            zi = int(parametri_comanda[4])
        except ValueError:
            raise EroareUI("Deadline invalid!")

        self.__service_laboratoare.modifica_deadline_laborator(numar_lab, numar_prob, an, luna, zi)
        print("Deadline modificata cu succes!")