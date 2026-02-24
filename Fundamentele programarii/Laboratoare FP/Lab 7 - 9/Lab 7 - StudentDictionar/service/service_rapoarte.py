#from domain.student_nota import StudentNota

class ServiceRapoarte:

    def __init__(self, service_studenti, service_laboratoare, service_assignment):
        self.__service_studenti = service_studenti
        self.__service_laboratoare = service_laboratoare
        self.__service_assignment = service_assignment

    def __get_studenti_si_note_laborator(self, numere_laborator):
        """
        Metoda care genereaza lista tuplu student/nota pentru un laborator dat
        :param numere_laborator: numerele laboratorului
        :return: lista student/nota
        """

        rezultat = []

        assignments = self.__service_assignment.access_assignments()
        for assignment in assignments:
            if assignment.get_numere_laborator_assign() == numere_laborator:
                student = self.__service_studenti.get_student_by_id(assignment.get_studentID_assign())
                nota = assignment.get_nota_assign()

                #student_nota = StudentNota
                rezultat.append((student, nota))

        return rezultat

    def get_studenti_ordonat_alfabetic(self, numere_laborator):
        """
        Metoda care genereaza lista sortata dupa nume a studentilor asignati la un anumit laborator
        :param numere_laborator: numerele laboratorului
        :return: lista sortata
        """
        studenti_si_note = self.__get_studenti_si_note_laborator(numere_laborator)
        studenti_si_note.sort(key=lambda pair: pair[0].get_nume())
        return studenti_si_note

    def get_studenti_ordonat_nota(self, numere_laborator):
        """
        Metoda care genereaza lista sortata dupa note a studentilor asignati la un anumit laborator
        :param numere_laborator: numerele laboratorului
        :return: lista sortata
        """
        studenti_si_note = self.__get_studenti_si_note_laborator(numere_laborator)
        studenti_si_note.sort(key=lambda pair: pair[1], reverse=True)  # pair[1] = nota
        return studenti_si_note

    def get_top20procent_medie(self):
        """
        Metoda care genereaza lista a primilor 20% de elevi dupa medie
        :return: lista generata
        """
        assignments = self.__service_assignment.access_assignments()

        # statistica[studentID] <=> [suma notelor, numar note]
        statistica = {}

        for assignment in assignments:
            studentID = assignment.get_studentID_assign()
            nota = assignment.get_nota_assign()
            if studentID not in statistica:
                statistica[studentID] = [0, 0]
            statistica[studentID][0] += nota
            statistica[studentID][1] += 1

        # construim lista (student, medie)
        rezultate = []
        for studentID, (suma, cnt) in statistica.items():
            medie = suma / cnt
            student = self.__service_studenti.get_student_by_id(studentID)
            rezultate.append((student, medie))

        # ordonăm descrescător după medie
        rezultate.sort(key=lambda pair: pair[1], reverse=True)

        # calculăm 20%
        n = len(rezultate)
        k = max(1, n * 20 // 100)  # cel puțin 1 student
        return rezultate[:k]

    def get_top5_medie(self):
        """
        Metoda care genereaza lista primilor 5% elevi dupa medie
        :return: lista generata
        """

        #Analaog top20%
        assignments = self.__service_assignment.access_assignments()

        statistica = {}

        for assignment in assignments:
            studentID = assignment.get_studentID_assign()
            nota = assignment.get_nota_assign()
            if studentID not in statistica:
                statistica[studentID] = [0, 0]
            statistica[studentID][0] += nota
            statistica[studentID][1] += 1

        rezultate = []
        for studentID, (suma, cnt) in statistica.items():
            medie = suma / cnt
            student = self.__service_studenti.get_student_by_id(studentID)
            rezultate.append((student, medie))

        rezultate.sort(key = lambda pair: pair[1], reverse=True)
        return rezultate[:5]
