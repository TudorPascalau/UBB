from controller.service import Service
from repository.repository import Repository
from ui.ui import UI


def main():
    repo = Repository()
    service = Service(repo)
    ui = UI(service)
    ui.start()


if __name__ == '__main__':
    main()
