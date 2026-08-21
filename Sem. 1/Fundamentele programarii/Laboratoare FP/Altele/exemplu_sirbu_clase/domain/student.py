class Student:
    def __init__(self, id, nume):
        self.__id = id
        self.__nume = nume

    def get_nume(self):
        return self.__nume

    def set_nume(self, value):
        self.__nume = value

    def get_id(self):
        return self.__id
