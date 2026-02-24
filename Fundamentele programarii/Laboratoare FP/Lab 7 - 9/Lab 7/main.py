from repository.repo_studenti import RepositoryStudenti
from service.service_studenti import ServiceStudenti
from test.teste import Teste
from ui.console import Console
from ui.ui_studenti import UIStudenti
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

    # Crearea obiectelor ce tin de testare
    teste = Teste()
    teste.test_all() # Apelarea testelor

    # Crearea obiectelor ce tin de UI
    ui = Console(ui_studenti)
    ui.run() # Apelarea consolei

if __name__ == "__main__":
    main()