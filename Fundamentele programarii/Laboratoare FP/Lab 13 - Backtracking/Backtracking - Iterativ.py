"""
Se da o lista de numere intregi a1, a2, ...., an
Determinati toate subsecventele (ordinea elementelor este mentinuta) strict crescatoare


Solutie candidat:
    x = (x0, x1, ... , xk), xi apartine {1,2, ... , n} si x0 < x1 < ... < xk
    xi reprezinta indicele elementului ai din lista de numere intregi

Conditie consistent:
    x = (x0, x1, ... , xk) e consistent daca a(xi) < a(xi+1), oricare i apartine {0, 1, ... , k-1}

Conditie solutie:
    x = (x0, x1, ... , xk) e solutie daca e consistent

"""


def consistent(x, a):
    for i in range(len(x)-1):
        if a[x[i]] >= a[x[i+1]]:
            return False

    for i in range(len(x)-1):
        if x[i]>=x[i+1]:
            return False

    return True

def solutie(x):
    return len(x) >= 2

def outputSolutie(x, a):
    print([a[i] for i in x])

def backIter(a):
    x = [-1] # solutia candidat
    while len(x) > 0:
        chosen = False
        while not chosen and x[-1] < len(a)-1:
            x[-1] = x[-1] + 1 #incrementeaza ultimul
            chosen = consistent(x, a)
        if chosen:
            if solutie(x):
                outputSolutie(x, a)
            x.append(-1) #continuare solutie candidat
        else:
            x.pop() #mergem inapoi

def main():
    print("Introduceti lista:")
    a = [int(item) for item in input().split()]

    backIter(a)

if __name__ == "__main__":
    main()

#2 4 7 3 9 10 11 5 8