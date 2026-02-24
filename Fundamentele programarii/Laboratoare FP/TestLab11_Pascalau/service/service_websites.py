from domain.visitors_pred import VisitorsPred
from domain.website import Website


class ServiceWebsites:

    def __init__(self, repo_websites, validator_websites):
        self.__repo_websites = repo_websites
        self.__validator_websites = validator_websites

    def adauga_website(self, website_id, url, adress, holder, visitors):
        """
        Metoda care adauga un website din datele sale
        :param website_id: id website
        :param url: url website
        :param adress: adresa fizica website
        :param holder: detinator website
        :param visitors: vizitatori website
        """
        website = Website(website_id, url, adress, holder, visitors)
        self.__validator_websites.valideaza_website(website)
        self.__repo_websites.adauga_website(website)

    def is_prefix(self, prefix, sir):
        """
        Metoda interna folosita pentru determinarea daca un string este prefix pentru alt sir
        :param prefix: string-ul prefix
        :param sir: string-ul pe care testam
        :return True: daca da
                False, daca nu
        """

        lungime_sir = len(sir)
        for lungime_prefix in range(lungime_sir):
            if prefix == sir[:lungime_prefix]:
                return True

        return False

    def calc_vizitatori_zile(self, zile, website):
        """
        Metoda care calculeaza numarul prezis de vizitatori al unui site intr-un numar de zile
        :param zile: numarul de zile
        :param website: website-ul
        :return numar_vizitatori: float, reprezentand numarul de zile
        """

        numar_vizitatori = website.get_visitors()
        for zi in range(zile):
            numar_vizitatori = float(numar_vizitatori*110/100)

        return numar_vizitatori

    def predict_visitors(self, zile, prefix):
        """
        Metoda care prezice cati vizitatori au site-urile cu un prefix dat intr-un numar de zile
        :param zile: numarul de zile in care ar fi site-ul vizitat, cu rata de crestere 10%
        :param prefix: prefixul site-urilor vizitate
        :return visitors_pred: obiect VisitorsPred, care contine site-urile cu prefix, respectiv total de vizitatori
        """

        websites = self.__repo_websites.get_all_websites()
        websites_prefix = []
        total_visitors = 0

        for website in websites.values():
            if self.is_prefix(prefix, website.get_url()) == True:
                websites_prefix.append(website.get_url())
                total_visitors += self.calc_vizitatori_zile(zile, website)

        visitors_pred = VisitorsPred(websites_prefix, total_visitors)
        return visitors_pred