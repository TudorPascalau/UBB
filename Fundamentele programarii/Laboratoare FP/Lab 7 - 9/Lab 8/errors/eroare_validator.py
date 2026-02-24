class EroareValidator(Exception):
    """
    Clasa speciala de exceptii pentru erori de validare
    """
    def __init__(self, mesaj):
        super().__init__()
        self.__mesaj = mesaj