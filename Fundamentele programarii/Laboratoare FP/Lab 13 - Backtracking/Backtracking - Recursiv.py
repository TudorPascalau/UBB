"""
Se da o lista de numere intregi a1, a2, ...., an
Determinati toate subsecventele (ordinea elementelor este mentinuta) strict crescatoare


Solutie candidat:
    x = (x0, x1, ... , xk), xi apartine {1,2, ... , n} si x0 < x1 < ... < xk
    xi reprezinta indicele elementului ai din lista de numere intregi

Conditie consistent:
    x = (x0, x1, ... , xk) e consistent daca a(xi) < a(xi+1), oricare i apartine {0, 1, ... , k-1}

Conditie solutie:
    x = (x0, x1, ... , xk) e solutie daca e consistent si k >= 1
"""


def consistent(x, a):
    for i in range(len(x)-1):
        if a[x[i]] >= a[x[i+1]]:
            return False
    return True

def solutie(x):
    return len(x) >= 2

def outputSolutie(x, a):
    print([a[i] for i in x])

def backRec(x, a, start):
    for i in range(start, len(a)):
        x.append(i) # setam elementul actual
        if consistent(x, a):
            if solutie(x):
                outputSolutie(x, a)
            backRec(x, a, i+1) # continuam cautare solutii
        x.pop() # mergem inapoi

def main():
    print("Introduceti lista:")
    a = [int(item) for item in input().split()] # lista intregi
    x = [] # solutie candidat
    start = 0

    backRec(x, a, start)

if __name__ == "__main__":
    main()

#2 4 7 3 9 10 11 5 8