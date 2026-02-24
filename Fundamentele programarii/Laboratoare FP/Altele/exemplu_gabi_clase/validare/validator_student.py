from exceptii.eroare_validator import EroareValidator


class ValidatorStudent:

    def valideaza_student(self,student):
        '''
        functie care valideaza studentul
        :param student: un student cu id int nume string si valoare float
        :return: -, daca studentul e valid
        :raises: EroareValidator cu mesajul:
                    id invalid!\n daca idul <0
                    nume invalid!\n daca numele este vid
                    valoare invalida!\n daca valoare <=0.0
        '''
        erori = ""
        if student.get_id_student()<0:
            erori += "id invalid!\n"
        if student.get_nume() == "":
            erori += "nume invalid!\n"
        if student.get_valoare() <=0.0:
            erori += "valoare invalida!\n"
        if len(erori)>0:
            raise EroareValidator(erori)