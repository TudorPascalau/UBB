number = int(input("Enter number:"))
is_prime = True

if number < 2:
    is_prime = False

else:
    for divizor in range(2,number//2 + 1):
        if(number % divizor == 0):
            is_prime = False

if(is_prime):
    print("Is prime")
else:
    print("Is not prime")
    
    
