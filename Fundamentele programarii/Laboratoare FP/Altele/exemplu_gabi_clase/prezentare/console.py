from exceptii.eroare_repo import EroareRepo
from exceptii.eroare_ui import EroareUI
from exceptii.eroare_validator import EroareValidator


class Console:
    def __init__(self,service_studenti,service_materii,service_note):
        self.__service_studenti = service_studenti
        self.__service_materii = service_materii
        self.__service_note = service_note
        self.__comenzi = {
            "adauga_student":self.__ui_adauga_student
        }

    def __ui_adauga_student(self,parametri_comanda):
        if len(parametri_comanda) != 3:
            raise EroareUI("numar parametri invalid! trebuie 3")
        try:
            id_student = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("id numeric invalid! introduceti o valoare intreaga")
        nume = parametri_comanda[1]
        try:
            valoare = float(parametri_comanda[2])
        except ValueError:
            raise EroareUI("valore numeric invalida! introduceti o valoare float")
        self.__service_studenti.adauga_student(id_student, nume, valoare)

    def run(self):
        while True:
            text_comanda = input(">>>").strip().lower()
            if text_comanda == "":
                continue
            if text_comanda == "exit":
                print("sayonara,Karen!")
                return
            parti_comanda = text_comanda.split()
            nume_comanda = parti_comanda[0]
            parametri_comanda = parti_comanda[1:]
            if nume_comanda in self.__comenzi:
                try:
                    self.__comenzi[nume_comanda](parametri_comanda)
                except EroareUI as eroare_ui:
                    print(f"eroare ui: {eroare_ui}")
                except EroareValidator as eroare_validator:
                    print(f"eroare validator: {eroare_validator}")
                except EroareRepo as eroare_repo:
                    print(f"eroare repo: {eroare_repo}")
            else:
                print(f"{nume_comanda} is not a valid command")
