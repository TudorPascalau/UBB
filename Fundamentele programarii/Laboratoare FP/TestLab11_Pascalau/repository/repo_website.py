from domain.website import Website
from errors.eroare_repo import EroareRepository

# Repository din memorie
class RepositoryWebsites:

    def __init__(self):
        self.__repo_websites = {}

    def __len__(self):
        return len(self.__repo_websites)

    def adauga_website(self, website):
        """
        Metoda care adauga un website in repo memorie
        :param website: website de adaugat
        :raises EroareRepository: daca id website deja exista
        """
        website_id = website.get_id()
        if website_id in self.__repo_websites:
            raise EroareRepository("Id website deja existent!")

        self.__repo_websites[website_id] = website

    def get_all_websites(self):
        """
        Metoda care returneaza toate websiturile
        :return: dictionarul de websiteuri
        """
        return self.__repo_websites


# Repository fisier
class RepositoryWebsitesFile(RepositoryWebsites):

    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_file()

    def adauga_website(self, website):
        """
        Metoda care adauga un website in repo fisier
        :param website: website de adaugat
        """

        super().adauga_website(website)
        self.__store()

    def get_all_websites(self):
        """
        Metoda care returneaza toate websiturile din fisier
        :return: dictionarul de website uri
        """
        return super().get_all_websites()

    def __load_file(self):
        """
        Metoda care citeste din fisier website urile
        :raises EroareRepository: daca nu s-a putut citi din fisier
        """
        try:
            with open(self.__filename, "r") as file:
                linii = file.readlines()
                for linie in linii:
                    linie = linie.strip()
                    parti = linie.split(",")

                    id = int(parti[0])
                    url = parti[1]
                    adress = parti[2]
                    holder = parti[3]
                    visitors = int(parti[4])

                    website = Website(id, url, adress, holder, visitors)
                    super().adauga_website(website)

        except FileNotFoundError:
            raise EroareRepository("Eroare la citirea din fisier!")

    def __store(self):
        """
        Metoda care scrie in fisier toate websiteurile
        :raises EroareRepository: daca nu s-a putut scrie in fisier:
        """
        try:
            with open(self.__filename, "w") as file:
                websites = self.get_all_websites()
                for website in websites.values():
                    website_str = ( str(website.get_id()) + ',' + website.get_url() + ',' + website.get_adress() + ','
                                    + website.get_holder() + ',' + str(website.get_visitors()) )

                    file.write(website_str + '\n')

        except IOError:
            raise EroareRepository("Eroare la scrierea in fisier!")