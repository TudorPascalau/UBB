"""
Aplicatie de gestionare a participantilor la un concurs de informatica
"""

import ui
import ui_scor
import ui_subset
import ui_filtrare
import menu
import test

from service import adauga_exemple_concurenti


def main():
    """
    Implementare interfata utilizator
    """

    concurenti = ["filler"]

    while True:
        menu.print_menu()
        option = input().strip()

        if option == "1":
            ui.adaugaConcurent(concurenti)
        elif option == "2":
            concurenti = ui.inserareConcurent(concurenti)
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
                concurenti = ui_scor.modificaScorConcurent(concurenti)

            if option_modif == "2":
                concurenti = ui_scor.stergeScorConcurent(concurenti)

            if option_modif == "3":
                concurenti = ui_scor.stergeScorInterval(concurenti)

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
                concurenti = ui_filtrare.filtrareMultiple(concurenti)

            elif option_filtrare == "2":
                concurenti = ui_filtrare.filtrareScorMaiMic(concurenti)

            else:
                print("Nu inteleg comanda")

        elif option == "7":
            adauga_exemple_concurenti(concurenti)

        elif option == "x":
            break

        else:
            print("Nu inteleg comanda")

    print("La revedere!")

if __name__ == "__main__":
    test.test_all()
    main()


"""
Exemple date de intrare:

305
10 9 8 7 9 10 8 9 8 7 ; 85
306
10 9 8 7 9 10 8 9 9 10 ; 89
310
10 9 8 7 9 6 8 9 9 10 ; 85
204
10 9 8 8 9 8 8 8 9 10 ; 87
"""