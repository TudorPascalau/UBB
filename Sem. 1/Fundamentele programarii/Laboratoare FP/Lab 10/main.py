
import unittest

from repository.repository_assignments import RepositoryAssignments, RepositoryAssignmentsFile
from repository.repository_laboratoare import RepositoryLaboratoare, RepositoryLaboratoareFile
from repository.repository_student import RepositoryStudenti, RepositoryStudentiFile
from service.service_assignments import ServiceAssignments
from service.service_laboratoare import ServiceLaboratoare
from service.service_studenti import ServiceStudenti
from ui.console import Console
from ui.ui_assignments import UIAssignments
from ui.ui_laboratoare import UILaboratoare
from ui.ui_studenti import UIStudenti

# Creeam obiectele ce tin de UnitTesting
loader = unittest.TestLoader()
suite = loader.discover("teste")
runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite)

#Creeam obiectele ce tin de studenti
repo_studenti = RepositoryStudenti()

filepath_studenti = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Lab 10\sources\studenti.txt"
repo_studenti_file = RepositoryStudentiFile(filepath_studenti)

service_studenti = ServiceStudenti(repo_studenti_file)
ui_studenti = UIStudenti(service_studenti)

#Creeam obiectele ce tin de laboratoare
repo_laboratoare = RepositoryLaboratoare()

filepath_laboratoare = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Lab 10\sources\laboratoare.txt"
repo_laboratoare_file = RepositoryLaboratoareFile(filepath_laboratoare)

service_laboratoare = ServiceLaboratoare(repo_laboratoare_file)
ui_laboratoare = UILaboratoare(service_laboratoare)

#Creeam obiectele ce tin de assignmenturi
repo_assignments = RepositoryAssignments()

filepath_assignments = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\Lab 10\sources\assignments.txt"
repo_assignments_file = RepositoryAssignmentsFile(filepath_assignments)

service_assignments = ServiceAssignments(repo_assignments_file, repo_studenti_file, repo_laboratoare_file)
ui_assignments = UIAssignments(service_assignments)

#Controller
console = Console(ui_studenti, ui_laboratoare, ui_assignments)
console.run()