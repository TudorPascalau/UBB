import unittest


class TestFile(unittest.TestCase):

    def testAccessFisier(self):
        """
        Testare accesarea / scrierea / citirea dintr-un fisier
        :return:
        """
        temp_path = r"C:\Users\tudor\Desktop\Examen FP Practic\sources\temp.txt"

        with open(temp_path, "w") as file:
            file.write("Testing")

        with open(temp_path, "r") as file:
            text = file.read()

        self.assertEqual(text, "Testing")