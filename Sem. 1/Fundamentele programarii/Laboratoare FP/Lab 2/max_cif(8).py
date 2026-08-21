
n = int(input("Introduceti numarul: "))

cifre = []

while(n):
    cifre.append(n%10)
    n = n//10

cifre.sort(reverse = True)

result = 0
for cif in range(len(cifre)):
    result = result*10 + cifre[cif]

print(result)
