from utils.eroare_ui import EroareUI


class UIStudenti:

    def __init__(self, service_studenti):
        """
        UI pentru gestionare studenti
        """
        self.__service_studenti = service_studenti

    def ui_adauga_student(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru adaugare student
        :raises EroareUI, daca comanda nu are 3 parametri
                EroareUI, daca datele despre student sunt invalide
        """
        if len(parametri_comanda) != 3:
            raise EroareUI("Numar parametri invalid!")

        try:
            student_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid! Trebuie intreg")

        nume = parametri_comanda[1]

        try:
            grupa = int(parametri_comanda[2])
        except ValueError:
            raise EroareUI("Grupa invalida! Trebuie sa aiba 3 cifre")

        self.__service_studenti.adauga_student(student_id, nume, grupa)
        print("Student adaugat cu succes")

    def ui_afiseaza_studenti(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru afisare studenti
        :raises EroareUI, daca comanda are vreun parametru
        """
        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        studenti = self.__service_studenti.get_studenti()

        if len(studenti) == 0:
            print("Nu exista studenti!")
        else:
            print("Studenti: \n")
            for student in studenti.values():
                print(student)

    def ui_sterge_student(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru stergere student
        :raises EroareUI, daca comanda nu are 1 parametru
                EroareUI, daca studentID dat este invalid
        """
        if len(parametri_comanda) != 1:
            raise EroareUI("Numar parametri invalid!")

        try:
            student_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        self.__service_studenti.sterge_student(student_id)
        print("Studentul a fost sters cu succes!")

    def ui_modifica_nume_student(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru modificare nume student
        :raises EroareUI, daca comanda nu are 2 parametri
                EroareUI, daca studentID dat este invalid
        """
        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalid!")
        try:
            student_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        nume = parametri_comanda[1]

        self.__service_studenti.modifica_nume_student(student_id, nume)
        print("Nume modificat cu succes!")

    def ui_modifica_grupa_student(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru modificare grupa student
        :raises EroareUI, daca comanda nu are 2 parametri
                EroareUI, daca studentID dat este invalid
                EroareUI, daca grupa data este invalid
        """
        if len(parametri_comanda) != 2:
            raise EroareUI("Numar parametri invalid!")
        try:
            student_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        try:
            grupa = int(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Grupa invalida!")

        self.__service_studenti.modifica_grupa_student(student_id, grupa)
        print("Grupa modificata cu succes!")

    def ui_cautare_studenti_grupa(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru cautare studenti dintr-o anumita grupa
        :raises EroareUI, daca comanda nu are 1 parametru
                EroareUI, daca grupa data data este invalid
        """
        if len(parametri_comanda) != 1:
            raise EroareUI("Numar parametri invalid!")

        try:
            grupa = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Grupa invalida!")

        studenti_grupa = self.__service_studenti.gaseste_studenti_grupa(grupa)
        for student in studenti_grupa:
            print(student)
