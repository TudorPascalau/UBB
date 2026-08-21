def is_Perfect(x):
    Sum = 0
    for divizor in range(1,x):
        if(x % divizor == 0):
            Sum = Sum + divizor

    return Sum == x

number = int(input("Introduceti numar: "))
result = number - 1

while(is_Perfect(result) == False and result > 5):
    result = result - 1

if(result > 5):
    print(result)
else:
    print("Nu exista numar perfect mai mic decat",number)
