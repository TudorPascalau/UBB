
n = int(input("Introduceti numar: "))

f1 = 1
f2 = 1
f3 = f1 + f2

while(f1 <= n):
    f1 = f2
    f2 = f3
    f3 = f1+ f2

print(f1)
