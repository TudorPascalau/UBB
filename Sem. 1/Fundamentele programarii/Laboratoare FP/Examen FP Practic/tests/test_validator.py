
import unittest

from domain.validator_sedinta import ValidatorSedinta, EroareValidator


class TestValidator(unittest.TestCase):

    def setUp(self):
        self.validator = ValidatorSedinta()

    def tearDown(self):
        pass

    def testValidator(self):
        """
        Testare validator pentru date sedinta
        """
        data_str = "20.02"
        ora_str = "08:00"
        extraordinar = "normala"

        self.assertEqual(self.validator.valideaza_date_sedinta(data_str, ora_str, extraordinar),True)

        data_str_invalid = "20/03"
        with self.assertRaises(EroareValidator):
            self.validator.valideaza_date_sedinta(data_str_invalid, ora_str, extraordinar)

        ora_str_invalid = "altceva"
        with self.assertRaises(EroareValidator):
            self.validator.valideaza_date_sedinta(data_str, ora_str_invalid, extraordinar)

        extraordinar_invalid = "normal"
        with self.assertRaises(EroareValidator):
            self.validator.valideaza_date_sedinta(data_str, ora_str, extraordinar_invalid)