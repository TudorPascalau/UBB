import datetime
import unittest

from domain.sedinta import Sedinta


class TestDomain(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testCreazaSedinta(self):
        """
        Testare crearea unui obiect de tip sedinta
        """

        data_str = "20.02"
        data = datetime.datetime.strptime(data_str, "%d.%m")
        ora_str = "08:00"
        ora = datetime.datetime.strptime(ora_str, "%H:%M")
        subiect = "Discutie"
        extraordinar = "normala"

        s_id = (subiect, extraordinar)

        sedinta = Sedinta(s_id, data_str, ora_str, subiect, extraordinar)

        self.assertEqual(sedinta.get_id(), s_id)
        self.assertEqual(sedinta.get_data_str(), data_str)
        self.assertEqual(sedinta.get_data(), data)
        self.assertEqual(sedinta.get_ora(), ora)
        self.assertEqual(sedinta.get_ora_str(), ora_str)
        self.assertEqual(sedinta.get_subiect(), subiect)
        self.assertEqual(sedinta.get_extraordinar(), extraordinar)