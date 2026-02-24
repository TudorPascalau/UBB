from errors.eroare_ui import EroareUI


class UIAssignment:

    def __init__(self, service_assignment):
        self.__service_assignment = service_assignment

    def _ui_adauga_assignment(self, parametri_comanda):
        """
        Metoda care asigneza o problema
        :raises EroareUI, daca nu are 3 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 3:
            raise EroareUI("Numar parametri invalid!")

        try:
            studentID = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        try:
            numar_lab = int(parametri_comanda[1])
            numar_problema = int(parametri_comanda[2])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        numere_laborator ={
            "numar_lab": numar_lab,
            "numar_problema": numar_problema,
        }

        self.__service_assignment.adauga_assignment(studentID, numere_laborator)
        print("Problema a fost asignata")

    def _ui_notare_assignment(self, parametri_comanda):
        """
        Metoda care noteaza un assignment
        :raises EroareUI, daca nu are 4 parametri
                EroareUI, daca datele introduse sunt invalide
        """

        if len(parametri_comanda) != 4:
            raise EroareUI("Numar parametri invalid!")

        try:
            studentID = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        try:
            numar_lab = int(parametri_comanda[1])
            numar_problema = int(parametri_comanda[2])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        numere_laborator = {
            "numar_lab": numar_lab,
            "numar_problema": numar_problema,
        }

        try:
            nota = int(parametri_comanda[3])
        except ValueError:
            raise EroareUI("Nota invalide!")

        self.__service_assignment.notare_assignment(studentID, numere_laborator, nota)
        print("Assignmentul a fost notat")

    def _ui_sterge_assignment(self, parametri_comanda):
        """
        Metoda care sterge un assignment
        :raises EroareUI, daca nu are 3 parametri
                EroareUI, daca datele introduse sunt invalide
        """


        if len(parametri_comanda) != 3:
            raise EroareUI("Numar parametri invalid!")

        try:
            studentID = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        try:
            numar_lab = int(parametri_comanda[1])
            numar_problema = int(parametri_comanda[2])
        except ValueError:
            raise EroareUI("Numere laborator invalide!")

        numere_laborator = {
            "numar_lab": numar_lab,
            "numar_problema": numar_problema,
        }

        self.__service_assignment.sterge_assignment(studentID, numere_laborator)
        print("Assignmentul a fost sters")


    def _ui_afiseaza_assignments(self, parametri_comanda):

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        assignments = self.__service_assignment.access_assignments()

        if len(assignments) == 0:
            print("Nu exista assignmenturi!")
        else:
            print("Assignmenturi: \n")
            for assignment in assignments:
                print(f"Laboratorul: {assignment.get_numere_laborator_assign()["numar_lab"]}")
                print(f"Problema: {assignment.get_numere_laborator_assign()["numar_problema"]}")
                print(f"Studentul: {assignment.get_studentID_assign()}")

                if assignment.get_nota_assign() is None:
                    print(f"Nota: - ")
                else:
                    print(f"Nota: {assignment.get_nota_assign()}")