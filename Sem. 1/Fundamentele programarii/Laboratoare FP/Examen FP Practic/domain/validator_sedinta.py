import datetime


class EroareValidator(Exception):
    pass

class ValidatorSedinta:

    def valideaza_date_sedinta(self, data_str, ora_str, extraordinar):
        """
        Functie ce valideaza daca anumite date legate de o sedinta sunt corecte sau nu
        :param data_str: data sedintei, in format string
        :param ora_str: ora sedintei, in format string
        :param extraordinar: daca sedinta este normala sau extraordinara
        :return: True, daca datele sunt valide
        :raises: EroareValidator, daca datele nu sunt valide
        """
        eroare = ""

        try:
            data = datetime.datetime.strptime(data_str, "%d.%m")
        except ValueError:
            eroare += "Data nu este in formatul corect! \n"

        try:
            ora = datetime.datetime.strptime(ora_str, "%H:%M")
        except ValueError:
            eroare += "Ora nu este in formatul corect! \n"

        extraordinar = extraordinar.lower()
        if extraordinar not in ["normala", "extraordinara"]:
            eroare += "Nu ati specificat corect daca sedinta este normala sau extraordinara! \n"

        if eroare != "":
            raise EroareValidator(eroare)

        return True