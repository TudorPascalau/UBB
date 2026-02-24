from exceptii.eroare_repo import EroareRepo


class RepositoryStudenti:
    def __init__(self):
        self.__studenti = {}

    def __len__(self):
        return len(self.__studenti)

    def adauga_student(self,student):
        id_student = student.get_id_student()
        if id_student in self.__studenti:
            raise EroareRepo("id student existent!")