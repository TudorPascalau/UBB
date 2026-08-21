def is_Prime(x):
    is_prime = True
    if(x < 2):
        is_prime = False
    for divizor in range(2, x//2 + 1):
        if(x % divizor == 0):
            is_prime = False

    return is_prime

def next_Prime(x):
    x = x + 1
    while(is_Prime(x) == False):
        x = x + 1

    return x


n = int(input("Introduceti numar: "))

if(n <= 3):
    print("Nu exista solutie")

else:
    p1 = 2

    while(p1 <= n//2):
        p2 = n - p1
        if(is_Prime(p2) == True):
            print("Solutia este",p1,"+",p2,"=",n)
            break

        else: p1 = next_Prime(p1)

    if(p1 > n//2):
        print("Nu exista solutie")



