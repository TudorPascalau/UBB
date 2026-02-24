import unittest

from domain.website import Website
from errors.eroare_repo import EroareRepository
from errors.eroare_valid import EroareValidator
from repository.repo_website import RepositoryWebsites, RepositoryWebsitesFile
from service.service_websites import ServiceWebsites
from validator.validator_website import ValidatorWebsite

#Clasa de teste pentru domain website
class TesteDomainWebsite(unittest.TestCase):

    def setUp(self):
        pass

    def test_creaza_website(self):
        """
        Metoda care testeaza crearea unui website
        """
        id = 1
        url ="google.com"
        adress = "Mihai Viteazul"
        holder = "Ion Popescu"
        visitors = 20

        website = Website(id, url, adress, holder, visitors)

        self.assertEqual(website.get_id(), id)
        self.assertEqual(website.get_url(), url)
        self.assertEqual(website.get_adress(), adress)
        self.assertEqual(website.get_holder(), holder)
        self.assertEqual(website.get_visitors(), visitors)

    def tearDown(self):
        pass

# Clasa de teste pentru validare website
class TesteValidatorWebsite(unittest.TestCase):

    def setUp(self):
        self.__website1 = Website(1,"google.com","Mihai Viteazul","Ion Popescu",20 )
        self.__website2 = Website(1,"google.com","Mihai Viteazul","",20 )
        self.__validator_test = ValidatorWebsite()

    def test_valideaza_website(self):
        """
        Metoda care testeaza validarea unui website
        """

        self.assertIs(self.__validator_test.valideaza_website(self.__website1), None)
        self.assertRaises(EroareValidator, self.__validator_test.valideaza_website, self.__website2)

    def tearDown(self):
        del self.__website1
        del self.__website2

# Clasa de teste pentru repository website
class TesteRepositoryWebsite(unittest.TestCase):

    def setUp(self):
        self.__repo_teste = RepositoryWebsites()
        self.__website = Website(1,"google.com","Mihai Viteazul","Ion Popescu",20 )

    def test_adauga_website(self):
        """
        Metoda care testeaza adaugarea unui website in repo memorie
        """

        self.assertEqual(len(self.__repo_teste), 0)
        self.__repo_teste.adauga_website(self.__website)

        self.assertEqual(len(self.__repo_teste), 1)
        self.assertRaises(EroareRepository, self.__repo_teste.adauga_website, self.__website)

    def test_get_all_websites(self):

        self.assertEqual(len(self.__repo_teste), 0)
        self.assertEqual(len(self.__repo_teste.get_all_websites()), 0)

        self.__repo_teste.adauga_website(self.__website)
        self.assertEqual(len(self.__repo_teste.get_all_websites()), 1)

        self.assertEqual(self.__repo_teste.get_all_websites()[1].get_id(), 1)

    def tearDown(self):
        del self.__website
        del self.__repo_teste

class TesteRepoFile(unittest.TestCase):

    def setUp(self):
        self.__path = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\TestLab11_Pascalau\teste\test_websites.txt"
        self.__repo_test = RepositoryWebsitesFile(self.__path)

    def test_read_from_file(self):
        """
        Metoda care testeaza ca se citeste dintr-un fisier
        """

        websites = self.__repo_test.get_all_websites()
        self.assertEqual(len(websites), 1)

    def tearDown(self):
        del self.__repo_test

class TesteServiceWebsite(unittest.TestCase):

    def setUp(self):
        self.__repo_teste = RepositoryWebsites()
        self.__validator_teste = ValidatorWebsite()
        self.__service_teste = ServiceWebsites(self.__repo_teste, self.__validator_teste)

    def test_adauga_website(self):
        """
        Metoda care testeaza adaugarea de website din service
        """

        self.assertEqual(len(self.__repo_teste), 0)
        self.__service_teste.adauga_website(1,"google.com","Mihai Viteazul","Ion Popescu",20)

        self.assertEqual(len(self.__repo_teste), 1)
        self.assertRaises(EroareRepository, self.__service_teste.adauga_website, 1,"google.com","Mihai Viteazul","Ion Popescu",20)

    def test_is_prefix(self):
        """
        Metoda care testeaza metoda interna de testare prefix
        """

        self.assertIs(self.__service_teste.is_prefix("goo","google.com"), True)
        self.assertIs(self.__service_teste.is_prefix("boo", "google.com"), False)

    def test_calc_vizitatori_zile(self):

        website = Website(1,"google.com","Mihai Viteazul","Ion Popescu",20)

        self.assertEqual(self.__service_teste.calc_vizitatori_zile(1,website), 22)
        self.assertEqual(self.__service_teste.calc_vizitatori_zile(2, website), 24.2)

    def test_predict_visitors(self):

        self.__service_teste.adauga_website(1,"google.com","Mihai Viteazul","Ion Popescu",20)

        visitors_pred = self.__service_teste.predict_visitors(2, "goo")
        self.assertEqual(visitors_pred.get_sites(), ["google.com"])
        self.assertEqual(visitors_pred.get_total_visitors(), 24.2)

    def tearDown(self):
        del self.__repo_teste
        del self.__validator_teste
        del self.__service_teste
