def is_Prime(x):
    is_prime = True
    if(x < 2):
        is_prime = False

    for divizor in range(2, x//2 + 1):
        if(x % divizor == 0):
            is_prime = False

    return is_prime


number = int(input("Enter number here: "))

result = number + 1

while(is_Prime(result) == False):
    result = result + 1

print(result)
