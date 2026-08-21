def gaseste_triplete_0(v,s):
    '''
    complexitate: theta(n^3)
    functie care determina toate tripletele de suma s din lista v de numere intregi distincte
    :param v: lista cu numere intregi distincte
    :param s: numar intreg
    :return: lista cu triplete de forma (v[i],v[j],v[k]) cu proprietatea ca v[i]+v[j]+v[k] == s
    '''
    rezultat = []
    for i in range(len(v)-2):
        for j in range(i+1,len(v)-1):
            for k in range(j+1,len(v)):
                if v[i]+v[j]+v[k]==s:
                    rezultat.append((v[i],v[j],v[k]))
    return rezultat


def cauta_binar(v, s, d, x):
    '''
    analiza complexitatii:
        caz favorabil - cand x se afla pe prima pozitie cautata, aka la mijloc :theta(1)
        caz defavorabil - cand x nu se afla in sir : theta(log2(d-s))
        caz mediu - 1*1+2*2+3*2^2+4*2^2+... =theta(log2(d-s))
        =>cf!=df=> complexitate generala O(complexitate caz mediu=log2(d-s))
    :param v:
    :param s:
    :param d:
    :param x:
    :return:
    '''
    mij = s+ (d-s)//2
    while s<=d:
        if v[mij]==x:
            return mij
        elif v[mij]>x:
            d = mij-1
        else:
            s = mij+1
    return -1

def gaseste_triplete_1(v,s):
    '''
    complexitate: O(n^2*log2(n))
    functie care determina toate tripletele de suma s din lista v de numere intregi distincte
    :param v: lista cu numere intregi distincte
    :param s: numar intreg
    :return: lista cu triplete de forma (v[i],v[j],v[k]) cu proprietatea ca v[i]+v[j]+v[k] == s
    '''
    rezultat = []
    v.sort()#caz defavorabil:theta(n^2)
    for i in range(len(v)-2):
        for j in range(i+1,len(v)-1):
            k =cauta_binar(v,j+1,len(v)-1,s-v[i]-v[j])
            if k!=-1:
                rezultat.append((v[i],v[j],v[k]))
    return rezultat


def shusta_cu_doi_indici(v,i, st, dr, s):
    rezultat = []
    while st<=dr:
        if v[i]+v[st]+v[dr] == s:
            rezultat.append((v[i],v[st],v[dr]))
            st+=1
        elif v[i]+v[st]+v[dr] < s:
            st+=1
        else:
            dr-=1
    return rezultat


def gaseste_triplete_2(v,s):
    '''
    complexitate:theta(n-1+n-2+...+2+1=n(n+1)/2 => n^2)
    functie care determina toate tripletele de suma s din lista v de numere intregi distincte
    :param v: lista cu numere intregi distincte
    :param s: numar intreg
    :return: lista cu triplete de forma (v[i],v[j],v[k]) cu proprietatea ca v[i]+v[j]+v[k] == s
    '''
    rezultat = []
    v.sort()#caz defavorabil:theta(n^2)
    for i in range(len(v)-2):
        triplete = shusta_cu_doi_indici(v,i,i+1,len(v)-1,s)
        rezultat += triplete
    return rezultat

def test_gaseste_triplete(functie_gaseste_triplete):
    pass