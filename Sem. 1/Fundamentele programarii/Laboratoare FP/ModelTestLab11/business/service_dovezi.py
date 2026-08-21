from domain.dovada import Dovada
from domain.suspect_dovezi_dto import SuspectDoveziDTO


class ServiceDovezi:

    def __init__(self, repo_dovezi):
        self.__repo_dovezi = repo_dovezi

    def adauga_dovada(self, id_dovada, descriere, data, tip, suspect):
        dovada = Dovada(id_dovada, descriere, data, tip, suspect)
        self.__repo_dovezi.adauga_dovada(dovada)

    def get_dovezi(self):
        return self.__repo_dovezi.get_all_dovezi()

    def get_dovezi_string(self, string):

        dovezi_string = []
        dovezi = self.get_dovezi()

        for dovada in dovezi.values():
            if string in dovada.get_suspect():
                dovezi_string.append(dovada)

        dovezi_string.sort(key=lambda x: x.get_tip())
        return dovezi_string

    def get_suspect_nr_dovezi(self):

        suspect_nr_dovezi = {}
        dovezi = self.get_dovezi()

        for dovada in dovezi.values():
            suspect = dovada.get_suspect()
            if suspect not in suspect_nr_dovezi:
                suspect_nr_dovezi[suspect] = 0

            suspect_nr_dovezi[suspect] += 1

        return suspect_nr_dovezi

    def get_suspect_dovezi_dtos(self):

        suspect_dovezi_dtos = []
        suspecti_nr_dovezi = self.get_suspect_nr_dovezi()

        for suspect in suspect_dovezi_dtos:
            nr_dovezi = suspecti_nr_dovezi[suspect]
            if nr_dovezi > 2:
                criminalitate = True
            else:
                criminalitate = False

            suspect_dovezi_dto = SuspectDoveziDTO(suspect, nr_dovezi, criminalitate)
            suspect_dovezi_dtos.append(suspect_dovezi_dto)

        return suspect_dovezi_dtos
