
import concurent
import validator
import service

def adaugaConcurent(concurenti):
    """
    UI pt adaugare concurent
    """
    numar = int(input("Numar: ")) #Numarul de concurs
    valori_probe = input("Valori probe: ") #Notele la cele 10 probe
    note = [int(nota) for nota in valori_probe.split()] #Transformare string note in lista

    concurent_nou = concurent.creeaza_concurent(numar, note) #Creare concurent cu informatiile date

    #Validare si adaugare concurent
    if validator.valideaza_concurent(concurent_nou, concurenti):
        service.adauga_concurent(concurenti, numar, note)
        print(f"Concurentul a fost adaugat pe pozitia {concurent.get_poz_from_numar(concurenti,numar)}.")

    else:
        print("Eroare la adaugare concurent!")

def inserareConcurent(concurenti):
    """
    UI pt inserare concurent
    """

    numar = int(input("Numar: ")) #Numarul de concurs
    valori_probe = input("Valori probe: ") #Notele la cele 10 probe
    note = [int(nota) for nota in valori_probe.split()] #Transformare string note in lista
    poz = int(input("Pozitie: ")) #Pozitia de inserare

    concurent_nou = concurent.creeaza_concurent(numar, note) #Creare concurent cu informatiile date

    #Validare si inserare concurent
    if validator.valideaza_concurent(concurent_nou, concurenti):
        print(f"Concurentul a fost inserat pe pozitia {poz}")
        concurenti = service.inserare_concurent(concurenti, poz, numar, note)

    else:
        print("Eroare la inserare concurent!")

    return concurenti

def afisareConcurent(concurent_afis):
    """
    UI pt afisare concurent
    """
    print(f"Numar: {concurent.get_numar_concurent(concurent_afis)}")
    #print(f"Pozitia: {concurent.get_poz_from_numar(concurenti, concurent.get_numar_concurent(concurent_afis))}")
    print(f"Note: {concurent.get_note_concurent(concurent_afis)}")
    print(f"Scor: {concurent.get_scor_concurent(concurent_afis)}")
    print()
