
class Student:
    def __init__(self, studentID, nume, grupa):
        """
        Definitia unui student
        :param studentID: int
        :param nume: string
        :param grupa: int
        """
        self.__data = {
            "studentID": studentID,
            "nume": nume,
            "grupa": grupa
        }

    def get_studentID(self):
        """
        Getter pentru studentID
        :return student.studentID
        """
        return self.__data["studentID"]

    def get_nume(self):
        """
        Getter pentru nume
        :return student.nume
        """
        return self.__data["nume"]

    def get_grupa(self):
        """
        Getter pentru grupa
        :return student.grupa
        """
        return self.__data["grupa"]

    def set_nume(self, nume):
        """
        Setter pentru numele unui student
        """
        self.__data["nume"] = nume

    def set_grupa(self, grupa):
        """
        Setter pentru grupa unui student
        """
        self.__data["grupa"] = grupa