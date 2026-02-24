
class SuspectDoveziDTO:

    def __init__(self, suspect, nr_dovezi, criminalitate):
        self.__suspect = suspect
        self.__nr_dovezi = nr_dovezi
        self.__criminalitate = criminalitate

    def get_suspect(self):
        return self.__suspect

    def get_nr_dovezi(self):
        return self.__nr_dovezi

    def get_criminalitate(self):
        return self.__criminalitate