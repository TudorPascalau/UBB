
class VisitorsPred:

    def __init__(self, sites, total_visitors):
        self.__sites = sites
        self.__total_visitors = total_visitors

    def get_sites(self):
        """
        Getter pentru lista site-uri
        :return: lista site-uri
        """
        return self.__sites

    def get_total_visitors(self):
        """
        Getter pentru lista total-visitors
        :return: total-visitors
        """
        return self.__total_visitors

    def __str__(self):
        return f"Lista cu site-uri prefixate {self.__sites}, cu totaul de vizitatori prezis la {self.__total_visitors}"