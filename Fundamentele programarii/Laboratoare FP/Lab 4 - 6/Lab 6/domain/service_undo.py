

def undo_last(istoric_concurenti):
    """
    Undo pentru ultima operatie efectuata
    :param istoric_concurenti: Lista de stive de concurenti, folosita pentru undo-uri
    :return: Lista de concurenti anterioara
    """


    concurenti = istoric_concurenti[-1] #Intoarcerea la ultima versiune a listei
    istoric_concurenti.pop() #Eliminarea versiunii actuale a listei din stiva

    return concurenti