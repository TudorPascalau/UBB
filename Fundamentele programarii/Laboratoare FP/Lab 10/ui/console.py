
from utils.eroare_repository import EroareRepository
from utils.eroare_ui import EroareUI
from utils.eroare_validator import EroareValidator


class Console:
    def __init__(self, ui_studenti, ui_laboratoare, ui_assignment):
        """
        Clasa de consola, cuprinde comenzile posibile
        """
        self.__ui_studenti = ui_studenti
        self.__ui_laboratoare = ui_laboratoare
        self.__ui_assignment = ui_assignment
        self.__comenzi = {
            "adauga_student": self.__ui_studenti.ui_adauga_student,
            "afiseaza_studenti": self.__ui_studenti.ui_afiseaza_studenti,
            "sterge_student": self.__ui_studenti.ui_sterge_student,
            "modifica_nume_student": self.__ui_studenti.ui_modifica_nume_student,
            "modifica_grupa_student": self.__ui_studenti.ui_modifica_grupa_student,
            "studenti_grupa": self.__ui_studenti.ui_cautare_studenti_grupa,

            "adauga_lab": self.__ui_laboratoare.ui_adauga_laborator,
            "afiseaza_lab": self.__ui_laboratoare.ui_afiseaza_laboratoare,
            "sterge_lab": self.__ui_laboratoare.ui_sterge_laborator,
            "modifica_desc_lab": self.__ui_laboratoare.ui_modifica_descriere_laborator,
            "modifica_deadline_lab": self.__ui_laboratoare.ui_modifica_deadline_laborator,

            "adauga_assign": self.__ui_assignment.ui_adauga_assignment,
            "afiseaza_assign": self.__ui_assignment.ui_afiseaza_assignment,
            "sterge_assign": self.__ui_assignment.ui_sterge_assignment,
            "noteaza_assign": self.__ui_assignment.ui_noteaza_assignment,

            "medii_ordonate_nume": self.__ui_assignment.ui_medii_ordonate_nume,
            "medii_ordonate_nota": self.__ui_assignment.ui_medii_ordonate_nota,
            "medii_ordonate_bubble": self.__ui_assignment.ui_medii_ordonate_bubble,
            "medii_ordonate_shell": self.__ui_assignment.ui_medii_ordonate_shell,
            "top20_medii": self.__ui_assignment.ui_get_top20_medii,
            "assign_ordonate": self.__ui_assignment.ui_sortare_assignment,

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
