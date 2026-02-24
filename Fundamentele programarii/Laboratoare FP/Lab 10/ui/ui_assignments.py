from utils.eroare_ui import EroareUI


class UIAssignments:

    def __init__(self, service_assignment):
        self.__service_assignment = service_assignment

    def ui_adauga_assignment(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru adaugare assignment
        :raises EroareUI, daca comanda nu are 3 parametri
                EroareUI, daca datele despre student sunt invalide
        """
        if len(parametri_comanda) != 3:
            raise EroareUI("Numar parametri invalid!")

        try:
            student_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid! Trebuie intreg")

        try:
            numar_lab = int(parametri_comanda[1])
            numar_prob = int(parametri_comanda[2])

            lab_id = (numar_lab, numar_prob)
        except ValueError:
            raise EroareUI("Id laborator invalid")

        self.__service_assignment.adauga_assignment(student_id, lab_id)
        print("Assignment adaugat cu succes")

    def ui_afiseaza_assignment(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru afisare assignments
        :raises EroareUI, daca comanda are vreun parametru
        """
        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        assignments = self.__service_assignment.get_assignments()

        if len(assignments) == 0:
            print("Nu exista assignments!")
        else:
            print("Assignments: \n")
            for assignment in assignments.values():
                print(assignment)

    def ui_sterge_assignment(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru stergere assignment
        :raises EroareUI, daca comanda nu are 1 parametru
                EroareUI, daca parametrul dat este invalid
        """
        if len(parametri_comanda) != 1:
            raise EroareUI("Numar parametri invalid!")

        try:
            assignment_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        self.__service_assignment.sterge_assignment(assignment_id)
        print("Assignment a fost sters cu succes!")

    def ui_noteaza_assignment(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru notare assignment
        :raises EroareUI, daca comanda nu are 2 parametri
                EroareUI, daca parametrii dati sunt invalizi
        """

        try:
            assignment_id = int(parametri_comanda[0])
        except ValueError:
            raise EroareUI("Id numeric invalid!")

        try:
            nota = float(parametri_comanda[1])
        except ValueError:
            raise EroareUI("Id laborator invalid!")

        self.__service_assignment.noteaza_assignment(assignment_id, nota)
        print("Assignment a fost notat cu succes!")

    def ui_medii_ordonate_nume(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru medii ordonate
        :raises: EroareUI, daca comanda nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        medii = self.__service_assignment.get_medii_ordonate_nume()
        for medie in medii:
            print(medie + '\n')

    def ui_medii_ordonate_nota(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru medii ordonate
        :raises: EroareUI, daca comanda nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        medii = self.__service_assignment.get_medii_ordonate_nota()
        for medie in medii:
            print(str(medie) + '\n')

    def ui_medii_ordonate_bubble(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru medii ordonate
        :raises: EroareUI, daca comanda nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        medii = self.__service_assignment.get_medii_ordonate_bubble()
        for medie in medii:
            print(str(medie) + '\n')

    def ui_medii_ordonate_shell(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru medii ordonate
        :raises: EroareUI, daca comanda nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        medii = self.__service_assignment.get_medii_ordonate_shell()
        for medie in medii:
            print(str(medie) + '\n')

    def ui_get_top20_medii(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru medii ordonate
        :raises: EroareUI, daca comanda nu are 0 parametri
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        medii = self.__service_assignment.get_top20_medii()
        for medie in medii:
            print(str(medie) + "\n")

    def ui_sortare_assignment(self, parametri_comanda):
        """
        Metoda care faciliteaza UI pentru sortarea de la lab
        """

        if len(parametri_comanda) != 0:
            raise EroareUI("Numar parametri invalid!")

        assignments = self.__service_assignment.get_assignments_ordonate()
        for assignment in assignments:
            print(assignment)