import datetime


class EroareUI(Exception):
    pass

class UISedinta:

    def __init__(self, service):
        self.__service = service

    def __print_menu(self):
        """
        Functie care printeaza meniul principal de interactiune UI
        """
        print("1. Adauga sedinta")
        print("2. Export in fisier")
        print("3. Setare filtru data")
        print("x. Iesire aplicatie")

    def __print_filtru(self):
        filtru = self.__service.get_filtru()

        if filtru != False:
            print("Zilele din urmatoarele 3 zile de la filtru:")
            zi = filtru
            sedinte_zi = self.__service.get_sedinte_zi_ora(zi)

            for sedinta in sedinte_zi:
                print(sedinta)

            zi = zi + datetime.timedelta(days=1)
            sedinte_zi = self.__service.get_sedinte_zi_ora(zi)

            for sedinta in sedinte_zi:
                print(sedinta)

            zi = zi + datetime.timedelta(days=1)
            sedinte_zi = self.__service.get_sedinte_zi_ora(zi)

            for sedinta in sedinte_zi:
                print(sedinta)

    def __ui_adauga(self):
        """
        Functie pentru adaugarea sedinta prin UI
        """

        data_str = input("Introduceti data: ")
        ora_str = input("Introduceti ora: ")
        subiect = input("Introduceti subiect: ")
        extraordinar = input("Introduceti tipul (normala / extraordinara): ")

        try:
            self.__service.adauga_sedinta(data_str, ora_str, subiect, extraordinar)
            print("Sedinta a fost adaugata cu succes")
        except Exception as e:
            print(e)

    def __print_sedinte_maine(self):

        print("Sedintele ce au loc in ziua de maine")

        zi = datetime.datetime.today() + datetime.timedelta(days=1)
        sedinte_zi = self.__service.get_sedinte_zi_ora(zi)

        for sedinta in sedinte_zi:
            print(sedinta)

    def __export(self):

        try:
            file_path = input("Introduceti nume fisier (fara extensie): ")
            key = input("Introduceti un sir: ")
            self.__service.export(file_path, key)

        except Exception as e:
            print(e)

    def __setare_filtru(self):
        try:
            data_str = input("Introduceti filtru data: ")
            data = datetime.datetime.strptime(data_str, "%d.%m")

            self.__service.seteaza_filtru(data)

        except ValueError:
            raise EroareUI("Data invalida")

    def run(self):
        """
        Functie care faciliteaza schimb date cu utilizatorul
        """

        self.__print_sedinte_maine()

        while True:
            self.__print_filtru()

            self.__print_menu()
            comanda = input(">>> ")
            match comanda:

                case "1":
                    self.__ui_adauga()

                case "2":
                    self.__export()

                case "3":
                    self.__setare_filtru()

                case "x":
                    print("La revedere!")
                    break

                case _:
                    print("Nu inteleg comanda!")