class EroareRepository(Exception):
    """
    Clasa speciala de exceptii pentru erori de repository
    """
    def __init__(self, mesaj):
        super().__init__()
        self.__mesaj = mesaj