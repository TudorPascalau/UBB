import random

from domain.automobil import Automobil
from repository.repository_automobile import EroareRepository


class ServiceAutomobile:
    def __init__(self, repo):
        self.__repo = repo

    def adauga_automobil(self, a_id, marca, pret, model, data_revizie_str):
        automobil = Automobil(a_id, marca, pret, model, data_revizie_str)
        self.__repo.adauga(automobil)

    def get_automobile_values(self):
        automobile = self.__repo.get_all()
        automobile_values = list(automobile.values())

        return automobile_values

    def genereaza_cuvant(self, cuvant_len):
        VOCALE = "aeiou"
        CONSOANE = "qwrtypsdfghjklzxcvbnm"

        incepe_vocala = random.choice([True, False])

        chars = []
        for i in range(cuvant_len):
            if i%2 == 0:
                urmeaza_vocala = incepe_vocala
            else:
                urmeaza_vocala = not incepe_vocala

            if urmeaza_vocala:
                chars.append(random.choice(VOCALE))
            else:
                chars.append(random.choice(CONSOANE))

        cuvant = ''.join(chars)
        return cuvant

    def genereaza_model(self):

        total_len = random.randint(8, 12)
        space_poz = random.randint(1,total_len-2)

        len1 = space_poz
        len2 = total_len - space_poz - 1

        cuvant1 = self.genereaza_cuvant(len1)
        cuvant2 = self.genereaza_cuvant(len2)

        marca = cuvant1 + " " + cuvant2
        return marca

    def sortare_pret_automobile(self):
        automobile_values = self.get_automobile_values()
        automobile_values.sort(key = lambda x: x.get_pret())

        return automobile_values

    def export_automobile_sortate(self, file_name):

        automobile_sortate = self.sortare_pret_automobile()
        file_path = file_name + ".csv"

        try:
            with open(file_path, "w") as file:
                for automobil in automobile_sortate:
                    automobil_line = f"{automobil.get_id()},{automobil.get_marca()},{automobil.get_pret()},{automobil.get_model()},{automobil.get_data_revizie_str()}\n"
                    file.write(automobil_line)

        except IOError:
            raise EroareRepository("Eroare la scrierea in fisier")
