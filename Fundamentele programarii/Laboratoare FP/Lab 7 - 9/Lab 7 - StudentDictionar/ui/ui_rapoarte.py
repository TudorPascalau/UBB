from errors.eroare_ui import EroareUI


class UIRaport:

    def __init__(self, service_rapoarte):
        self.__service_rapoarte = service_rapoarte

    def _ui_get_studenti_ordonati_alfabetic(self, parametri_comanda):
        """
        Metoda care genereaza raport
        :raises EroareUI, daca nu are 2 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
            numar_problema = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        numere_laborator ={
            "numar_lab": numar_lab,
            "numar_problema": numar_problema,
        }

        rezultat = self.__service_rapoarte.get_studenti_ordonat_alfabetic(numere_laborator)

        for item in rezultat:
            print(f"Student: {item[0].get_nume()}")
            print(f"Nota: {item[1]}")

    def _ui_get_studenti_ordonat_nota(self, parametri_comanda):
        """
        Metoda care genereaza raport
        :raises EroareUI, daca nu are 2 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalid!")

        try:
            numar_lab = int(parametri_comanda[0])
            numar_problema = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        numere_laborator = {
            "numar_lab": numar_lab,
            "numar_problema": numar_problema,
        }

        rezultat = self.__service_rapoarte.get_studenti_ordonat_nota(numere_laborator)

        for item in rezultat:
            print(f"Student: {item[0].get_nume()}")
            print(f"Nota: {item[1]}")

    def _ui_get_top20procent_medie(self, parametri_comanda):
        """
        Metoda care genereaza raport
        :raises EroareUI, daca nu are 0 parametri
                EroareUI, daca datele introduse sunt invalide
        """
        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        rezultat = self.__service_rapoarte.get_top20procent_medie()
        for item in rezultat:
            print(f"Student: {item[0].get_nume()}")
            print(f"Medie: {item[1]}")

    def _ui_get_top5_medie(self, parametri_comanda):
        """
        Metoda care genereaza raport
        :raises EroareUI, daca nu are 3 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        rezultat = self.__service_rapoarte.get_top5_medie()
        for item in rezultat:
            print(f"Student: {item[0].get_nume()}")
            print(f"Medie: {item[1]}")

