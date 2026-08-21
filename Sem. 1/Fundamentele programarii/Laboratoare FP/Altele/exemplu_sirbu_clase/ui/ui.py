from domain.validator.validator_exception import ValidatorException
from repository.repository_exception import RepositoryException


class UI:
    def __init__(self, service):
        self.__service = service

    def read_data_type(self, text, data_type):
        while True:
            data = input(text)
            try:
                data = data_type(data)
                return data
            except ValueError:
                print("Invalid type!")

    def adauga(self):
        id = self.read_data_type("Da id: ", int)
        nume = self.read_data_type("Da nume: ", str)
        self.__service.add(id, nume)

    def start(self):
        while True:
            comanda = self.read_data_type("Da comanda: ", int)
            try:
                if comanda == 1:
                    self.adauga()
                elif comanda == 2:
                    break
            except (RepositoryException, ValidatorException) as e:
                print("Execution error")
                print(e.get_message())
