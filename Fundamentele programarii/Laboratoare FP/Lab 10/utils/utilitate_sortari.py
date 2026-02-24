def selection_sort(lista, key = lambda x: x, reverse = False):
    n = len(lista)
    for i in range(0, n - 1):
        poz_extrem = i
        for j in range(i + 1, n):
            if not reverse:
                if key(lista[j]) < key(lista[poz_extrem]):
                    poz_extrem = j

            else:
                if key(lista[j]) > key(lista[poz_extrem]):
                    poz_extrem = j

        if poz_extrem != i:
            aux = lista[i]
            lista[i] = lista[poz_extrem]
            lista[poz_extrem] = aux

    return lista