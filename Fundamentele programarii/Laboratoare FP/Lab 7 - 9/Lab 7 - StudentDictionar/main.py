from repository.repo_laboratoare import RepositoryLaboratoare
from repository.repo_studenti import RepositoryStudenti
from repository.repo_assignment import RepositoryAssignments
from service.service_assignment import ServiceAssignment
from service.service_laboratoare import ServiceLaboratoare
from service.service_rapoarte import ServiceRapoarte
from service.service_studenti import ServiceStudenti
from test.teste_assignment import TesteAssignment
from test.teste_laborator import TesteLaborator
from test.teste_rapoarte import TesteRapoarte
from test.teste_student import TesteStudent
from ui.console import Console
from ui.ui_assignment import UIAssignment
from ui.ui_laboratoare import UILaboratoare
from ui.ui_rapoarte import UIRaport
from ui.ui_studenti import UIStudenti
from validare.validator_assignment import ValidatorAssignment
from validare.validator_laborator import ValidatorLaborator
from validare.validator_student import ValidatorStudent

def main():
    """
    Derularea intregului program
    """

    # Crearea obiectelor ce tin de gestionare studentilor
    validator_student = ValidatorStudent()
    repo_studenti = RepositoryStudenti()
    service_studenti = ServiceStudenti(repo_studenti, validator_student)
    ui_studenti = UIStudenti(service_studenti)

    # Crearea obiectelor ce tin de gestionarea laboratoarelor
    validator_laborator = ValidatorLaborator()
    repo_laboratoare = RepositoryLaboratoare()
    service_laboratoare = ServiceLaboratoare(repo_laboratoare, validator_laborator)
    ui_laborator = UILaboratoare(service_laboratoare)

    #Crearea obiectelor ce tin de gestionarea assignmenturilor
    validator_assignment = ValidatorAssignment()
    repo_assignment = RepositoryAssignments()
    service_assignment = ServiceAssignment(repo_assignment, validator_assignment, repo_studenti, repo_laboratoare)
    ui_assigment = UIAssignment(service_assignment)

    #Crearea obiectelor ce tin de gestionarea rapoartelor
    service_rapoarte = ServiceRapoarte(service_studenti, service_laboratoare, service_assignment)
    ui_rapoarte = UIRaport(service_rapoarte)

    # Crearea obiectelor ce tin de testare
    teste_student = TesteStudent()
    teste_student.test_all() # Apelarea testelor

    teste_laborator = TesteLaborator()
    teste_laborator.test_all()

    teste_assignment = TesteAssignment()
    teste_assignment.test_all()

    teste_rapoarte = TesteRapoarte()
    teste_rapoarte.test_all()

    # Crearea obiectelor ce tin de UI
    ui = Console(ui_studenti, ui_laborator, ui_assigment, ui_rapoarte)
    ui.run() # Apelarea consolei

if __name__ == "__main__":
    main()