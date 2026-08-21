
from ui import ui, ui_scor, ui_undo
from domain import service


def run():
    """
    Implementare interfata utilizator
    """

    concurenti = ["filler"]
    istoric_concurenti = []

    while True:
        print(">>> ")
        comanda = input().strip()
        comenzi = comanda.split()

        comanda = comenzi[0]
        param = comenzi[1:]

        if comanda == "Adaugare":
            ui.adaugaConcurent(concurenti, istoric_concurenti, param)

        elif comanda == "Inserare":
            concurenti = ui.inserareConcurent(concurenti, istoric_concurenti, param)

        elif comanda == "Afisare":
            tip_afis = param[0]
            param = param[1:]

            if tip_afis == "ordonata":
                ui_scor.afisareConcurentiOrdonareScor(concurenti)

            elif tip_afis == "comparare":
                ui_scor.afisareConcurentiComparareScor(concurenti, param)

            else: print("Nu inteleg comanda")

        elif comanda == "Sterge":
            concurenti = ui_scor.stergeScorConcurent(concurenti, istoric_concurenti,param)

        elif comanda == "Undo":
            concurenti = ui_undo.Undo(istoric_concurenti)

        elif comanda == "Exemple":
            service.adauga_exemple_concurenti(concurenti,istoric_concurenti)

        elif comanda == "Exit":
            break

        else: print("Nu inteleg comanda")