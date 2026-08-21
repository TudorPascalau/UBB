from utils.eroare_repo import EroareRepository
from utils.eroare_ui import EroareUI


class Console:

    def __init__(self, ui_dovezi):
        self.__ui_dovezi = ui_dovezi
        self.__comenzi = {
            "adauga_dovada": self.__ui_dovezi.ui_adauga_dovada,
            "afiseaza_dovezi": self.__ui_dovezi.ui_afiseaza_dovezi,
            "dovezi_string": self.__ui_dovezi.ui_afiseaza_dovezi_string,
        }

    def run(self):

        while True:
            user_input = input(">>>").strip()

            if user_input == "exit":
                break

            elif user_input == "":
                continue

            else:
                parti_comanda = user_input.split()
                comanda = parti_comanda[0].lower()
                parametri_comanda = parti_comanda[1:]

                if comanda in self.__comenzi:
                    try:
                        self.__comenzi[comanda](parametri_comanda)
                    except EroareUI as eroare_ui:
                        print(eroare_ui)
                    except EroareRepository as eroare_repository:
                        print(eroare_repository)

                else:
                    print("Nu inteleg comanda")