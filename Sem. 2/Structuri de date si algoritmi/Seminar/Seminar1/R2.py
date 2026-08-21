class PerecheElementFrecventa:
    def __init__(self, e, f):
        self.__e = e
        self.__f = f

    @property
    def element(self):
        return self.__e

    @property
    def frecventa(self):
        return self.__f

    @frecventa.setter
    def frecventa(self, f):
        self.__f = f

    '''
    def set_element(self, e):
        self.__e = e


    def set_frecventa(self, f):
        self.__f = f


    def get_element(self):
        return self.__e


    def get_frecventa(self):
        return self.__f
    '''


class ColectieElementFrecventa:
    def __init__(self):
        self.__perechi = []
        # pastram o variabila care memoreaza numarul de elemente curent
        # actualizam aceasta variabila dupa fiecare adaugare/stergere
        self.__nr_elem = 0  

    def adauga(self, e):
        # Distingem doua cazuri: (1) elementul apare sau (2) nu apare deja in colectie
        # cazul (1): incrementam frecventa elementului
        # cazul (2): adaugam elementul nou, cu frecventa 1
        self.__nr_elem += 1
        for p in self.__perechi:
            if p.element == e:
                p.frecventa += 1  # daca am fi definit operatiile get_frecventa si set_frecventa: p.set_frecventa(p.get_frecventa()+1)
                return
                
        p = PerecheElementFrecventa(e, 1)
        self.__perechi.append(p)

    def cauta(self, e):
        for p in self.__perechi:
            if p.element == e:
                return True
        return False

    def sterge(self, e):
        # Distingem trei cazuri:
        # (1) elementul nu apare in colectie
        # (2) elementul apare in colectie o singura data
        # (3) elementul apare in colectie de mai multe ori
        # cazul (1): colectia ramane nemodificata
        # cazul (2): perechea care il contine va fi stearsa
        # cazul (3): frecventa lui va fi decrementata
        # se returneaza True daca elementul a fost sters si False altfel
        for i, p in enumerate(self.__perechi):
            if p.element == e:
                # stergem o aparitie => dimensiunea este decrementata
                self.__nr_elem -= 1
                if p.frecventa > 1:
                    p.frecventa -= 1
                else:
                    self.__perechi.pop(i)
                return True
        return False

    def dim(self):
        return self.__nr_elem
        # daca nu memoram intr-o variabila numarul de elemente,
        # acesta poate fi calculat ca suma frecventelor tuturor elementelor din colectie
        # return sum(p.frecventa for p in self.__perechi)

    def iterator(self):
        return IteratorColectieFrecventa(self)

    def nr_aparitii(self, e):
        for p in self.__perechi:
            if p.element == e:
                return p.frecventa
        return 0


class IteratorColectieFrecventa:
    
    def __init__(self, c):
        self.__col = c
        self.__curent = 0    # indexul elementului curent
        self.__f = 1         # frecventa curenta

    def valid(self):
        return self.__curent < len(self.__col._ColectieElementFrecventa__perechi)

    def element(self):
        return self.__col._ColectieElementFrecventa__perechi[self.__curent].element

    def urmator(self):
        # Distingem doua cazuri: frecventa curenta a elementului curent este
        # (1) strict mai mica decat sau (2) egala cu frecventa elementului curent in colectia iterata
        # cazul (1): incrementam frecventa curenta
        # cazul (2): trecem la elementul urmator, incrementand indexul curent si reinitializand frecventa curenta cu 1 
        if self.__f < self.__col._ColectieElementFrecventa__perechi[self.__curent].frecventa:
           self.__f += 1
        else:
           self.__curent += 1
           self.__f = 1
		   
    def prim(self):
        self.__curent = 0
        self.__f = 1


def teste():
    c = ColectieElementFrecventa()
    for i in range(100):
        c.adauga(i)
        
    assert c.dim() == 100

    for i in range(100):
        assert c.cauta(i) == True
    
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
            assert c.cauta(i) == False
            assert c.sterge(i) == False
            assert c.dim() == old_dim
        else:
            assert c.sterge(i) == True
    
    assert c.dim() == 50

    
def populeaza_colectie_intregi(c):
    c.adauga(1)
    c.adauga(2)
    c.adauga(3)
    c.adauga(2) 
    c.sterge(2)
    c.adauga(2)
    c.sterge(100)

    
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
    c = ColectieElementFrecventa()
    populeaza_colectie_intregi(c)
    print("Dimensiunea colectiei:", c.dim())
    print("Numarul de aparitii ale elementului 2:", c.nr_aparitii(2))
    tipareste(c)

main()
