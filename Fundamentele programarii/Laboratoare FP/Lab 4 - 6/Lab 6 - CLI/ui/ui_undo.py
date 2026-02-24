from domain import service_undo

def Undo(istoric_concurenti):
    """
    Implementare UI pentru functionalitatea de undo
    """

    try:
        concurenti =  service_undo.undo_last(istoric_concurenti)
    except IndexError:
        print("Lista este goala! Operatia de undo nu se poate efectua!")
    else:
        print("Operatia de undo a fost executata")
        return concurenti