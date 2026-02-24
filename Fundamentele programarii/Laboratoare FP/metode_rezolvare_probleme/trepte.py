def fibo0(n):
    '''
    complexitate: O(2^n)
    functie care returneaza al n-ulea din sirul lui fibonacci
    :param n: intreg >0
    :return:fn al n-ulea termen din sirul lui fibonacci
    '''
    if n==0 or n==1:
        return n
    return fibo0(n-1) + fibo0(n-2)

def fibo1(n):
    '''
    complexitate: theta(n)
    functie care returneaza al n-ulea din sirul lui fibonacci
    :param n: intreg >0
    :return:fn al n-ulea termen din sirul lui fibonacci
    '''
    if n==0 or n==1:
        return n
    anterior = 0
    curent = 1
    for i in range(n):
        aux = anterior+curent
        anterior = curent
        curent = aux
    return anterior

def ridicare_putere(n,p):
    '''
    complexitate: theta(log2(p))
    algoritm de ridicare la putere in timp logaritmic
    :param n:
    :param p:
    :return:
    '''
    if p == 0:
        return 1
    rezultat = ridicare_putere(n, p//2)
    if p % 2 == 0:
        return rezultat*rezultat
    return rezultat*rezultat*n


def mul_mat(a, b):
    return [[0,1],[1,1]]


def ridicare_putere_matrice(m,p):
    '''
    complexitate: theta(log2(p))
    algoritm de ridicare la putere in timp logaritmic
    :param n:
    :param p:
    :return:
    '''
    if p == 0:
        return 1
    rezultat = ridicare_putere_matrice(m, p//2)
    if p % 2 == 0:
        return mul_mat(rezultat, rezultat)
    return mul_mat(mul_mat(rezultat, rezultat),m)

def fibo2(n):
    '''
    complexitate: theta(log2(n))
    functie care returneaza al n-ulea din sirul lui fibonacci
    :param n: intreg >0
    :return:fn al n-ulea termen din sirul lui fibonacci
    '''
    if n==0 or n==1:
        return n
    A = [[0,1],[1,1]]
    return ridicare_putere_matrice(A,n+1)[0][0]

