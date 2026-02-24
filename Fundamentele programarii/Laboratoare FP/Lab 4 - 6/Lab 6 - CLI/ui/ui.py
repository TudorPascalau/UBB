
from domain import concurent, service
from utils import validator


def adaugaConcurent(concurenti, istoric_concurenti, param):
    """
    UI pt adaugare concurent
    """
    try:
        numar = int(param[0]) #Numarul de concurs
        valori_probe = param[1:] #Notele la cele 10 probe
        note = [int(nota) for nota in valori_probe] #Transformare string note in lista

        concurent_nou = concurent.creeaza_concurent(numar, note) #Creare concurent cu informatiile date

        #Validare si adaugare concurent
        if validator.valideaza_concurent(concurent_nou, concurenti):
            service.adauga_concurent(concurenti, numar, note, istoric_concurenti)
            print(f"Concurentul a fost adaugat pe pozitia {concurent.get_poz_from_numar(concurenti,numar)}.")

        else:
            print("Concurentul nu este valid!")

    except:
        print("Parametrii comenzii nu sunt corecti!")

def inserareConcurent(concurenti, istoric_concurenti, param):
    """
    UI pt inserare concurent
    """

    try:
        poz = int(param[0]) # Pozitia de inserare
        numar = int(param[1]) #Numarul de concurs
        valori_probe = param[2:] #Notele la cele 10 probe
        note = [int(nota) for nota in valori_probe] #Transformare string note in lista


        concurent_nou = concurent.creeaza_concurent(numar, note) #Creare concurent cu informatiile date

        #Validare si inserare concurent
        if validator.valideaza_concurent(concurent_nou, concurenti):
            print(f"Concurentul a fost inserat pe pozitia {poz}")
            concurenti = service.inserare_concurent(concurenti, poz, numar, note, istoric_concurenti)

        else:
            print("Concurentul nu este valid!")

        return concurenti

    except:
        print("Parametrii comenzii nu sunt corecti!")

def afisareConcurent(concurent_afis):
    """
    UI pt afisare concurent
    """
    print(f"Numar: {concurent.get_numar_concurent(concurent_afis)}")
    #print(f"Pozitia: {concurent.get_poz_from_numar(concurenti, concurent.get_numar_concurent(concurent_afis))}")
    print(f"Note: {concurent.get_note_concurent(concurent_afis)}")
    print(f"Scor: {concurent.get_scor_concurent(concurent_afis)}")
    print()
