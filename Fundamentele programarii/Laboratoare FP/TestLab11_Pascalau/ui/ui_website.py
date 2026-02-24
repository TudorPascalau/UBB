from errors.eroare_ui import EroareUI


class UIWebsite:

    def __init__(self, service_websites):
        self.__service_websites = service_websites

    def ui_adauga_website(self, parametri_comanda):
        """
        Metoda UI pentru adaugare website
        :raises EroareUI: daca numar parametri invalizi
        :raises EroareUI: daca date introduse invalide
        """

        if len(parametri_comanda) != 7:
            raise EroareUI("Numar parametri invalizi")

        try:
            id = int(parametri_comanda[0])
            url = parametri_comanda[1]
            adress = parametri_comanda[2] + " " +  parametri_comanda[3]
            holder = parametri_comanda[4] + " " + parametri_comanda[5]
            visitors = int(parametri_comanda[6])

        except ValueError:
            raise EroareUI("Date invalide")

        self.__service_websites.adauga_website(id, url, adress, holder, visitors)
        print("Website adaugat cu succes!")

    def ui_predict_visitors(self, parametri_comanda):
        """
        Metoda UI pentru predict visitors
        :raises EroareUI: daca numar parametri invalizi
        :raises EroareUI: daca date introduse invalide
        """

        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalizi")

        try:
            zile = int(parametri_comanda[0])
            prefix = parametri_comanda[1]
        except ValueError:
            raise EroareUI("Date invalide")

        if zile < 1:
            raise EroareUI("Date invalide")

        visitors_pred = self.__service_websites.predict_visitors(zile, prefix)
        print(str(visitors_pred) + '\n')
