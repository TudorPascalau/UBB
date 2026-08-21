from domain.validator import ValidatorMelodie, ValidatorPersoana, ValidatorRating
from repos.repo_melodii import RepoMelodieMemory, RepoMelodieFile
from repos.repo_persoane import PersonFileRepository
from repos.repo_rating import RatingMemoryRepository, RepoRatingFile

from services.service_melodii import ServiceMelodii
from services.service_persoane import ServicePersoane
from services.service_ratings import ServiceRatings
from ui.console import Console

repo_melodii = RepoMelodieFile("data/melodii.txt")
val_melodie = ValidatorMelodie()
srv_melodii = ServiceMelodii(repo_melodii, val_melodie)

repo_persoane = PersonFileRepository("data/persons.txt")

val_persoana = ValidatorPersoana()
srv_persoane = ServicePersoane(repo_persoane, val_persoana)
repo_ratings = RepoRatingFile("data/evaluari.txt")
val_rating = ValidatorRating()
srv_ratings = ServiceRatings(repo_melodii, repo_persoane, repo_ratings, val_rating)
console = Console(srv_melodii, srv_persoane, srv_ratings)
console.run()
