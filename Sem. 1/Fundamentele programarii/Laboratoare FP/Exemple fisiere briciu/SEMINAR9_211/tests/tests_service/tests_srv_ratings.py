from domain.entities import Melodie
from domain.validator import ValidatorRating
from exceptions.exceptions import PersonDoesNotExistException, SongDoesNotExistException
from repos.repo_melodii import RepoMelodieMemory
from repos.repo_persoane import PersonFileRepository
from repos.repo_rating import RatingMemoryRepository
from services.service_ratings import ServiceRatings
from utils.file_utils import copy_file_content, clear_file_content

TEST_FILE_PATH = "test_persons.txt"
DEFAULT_ENTITIES_PATH = "default_persons.txt"


def test_add_rating():
    song_repo = RepoMelodieMemory()
    song_repo.add(Melodie(1, "Highway Star", "Deep Purple", "rock", 4.21))

    clear_file_content(TEST_FILE_PATH)
    copy_file_content(DEFAULT_ENTITIES_PATH, TEST_FILE_PATH)
    person_repo = PersonFileRepository(TEST_FILE_PATH)

    evaluare_repo = RatingMemoryRepository()
    rating_validator = ValidatorRating()
    rating_service = ServiceRatings(song_repo, person_repo, evaluare_repo, rating_validator)
    # all ok, can add
    rating_service.add_rating(1, '6050706437566', 4)
    assert (len(rating_service.get_all()) == 1)

    rating_service.add_rating(1, '1760920213245', 3.21)
    assert (len(rating_service.get_all()) == 2)

    # add same rating
    try:
        rating_service.add_rating(1, '1760920213245', 3.75)
        assert False
    except ValueError:
        assert True

    # person doesn't exist
    try:
        rating_service.add_rating(1, '1760920213241', 5)
        assert False
    except PersonDoesNotExistException:
        assert True

    # song doesn't exist
    try:
        rating_service.add_rating(1347, '1760920213245', 2.335)
        assert False
    except SongDoesNotExistException:
        assert True

    # incorrect evaluation score
    try:
        rating_service.add_rating(1, '1760920213245', 100)
        assert False
    except ValueError:
        assert True



if __name__ == '__main__':
    test_add_rating()
