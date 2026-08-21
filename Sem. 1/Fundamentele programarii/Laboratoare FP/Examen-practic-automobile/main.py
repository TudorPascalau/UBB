import unittest

from repository.repository_automobile import RepositoryAutomobile
from service.service_automobile import ServiceAutomobile
from ui.ui import UIAutomobile

loader = unittest.TestLoader()
suite = loader.discover("tests")
runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite)

file_path = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Examen-practic-automobile\sources\automobile.txt"
repo = RepositoryAutomobile(file_path)

service = ServiceAutomobile(repo)
ui = UIAutomobile(service)

ui.run()