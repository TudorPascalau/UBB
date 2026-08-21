
class Website:

    def __init__(self, website_id, url, adress, holder, visitors):
        self.__website_id = website_id
        self.__url = url
        self.__adress = adress
        self.__holder = holder
        self.__visitors = visitors

    def get_id(self):
        """
        Getter pentru id website
        :return: id website
        """
        return self.__website_id

    def get_url(self):
        """
        Getter pentru url website
        :return: url website
        """
        return self.__url

    def get_adress(self):
        """
        Getter pentru adress website
        :return: adressa website
        """
        return self.__adress

    def get_holder(self):
        """
        Getter pentru holder website
        :return: holder website
        """
        return self.__holder

    def get_visitors(self):
        """
        Getter pentru visitors website
        :return: numar vizitatori
        """
        return self.__visitors

    def __str__(self):
        return f"Website no. {self.__website_id} {self.__url}, located at {self.__adress}, holder {self.__holder}, with {self.__visitors} visitors"