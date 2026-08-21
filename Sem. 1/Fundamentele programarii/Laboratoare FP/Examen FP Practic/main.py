
import unittest

from domain.validator_sedinta import ValidatorSedinta
from repository.repository_sedinte import RepositorySedinte
from service.service_sedinte import ServiceSedinte
from ui.ui import UISedinta

# Definim obiectele ce tin de testare
loader = unittest.TestLoader()
suite = loader.discover("tests")
runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite) #Rulam toate testele

#Crearea obiectelor ce tin de repository
file_path = r"C:\Users\tudor\Desktop\Examen FP Practic\sources\sedinte.txt"
repository = RepositorySedinte(file_path)

#Crearea obiectelor ce tin de service
validator = ValidatorSedinta()
service = ServiceSedinte(repository, validator)

#Crearea obiectelor ce tin de UI
ui = UISedinta(service)

ui.run()