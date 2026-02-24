from domain.validator.validator_exception import ValidatorException


class StudentValidator:
    def __init__(self, student):
        self.__student = student

    def validate(self):
        for c in "1234567890":
            if c in self.__student.get_nume():
                raise ValidatorException("Numele nu este valid!")
