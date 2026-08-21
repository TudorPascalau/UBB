from business.service_materii import ServiceMaterii
from business.service_note import ServiceNote
from business.service_studenti import ServiceStudenti
from infrastructura.repo_materii import RepositoryMaterii
from infrastructura.repo_note import RepositoryNote
from infrastructura.repo_studenti import RepositoryStudenti
from prezentare.console import Console
from testare.teste import Teste
from validare.validator_materie import ValidatorMaterie
from validare.validator_nota import ValidatorNota
from validare.validator_student import ValidatorStudent

validator_student = ValidatorStudent()
validator_materie = ValidatorMaterie()
validator_nota = ValidatorNota()

repo_studenti = RepositoryStudenti()
repo_materii = RepositoryMaterii()
repo_note = RepositoryNote()

service_studenti = ServiceStudenti(repo_studenti, validator_student)
service_materii = ServiceMaterii(repo_materii, validator_materie)
service_note = ServiceNote(repo_studenti,repo_materii,repo_note, validator_nota)

teste = Teste()
teste.ruleaza_toate_testele()
ui = Console(service_studenti, service_materii, service_note)
ui.run()