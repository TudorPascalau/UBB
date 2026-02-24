import datetime
import unittest

from domain.validator_sedinta import ValidatorSedinta, EroareValidator
from repository.repository_sedinte import RepositorySedinte, EroareRepository
from service.service_sedinte import ServiceSedinte


class TestService(unittest.TestCase):

    def setUp(self):
        file_path = r"C:\Users\tudor\Desktop\Examen FP Practic\sources\test.txt"
        self.repository = RepositorySedinte(file_path)

        self.validator = ValidatorSedinta()
        self.service = ServiceSedinte(self.repository, self.validator)

        self.data_str = "20.02"
        self.ora_str = "08:00"
        self.subiect = "Discutie"
        self.extraordinar = "normala"


    def tearDown(self):
        self.repository.clear_repo()

    def testAdaugaService(self):
        """
        Testare adaugare prin service
        """

        self.assertEqual(len(self.repository), 0)

        self.service.adauga_sedinta(self.data_str, self.ora_str, self.subiect, self.extraordinar)
        self.assertEqual(len(self.repository), 1)

        with self.assertRaises(EroareRepository):
            self.service.adauga_sedinta(self.data_str, self.ora_str, self.subiect, self.extraordinar)

        data_str_invalid = "invalid"
        with self.assertRaises(EroareValidator):
            self.service.adauga_sedinta(data_str_invalid, self.ora_str, self.subiect, self.extraordinar)

    def testGetListaSedinte(self):
        """
        Testare get lista sedinte
        """

        sedinte = self.service.get_lista_sedinte()
        self.assertEqual(sedinte, [])

        self.service.adauga_sedinta(self.data_str, self.ora_str, self.subiect, self.extraordinar)
        sedinte = self.service.get_lista_sedinte()
        self.assertEqual(sedinte[0].get_data_str(), self.data_str)

    def testGetSedinteZi(self):
        """
        Testare get sedinte zi
        """

        self.service.adauga_sedinta(self.data_str, self.ora_str, self.subiect, self.extraordinar)
        zi = datetime.datetime.strptime(self.data_str, "%d.%m")

        sedinte_zi = self.service.get_sedinte_zi(zi)
        self.assertEqual(len(sedinte_zi), 1)
        self.assertEqual(sedinte_zi[0].get_data_str(), self.data_str)

        zi = datetime.datetime.strptime("23.02", "%d.%m")
        sedinte_zi = self.service.get_sedinte_zi(zi)
        self.assertEqual(len(sedinte_zi), 0)


    def testGetSedinteZiOra(self):
        """
        Testare get sedinte zi sortate ora
        """

        self.service.adauga_sedinta(self.data_str, self.ora_str, self.subiect, self.extraordinar)
        zi = datetime.datetime.strptime(self.data_str, "%d.%m")

        sedinte_zi = self.service.get_sedinte_zi_ora(zi)
        self.assertEqual(len(sedinte_zi), 1)
        self.assertEqual(sedinte_zi[0].get_data_str(), self.data_str)

        subiect = "altceva"
        ora = "12:30"
        self.service.adauga_sedinta(self.data_str, ora, subiect, self.extraordinar)

        sedinte_zi = self.service.get_sedinte_zi_ora(zi)
        self.assertEqual(len(sedinte_zi), 2)

        self.assertEqual(sedinte_zi[0].get_ora_str(), self.ora_str)
        self.assertEqual(sedinte_zi[1].get_ora_str(), ora)

    def testFiltru(self):

        self.assertEqual(self.service.get_filtru(), False)

        data_str = "30.03"
        data = datetime.datetime.strptime(data_str, "%d.%m")

        self.service.seteaza_filtru(data)
        self.assertEqual(self.service.get_filtru(), data)
