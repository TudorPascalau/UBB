from errors.eroare_repo import EroareRepository
from errors.eroare_ui import EroareUI
from errors.eroare_valid import EroareValidator


class Console:

    def __init__(self, ui_website):
        self.__ui_website = ui_website
        self.__comenzi = {
            "adauga_website": self.__ui_website.ui_adauga_website,
            "predict_visitors": self.__ui_website.ui_predict_visitors,
        }


    def run(self):
        """
        Metoda principala a aplicatiei, care faciliteaza UI
        """
        while True:

            user_input = input(">>> ").strip()

            parti_comanda = user_input.split()
            comanda = parti_comanda[0]
            parametri = parti_comanda[1:]

            if comanda == "exit":
                print("Goodbye")
                break

            elif comanda == "":
                continue

            elif comanda in self.__comenzi:
                try:
                    self.__comenzi[comanda](parametri)

                except EroareUI as eroare_ui:
                    print(eroare_ui)
                except EroareRepository as eroare_repo:
                    print(eroare_repo)
                except EroareValidator as eroare_validator:
                    print(eroare_validator)

            else:
                print("Nu inteleg comanda")