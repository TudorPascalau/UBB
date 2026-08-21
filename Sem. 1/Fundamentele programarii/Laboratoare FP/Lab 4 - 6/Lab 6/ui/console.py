
from ui import ui, ui_filtrare, ui_scor, ui_subset, ui_undo
from utils import menu

from domain.service import adauga_exemple_concurenti

def run():
    """
    Implementare interfata utilizator
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    while True:
        menu.print_menu()
        option = input().strip()

        if option == "1":
            ui.adaugaConcurent(concurenti, istoric_concurenti)
        elif option == "2":
            concurenti = ui.inserareConcurent(concurenti, istoric_concurenti)
        elif option == "3":
            menu.print_menu_afisare()
            option_afis = input().strip()

            if option_afis == "1":
                ui_scor.afisareConcurentiComparareScor(concurenti)
            elif option_afis == "2":
                ui_scor.afisareConcurentiOrdonareScor(concurenti)
            elif option_afis == "3":
                ui_scor.afisareConcurentiOrdonareComparare(concurenti)

            else:
                print("Nu inteleg comanda")

        elif option == "4":
            menu.print_menu_modif()
            option_modif = input().strip()

            if option_modif == "1":
                concurenti = ui_scor.modificaScorConcurent(concurenti, istoric_concurenti)

            elif option_modif == "2":
                concurenti = ui_scor.stergeScorConcurent(concurenti, istoric_concurenti)

            elif option_modif == "3":
                concurenti = ui_scor.stergeScorInterval(concurenti, istoric_concurenti)

            else:
                print("Nu inteleg comanda")

        elif option == "5":
            menu.print_menu_subset()
            option_subset = input().strip()

            if option_subset == "1":
                ui_subset.afisareMedieInterval(concurenti)

            elif option_subset == "2":
                ui_subset.afisareMinInterval(concurenti)

            elif option_subset == "3":
                ui_subset.afisareMultiplu10(concurenti)

            else:
                print("Nu inteleg comanda")

        elif option == "6":
            menu.print_menu_filtrare()
            option_filtrare = input().strip()

            if option_filtrare == "1":
                concurenti = ui_filtrare.filtrareMultiple(concurenti, istoric_concurenti)

            elif option_filtrare == "2":
                concurenti = ui_filtrare.filtrareScorMaiMic(concurenti, istoric_concurenti)

            else:
                print("Nu inteleg comanda")

        elif option == "7":
            adauga_exemple_concurenti(concurenti, istoric_concurenti)

        elif option == "8":
            concurenti = ui_undo.Undo(istoric_concurenti)

        elif option == "x":
            break

        else:
            print("Nu inteleg comanda")

    print("La revedere!")