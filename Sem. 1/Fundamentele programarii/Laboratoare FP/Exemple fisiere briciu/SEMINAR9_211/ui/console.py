from colorama import Fore


class Console:
    def __init__(self, service_melodii, service_persoane, service_ratings):
        self.__srv_melodii = service_melodii
        self.__srv_persoane = service_persoane
        self.__srv_ratings = service_ratings

    @staticmethod
    def print_menu():
        print("1. Adauga melodie")
        print("2. Sterge melodie dupa id")
        print("3. Cauta melodii cu durata intre doua valori")
        print("4. Modifica melodie")
        print("5. Adauga persoana")
        print("6. Adauga rating")
        print("7. Cele mai ascultate melodii")
        print("--" * 10)
        print("pm. Afiseaza toate melodiile")
        print("pp. Afiseaza toate persoanele")
        print("pr. Afiseaza toate rating-urile")
        print("E. Exit")

    #the code in the following 3 methods
    #looks awfully similar...should we do something about it? (and what?)
    @staticmethod
    def __print_melodii(lista_melodii):
        if not lista_melodii:
            print("Nu exista melodii in lista.")
        else:
            print(Fore.MAGENTA + "Lista de melodii:" + Fore.RESET)
            for melodie in lista_melodii:
                print(melodie)

    @staticmethod
    def __print_persoane(lista_persoane):
        if not lista_persoane:
            print("Nu exista persoane in lista.")
        else:
            print(Fore.GREEN + "Lista de persoane:" + Fore.RESET)
            for persoana in lista_persoane:
                print(persoana)

    @staticmethod
    def __print_ratings(lista_ratings):
        if not lista_ratings:
            print("Nu exista rating-uri in lista.")
        else:
            print(Fore.GREEN + "Lista de rating-uri:" + Fore.RESET)
            for rating in lista_ratings:
                print(rating)
    def __add_ui(self):
        m_id = input("ID melodie:")
        titlu = input("Titlu: ")
        artist = input("Artist: ")
        gen = input("Gen:")
        durata = input("Durata")

        try:
            m_id = int(m_id)
            durata = float(durata)
            self.__srv_melodii.add_melodie(m_id, titlu, artist, gen, durata)
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)
        else:
            print(Fore.GREEN + "Melodia a fost adaugata cu succes." + Fore.RESET)

    def __delete_ui(self):
        m_id = input("ID-ul melodiei de sters")
        try:
            m_id = int(m_id)
            melodie_stearsa = self.__srv_melodii.delete_melodie(m_id)
            print(f"{melodie_stearsa} a fost stearsa.")
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def __filter_by_durata_ui(self):
        durata_lower_bound = input("Durata melodiilor ar trebui sa fie mai mare de: ")
        durata_upper_bound = input("Durata melodiilor ar trebui sa fie mai mica de: ")
        try:
            durata_upper_bound = float(durata_upper_bound)
            durata_lower_bound = float(durata_lower_bound)
            melodii_filtered = self.__srv_melodii.filter_by_durata(durata_lower_bound, durata_upper_bound)
            print(f"Melodiile cu durata mai mare de {durata_lower_bound} si mai mica de {durata_upper_bound} sunt:")
            Console.__print_melodii(melodii_filtered)
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def __modify_ui(self):
        m_id = input("ID melodie:")
        titlu = input("Titlu: ")
        artist = input("Artist: ")
        gen = input("Gen:")
        durata = input("Durata")
        try:
            m_id = int(m_id)
            durata = float(durata)
            melodie_veche = self.__srv_melodii.update_melodie(m_id, titlu, artist, gen, durata)
            print(f"{melodie_veche} a fost actualizata.")
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def run(self):
        while True:
            Console.print_menu()
            option = input(">>>").strip()
            if option == "1":
                self.__add_ui()
            elif option == "2":
                self.__delete_ui()
            elif option == "3":
                self.__filter_by_durata_ui()
            elif option == '4':
                self.__modify_ui()
            elif option == "5":
                self.__add_persoana_ui()
            elif option == "6":
                self.__add_rating_ui()
            elif option == '7':
                d = self.__srv_ratings.most_listened_to(3)
                for elem in d:
                    print(elem)
            if option.upper() == "PP":
                Console.__print_persoane(self.__srv_persoane.get_all())
            elif option.upper() == 'PM':
                Console.__print_melodii(self.__srv_melodii.get_melodii())
            elif option.upper() == 'PR':
                Console.__print_melodii(self.__srv_ratings.get_all())
            elif option.upper() == 'E':
                break

    def __add_persoana_ui(self):
        cnp = input("CNP: ")
        nume = input("Nume: ")
        try:
            self.__srv_persoane.add_persoana(cnp, nume)
        except ValueError as ve:
            print(Fore.RED + str(ve) + Fore.RESET)


    def __add_rating_ui(self):
        try:
            cnp_p = input("CNP:")
            id_m = int(input("ID melodie"))
            scor = float(input("Scor:"))
            self.__srv_ratings.add_rating(id_m, cnp_p, scor)
        except Exception as e:
            print(Fore.RED + str(e) + Fore.RESET)
