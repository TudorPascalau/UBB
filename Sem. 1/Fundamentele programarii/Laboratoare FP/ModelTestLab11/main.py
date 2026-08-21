import unittest

from business.service_dovezi import ServiceDovezi
from repository.repo_dovezi import RepositoryDovezi, RepositoryDoveziFile
from ui.console import Console
from ui.ui_dovezi import UIDovezi

loader = unittest.TestLoader()
suite = loader.discover("teste")
runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite)

dovezi_filepath = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\ModelTestLab11\sources\dovezi.txt"
repo_dovezi = RepositoryDoveziFile(dovezi_filepath)
service_dovezi = ServiceDovezi(repo_dovezi)
ui_dovezi = UIDovezi(service_dovezi)

console = Console(ui_dovezi)

console.run()