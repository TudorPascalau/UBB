
from datetime import datetime

class EroareUI(Exception):
    pass

class UIAutomobile:
    def __init__(self, service):
        self.__service = service

    def __print_menu(self):
        print("1. Adauga automobile")
        print("2. Afiseaza automobile")
        print("3. Genereaza marca")
        print("4. Sortare pret")
        print("5. Export automobile sortate")
        print("x. Exit")

    def __adauga_automobile(self):
        try:
            a_id = int(input("Introduceti id: "))
        except ValueError:
            raise EroareUI("Id invalid! Trebuie intreg")

        marca = input("Introduceti marca: ")
        try:
            pret = int(input("Introduceti pret: "))
        except ValueError:
            raise EroareUI("Pret invalid! Trebuie intreg")
        model = input("Introduceti model: ")
        try:
            data_revizie_str = input("Introduceti data reviziei: ")
            data_revizie = datetime.strptime(data_revizie_str, "%d:%m:%Y")
        except ValueError:
            raise EroareUI("Format data revizie invalid!")

        self.__service.adauga_automobil(a_id, marca, pret, model, data_revizie_str)

    def __afiseaza_automobile(self):
        automobile_values = self.__service.get_automobile_values()
        for automobil in automobile_values:
            if datetime.now() > automobil.get_data_revizie():
                expirat = True
            else: expirat = False

            if expirat:
                print("*",automobil)
            else:
                print(automobil)

    def __afiseaza_automobile_sortate_pret(self):
        automobile_sortate_pret = self.__service.sortare_pret_automobile()
        for automobil in automobile_sortate_pret:
            if datetime.now() > automobil.get_data_revizie():
                expirat = True
            else:
                expirat = False

            if expirat:
                print("*", automobil)
            else:
                print(automobil)

    def __export_automobile_sortate(self):
        file_name = input("Introduceti nume fisier fara terminator: ")
        self.__service.export_automobile_sortate(file_name)

    def run(self):

        while True:
            self.__print_menu()
            command = input(">>> ")
            match command:
                case "1":
                    try:
                        self.__adauga_automobile()
                        print("Automobil adaugat cu succes!")
                    except Exception as e:
                        print(e)

                case "2":
                    self.__afiseaza_automobile()

                case "3":
                    print(self.__service.genereaza_model())

                case "4":
                    self.__afiseaza_automobile_sortate_pret()

                case "5":
                    self.__export_automobile_sortate()

                case "x":
                    print("La revedere!")
                    break

                case _:
                    print("Nu inteleg comanda")