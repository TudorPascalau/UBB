from errors.eroare_valid import EroareValidator


class ValidatorWebsite:

    def __init__(self):
        pass

    def valideaza_website(self, website):
        """
        Metoda care valideaza un website
        :param website: website-ul de validat
        :return - :, daca website e valid
        :raises EroareValidator:, daca website nu e valid
        """

        website_id = website.get_id()
        if website_id == 0:
            raise EroareValidator("Id invalid!")

        url = website.get_url()
        if url == "":
            raise EroareValidator("Url invalid!")

        adress = website.get_adress()
        if adress == "":
            raise EroareValidator("Adresa invalida!")

        holder = website.get_holder()
        if holder == "":
            raise EroareValidator("Holder invalid!")

        visitors = website.get_visitors()
        if visitors == 0:
            raise EroareValidator("Numar visitors invalid!")
