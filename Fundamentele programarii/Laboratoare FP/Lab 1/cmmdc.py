number_1 = int(input("Enter first number: "))

number_2 = int(input("Enter second number: "))

r = number_1 % number_2

while(r):
    number_1 = number_2
    number_2 = r
    r = number_1 % number_2

print("cmmdc este",number_2)
