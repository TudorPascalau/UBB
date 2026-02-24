import unittest

from repository.repository_automobile import RepositoryAutomobile, EroareRepository
from service.service_automobile import ServiceAutomobile


class TestService(unittest.TestCase):
    def setUp(self):
        file_path = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Examen-practic-automobile\sources\automobile_test.txt"
        self.repo = RepositoryAutomobile(file_path)
        self.repo.clear()

        self.service = ServiceAutomobile(self.repo)

        self.a_id = 1
        self.marca = "Ford"
        self.pret = 20000
        self.model = "Mustang"
        self.data_revizie_str = "22:03:2025"

    def tearDown(self):
        pass

    def testAdaugaAutomobil(self):
        self.assertEqual(len(self.repo),0)

        self.service.adauga_automobil(self.a_id, self.marca, self.pret, self.model, self.data_revizie_str)
        self.assertEqual(len(self.repo),1)

        with self.assertRaises(EroareRepository):
            self.service.adauga_automobil(self.a_id, self.marca, self.pret, self.model, self.data_revizie_str)


    def testGetAutomobileValues(self):
        self.assertEqual(len(self.repo),0)

        self.service.adauga_automobil(self.a_id, self.marca, self.pret, self.model, self.data_revizie_str)
        automobile_values = self.service.get_automobile_values()

        self.assertEqual(automobile_values[0].get_id(), self.a_id)
        self.assertEqual(automobile_values[0].get_marca(), self.marca)

    def testGenereazaModel(self):

        model = self.service.genereaza_model()

        self.assertLessEqual(len(model),12)
        self.assertGreaterEqual(len(model),8)

        self.assertIn(" ", model)