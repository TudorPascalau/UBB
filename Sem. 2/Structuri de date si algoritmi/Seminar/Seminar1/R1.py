class Colectie:
    def __init__(self):
        self.__elemente = []

    def adauga(self, e):
        self.__elemente.append(e)

    def cauta(self, e):
        return e in self.__elemente

    def sterge(self, e):
        # obs: pentru temele de la laborator, operatiile vor trebui implementate de voi (nu puteti folosi containere din STL)
        i = 0
        while i < len(self.__elemente):
            if self.__elemente[i] == e:
                self.__elemente.pop(i)
                return True
            i += 1
        return False
        # solutie alternativa:
        '''
        try:
            self.__elemente.remove(e)  
            return True
        except ValueError as e:
            return False
        '''

    def dim(self):
        return len(self.__elemente)

    def iterator(self):
        return Iterator(self)

    def nr_aparitii(self, e):
        n = 0
        for elem in self.__elemente:
            if elem == e:
                n = n + 1
        return n


class Iterator:
    def __init__(self, c):
        self.__c = c
        self.__curent = 0  # indexul elementului curent

    def valid(self):
        return self.__curent < self.__c.dim()

    def element(self):
        # in C++, Iteratorul si Colectia vor fi friend classes => iteratorul va putea accesa atributele private ale colectiei
        # in Python, putem accesa atributul privat "elemente" astfel:
        return self.__c._Colectie__elemente[self.__curent]

    def urmator(self):
        self.__curent = self.__curent + 1

    def prim(self):
        self.__curent = 0


def teste():
    c = Colectie()
    for i in range(100):
        c.adauga(i)

    assert c.dim() == 100

    for i in range(100):
        if i % 2 == 0:
            c.adauga(i)

    for i in range(100):
        if i % 2 == 0:
            assert c.nr_aparitii(i) == 2
        else:
            assert c.nr_aparitii(i) == 1

    for i in range(-100, 100):
        if i < 0:
            old_dim = c.dim()
            assert not(c.sterge(i))
            assert c.dim() == old_dim
        else:
            assert c.sterge(i)

    assert c.dim() == 50


def populeaza_colectie_intregi(c):
    c.adauga(1)
    c.adauga(2)
    c.adauga(3)
    c.adauga(2)
    print("Stergerea elementului 2:", c.sterge(2))
    c.adauga(2)
    print("Stergerea elementului 100", c.sterge(100))


def tipareste(c):
    it = c.iterator()
    while it.valid():
        print(it.element())
        it.urmator()
    print("Finalizare tiparire. Sa tiparim din nou continutul colectiei.")
    it.prim()
    while it.valid():
        print(it.element())
        it.urmator()


def main():
    teste()
    c = Colectie()
    populeaza_colectie_intregi(c)
    print("Dimensiunea colectiei:", c.dim())
    print("Numarul de aparitii ale elementului 2:", c.nr_aparitii(2))
    tipareste(c)


main()
