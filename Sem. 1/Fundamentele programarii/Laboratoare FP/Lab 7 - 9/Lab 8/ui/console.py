
from errors.eroare_repo import EroareRepository
from errors.eroare_ui import EroareUI
from errors.eroare_validator import EroareValidator


class Console:
    def __init__(self, ui_studenti):
        """
        Clasa de consola, cuprinde comenzile posibile
        """
        self.__ui_studenti = ui_studenti
        self.__comenzi = {
            "adauga_student": self.__ui_studenti._ui_adauga_student,
            "afiseaza_studenti": self.__ui_studenti._ui_afiseaza_studenti,
            "sterge_student": self.__ui_studenti._ui_sterge_student,
            "modifica_nume_student": self.__ui_studenti._ui_modifica_nume_student,
            "modifica_grupa_student": self.__ui_studenti._ui_modifica_grupa_student,
            "cautare_studenti_grupa": self.__ui_studenti._ui_cautare_studenti_grupa,
        }


    def run(self):
        """
        Metoda ce ruleaza interfata aplicatiei
        """
        while True:
            text_comanda = input(">>> ").strip()
            if text_comanda == "":
                continue
            if text_comanda == "exit":
                print("La revedere!")
                break

            parti_comanda = text_comanda.split()
            nume_comanda = parti_comanda[0].lower()
            parametri_comanda = parti_comanda[1:]

            if nume_comanda in self.__comenzi:
                try:
                    self.__comenzi[nume_comanda](parametri_comanda)
                except EroareUI as eroare_ui:
                    print(f"Eroare UI: {eroare_ui}")
                except EroareRepository as eroare_repository:
                    print(f"Eroare Repository: {eroare_repository}")
                except EroareValidator as eroare_validator:
                    print(f"Eroare Validator: {eroare_validator}")

            else:
                print(f"{nume_comanda} este comanda invalida!")