from utils.eroare_ui import EroareUI


class UIDovezi:

    def __init__(self, service_dovezi):
        self.__service_dovezi = service_dovezi

    def ui_adauga_dovada(self, parametri_comanda):

        if len(parametri_comanda) != 6:
            raise EroareUI("Numar parametri invalid!")

        try:
            id_dovada = parametri_comanda[0]
        except ValueError:
            raise EroareUI("Id invalid")

        descriere = parametri_comanda[1]
        data = parametri_comanda[2]
        tip = parametri_comanda[3]
        suspect = parametri_comanda[4] + " " + parametri_comanda[5]

        self.__service_dovezi.adauga_dovada(id_dovada, descriere, data, tip, suspect)

    def ui_afiseaza_dovezi(self, parametri_comanda):

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        dovezi = self.__service_dovezi.get_dovezi()
        if len(dovezi) == 0:
            print("Nu exista dovezi")

        else:
            for dovada in dovezi.values():
                print(str(dovada) + '\n')

    def ui_afiseaza_dovezi_string(self, parametri_comanda):

        if len(parametri_comanda) != 1:
            raise EroareUI("Numar parametri invalid!")

        string = parametri_comanda[0]

        dovezi_string = self.__service_dovezi.get_dovezi_string(string)
        if len(dovezi_string) == 0:
            print(f"Nu exista dovezi care sa contina {string}")

        for dovada in dovezi_string:
            print(str(dovada) + '\n')

