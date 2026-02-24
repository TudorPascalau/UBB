from errors.eroare_validator import EroareValidator


class ValidatorLaborator:

    def valideaza_laborator(self,laborator):
        """
        Metoda care valideaza laboratorul
        :param laborator:
        :return: - daca laboratorul este valid
        :raises EroareValidator cu mesajul
                numar laborator invalid!\n, daca numar lab <0
                numar problema invalida!\n, daca numar probleam <0
                descriere invalida!\n daca descriere == ""
                an deadline invalid!\n daca an in trecut
                luna deadline invalida!\n, daca luna in trecut
                zi deadline invalida!\n, daca zi in trecut
        """

        erori = ""
        if laborator.get_numar_laborator() <= 0:
            erori += "numar laborator invalid!\n"
        if laborator.get_numar_problema() <= 0:
            erori += "numar problema invalida!\n"
        if laborator.get_descriere_laborator() == "":
            erori += "descriere invalida!\n"
        if laborator.get_an_deadline() < 2025:
            erori += "an deadline invalid!\n"
        if not 1 <= laborator.get_luna_deadline() <= 12:
            erori += "luna deadline invalida!\n"
        if not 1 <= laborator.get_zi_deadline() <= 31:
            erori += "zi deadline invalida!\n"

        if len(erori) > 0:
            raise EroareValidator(erori)
