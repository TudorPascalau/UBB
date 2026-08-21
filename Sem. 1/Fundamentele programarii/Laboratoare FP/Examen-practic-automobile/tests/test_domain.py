import unittest

from domain.automobil import Automobil


class TestDomain(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testDomain(self):
        id = 1
        marca = "Ford"
        pret = 20000
        model = "Mustang"
        data_revizie_str = "22:03:2025"

        automobil = Automobil(id, marca, pret, model, data_revizie_str)

        self.assertEqual(automobil.get_id(), id)
        self.assertEqual(automobil.get_marca(), marca)
        self.assertEqual(automobil.get_pret(), pret)
        self.assertEqual(automobil.get_model(), model)