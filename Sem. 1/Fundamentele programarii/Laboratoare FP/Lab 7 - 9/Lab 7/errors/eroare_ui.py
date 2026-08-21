class EroareUI(Exception):
    """
    Clasa speciala de exceptii pentru erori de UI
    """
    def __init__(self, mesaj):
        super().__init__()
        self.__mesaj = mesaj