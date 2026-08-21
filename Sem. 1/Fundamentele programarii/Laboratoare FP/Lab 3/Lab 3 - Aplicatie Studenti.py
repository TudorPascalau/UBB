"""

Student:
    - nume
    - CNP
    - specializare
    - grupa

"""

"""
Functionalitati:
    - adaugare studenit
    - afisare
"""

def creeaza_student(nume, grupa, spec, cnp):
    # return [nume, grupa, spec, cnp]
    return {
        "nume": nume,
        "grupa": grupa,
        "specializare": spec,
        "cnp": cnp
        }

def get_nume_student(student):
    # return student[0]
    return student["nume"]

def get_grupa_student(student):
    return student["grupa"]

def valideaza_student(student):
    """
    Verifica daca studentul 'student' este corect
    Input:
        - student - student
    Output:
        - True daca studentul este corect,
        - False altfel
    """

    erori = []

    #validare nume
    for litera in get_nume_student(student):
        if '0' <= litera <= '9':
            erori.append("Numele nu este valid!")
            break
    #validare grupa
    if not 100 <= get_grupa_student(student) <= 999:
        erori.append("Grupa nu este valida!")

    if erori:
        return False
    return True

def adauga_student(studenti, nume, grupa, spec, cnp):
    # studenti.append([nume, grupa, spec, cnp])

    """
    Adauga un student in 'studenti' cu datele furnizate
    input:
        - studenit - lista de studenti in care se va insera
        - nume - numele studentului care va fi inserat
    output:
        - True daca adauga studentul
        - False altfel
    """
    
    student = creeaza_student(nume, grupa, spec, cnp)
    if not valideaza_student(student):
        return False

    studenti.append(student)
    return True
    

def adaugare_ui(studenti):
    nume = input("Da nume: ")
    grupa = int(input("Da grupa: "))
    spec = input("Da specializare: ")
    cnp = input("Da CNP:")

    if adauga_student(studenti, nume, grupa, spec, cnp):
        print("Studentul s-a adaugat cu succes!")

    else:
        print("Eroare la adaugare!")

def afisare_studenti(studenti):
    for student in studenti:
        print(f"Nume: {get_nume_student(student)}")

def main():

    studenti = []

    while True:
        comanda = int(input("Da comanda: "))
        if comanda == 1: # adaugam
            adaugare_ui(studenti)
            
        elif comanda == 2: # afisare
            afisare_studenti(studenti)

        elif comanda == 3: # exit
            break

        else:
            print(f"Nu inteleg comanda {comanda} ")

def test_creeaza_student():
    student = creeaza_student("Vasile", 214 , "Info", 1234)
    assert get_nume_student(student) == "Vasile"

def test_adauga_student():

    studenti = []
    adauga_student(studenti, "Vasile", 214, "Info", "12456")
    
    assert len(studenti) == 1
    assert get_nume_student(studenti[len(studenti) - 1]) == "Vasile"

def test_all():
    test_creeaza_student()
    test_adauga_student()
    


test_all()
main()
