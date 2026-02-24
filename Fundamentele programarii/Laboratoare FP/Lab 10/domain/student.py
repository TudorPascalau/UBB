
class Student:

    def __init__(self, student_id, nume, grupa):
        self.__id = student_id
        self.__nume = nume
        self.__grupa = grupa

    def get_student_id(self):
        """
        Getter pentru id student
        """
        return self.__id

    def get_nume(self):
        """
        Getter pentru nume student
        """
        return self.__nume

    def get_grupa(self):
        """
        Getter pentru grupa student
        """
        return self.__grupa

    def set_nume(self, nume):
        """
        Setter pentru nume student
        """
        self.__nume = nume

    def set_grupa(self, grupa):
        """
        Setter pentru grupa student
        """
        self.__grupa = grupa

    def __str__(self):
        return f"Studentul {self.get_nume()}, ID: {self.get_student_id()}, Grupa {self.get_grupa()}"