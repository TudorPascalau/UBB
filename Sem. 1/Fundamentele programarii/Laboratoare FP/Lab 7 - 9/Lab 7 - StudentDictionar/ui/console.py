
from errors.eroare_repo import EroareRepository
from errors.eroare_ui import EroareUI
from errors.eroare_validator import EroareValidator


class Console:
    def __init__(self, ui_studenti, ui_laborator, ui_assignment, ui_rapoarte):
        """
        Clasa de consola, cuprinde comenzile posibile
        """
        self.__ui_studenti = ui_studenti
        self.__ui_laborator = ui_laborator
        self.__ui_assignment = ui_assignment
        self.__ui_rapoarte = ui_rapoarte
        self.__comenzi = {
            "adauga_student": self.__ui_studenti._ui_adauga_student,
            "afiseaza_studenti": self.__ui_studenti._ui_afiseaza_studenti,
            "sterge_student": self.__ui_studenti._ui_sterge_student,
            "modifica_nume_student": self.__ui_studenti._ui_modifica_nume_student,
            "modifica_grupa_student": self.__ui_studenti._ui_modifica_grupa_student,
            "cautare_studenti_grupa": self.__ui_studenti._ui_cautare_studenti_grupa,
            "genereaza_studenti": self.__ui_studenti._ui_genereaza_studenti,

            "adauga_laborator": self.__ui_laborator._ui_adauga_laborator,
            "afiseaza_laboratoare": self.__ui_laborator._ui_afiseaza_laboratoare,
            "sterge_laborator": self.__ui_laborator._ui_sterge_laborator,
            "modifica_descriere_lab": self.__ui_laborator._ui_modifica_descriere_laborator,
            "modifica_deadline_lab": self.__ui_laborator._ui_modifica_deadline_laborator,

            "asigneaza_problema": self.__ui_assignment._ui_adauga_assignment,
            "notare_assignment": self.__ui_assignment._ui_notare_assignment,
            "sterge_assignment": self.__ui_assignment._ui_sterge_assignment,
            "afiseaza_assignments": self.__ui_assignment._ui_afiseaza_assignments,

            "studenti_ordonat_nume": self.__ui_rapoarte._ui_get_studenti_ordonati_alfabetic,
            "studenti_ordonat_nota": self.__ui_rapoarte._ui_get_studenti_ordonat_nota,
            "top_20procent_medie": self.__ui_rapoarte._ui_get_top20procent_medie,
            "top_5_medie": self.__ui_rapoarte._ui_get_top5_medie,

        }

    def __setup(self):
        self.__comenzi["adauga_student"](["23", "Jordan", "323"])
        self.__comenzi["adauga_student"](["14", "Pascalau", "215"])
        self.__comenzi["adauga_student"](["1", "Popescu", "216"])
        self.__comenzi["adauga_student"](["25", "Muntoiu", "323"])
        self.__comenzi["adauga_student"](["16", "Pragai", "215"])
        self.__comenzi["adauga_student"](["2", "Frumosu", "216"])

        self.__comenzi["adauga_laborator"](["9", "2", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["9", "3", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["10", "2", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["5", "5", "desc", "2025", "12", "1"])

        self.__comenzi["asigneaza_problema"](["23", "9", "2"])
        self.__comenzi["notare_assignment"](["23", "9", "2", "10"])
        self.__comenzi["asigneaza_problema"](["14", "9", "2"])
        self.__comenzi["notare_assignment"](["14", "9", "2", "7"])
        self.__comenzi["asigneaza_problema"](["1", "10", "2"])
        self.__comenzi["notare_assignment"](["1", "10", "2", "9"])

        self.__comenzi["asigneaza_problema"](["25", "9", "3"])
        self.__comenzi["notare_assignment"](["25", "9", "3", "10"])
        self.__comenzi["asigneaza_problema"](["16", "5", "5"])
        self.__comenzi["notare_assignment"](["16", "5", "5", "7"])
        self.__comenzi["asigneaza_problema"](["2", "9", "2"])
        self.__comenzi["notare_assignment"](["2", "9", "2", "9"])

    def __setup_no_assign(self):
        self.__comenzi["adauga_student"](["23", "Jordan", "323"])
        self.__comenzi["adauga_student"](["14", "Pascalau", "215"])
        self.__comenzi["adauga_student"](["1", "Popescu", "216"])
        self.__comenzi["adauga_student"](["25", "Muntoiu", "323"])
        self.__comenzi["adauga_student"](["16", "Pragai", "215"])
        self.__comenzi["adauga_student"](["2", "Frumosu", "216"])

        self.__comenzi["adauga_laborator"](["9", "2", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["9", "3", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["10", "2", "desc", "2025", "12", "1"])
        self.__comenzi["adauga_laborator"](["5", "5", "desc", "2025", "12", "1"])

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

            if nume_comanda == "setup":
                self.__setup()

            elif nume_comanda == "setup_no_assign":
                self.__setup_no_assign()

            elif nume_comanda in self.__comenzi:
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
