
import math

def show_menu():
    
    print("--- Meniu principal ---")
    print("1. Citeste o lista de numere intregi")
    print("2. Afisati lista citita")
    print("3. Gasirea secventei de lungime maxima cu proprietatea ca toate elementele sunt egale")
    print("4. Gasirea secventei de lungime maxima cu proprietatea ca diferentele dintre doi termeni consecutivi au semne contrare, doi cate doi")
    print("5. Gasirea secventei de lungime maxima cu suma maxima")
    print("6. Iesire din aplicatie \n")

#1. Citeste o lista de numere intregi
def read_list():

    global numbers
    numbers = []

    global list_length
    list_length = input("Introduceti lungimea listei: ")
    if not list_length.isnumeric():
        print("Nu ati introdus un numar valid! Va rugam incercati din nou. \n")
        return 

    else:
        list_length = int(list_length)
        print("Introduceti elementele listei:")
        
        values = input()
        numbers = [int(val) for val in values.split()][:list_length]

#2. Afisati lista citita            
def show_list():

    if not numbers:
        print("Lista este goala! Cititi mai intai o lista (optiunea 1).")

    else:
        print("Lista curenta este: ")
        print(numbers,"\n")

#3. Gasirea secventei de lungime maxima cu proprietatea ca toate elementele sunt egale
def equal_val_seq():

    if not numbers:
        print("Lista este goala! Cititi mai intai o lista (optiunea 1).")

    else:

        global list_length

        index_start = 0
        max_index_start = 0
        max_index_stop = 0
        
        max_equals_length = 1
        equals_length = 1

        for index in range(1,list_length):
            if numbers[index] == numbers[index - 1]:
                equals_length += 1
                
            else:
                if equals_length > max_equals_length:
                    max_equals_length = equals_length
                    max_index_start = index_start
                    max_index_stop = index - 1

                index_start = index
                equals_length = 1

        if equals_length > max_equals_length:
            max_equals_length = equals_length
            max_index_start = index_start
            max_index_stop = index

        print("Secventa de lungime maxima cu proprietatea ca toate elementele sunt egale este:")
        print(numbers[max_index_start:max_index_stop + 1])

#4. Gasirea secventei de lungime maxima cu proprietatea ca diferentele dintre doi termeni consecutivi au semne contrare, doi cate doi
def sign_diff_seq():

    global list_length

    if not numbers:
        print("Lista este goala! Cititi mai intai o lista (optiunea 1).")

    else:

        index_start = 0
        max_index_start = 0
        max_index_stop = 0

        max_diff_length = 1
        diff_length = 1

        for index in range(2,list_length):
            if numbers[index] - numbers[index - 1] > 0 and numbers[index - 1] - numbers[index - 2] < 0:
                diff_length += 1
            elif numbers[index] - numbers[index - 1] < 0 and numbers[index - 1] - numbers[index - 2] > 0:
                diff_length += 1
            else:
                if diff_length > max_diff_length:
                    max_diff_length = diff_length
                    max_index_start = index_start
                    max_index_stop = index - 1

                index_start = index - 1
                diff_length = 1

        if diff_length > max_diff_length:
            max_diff_length = diff_length
            max_index_start = index_start
            max_index_stop = index

        print("Secventa de lungime maxima cu proprietatea ca diferentele dintre doi termeni consecutivi au semne contrare, doi cate doi, este: ")
        print(numbers[max_index_start : max_index_stop + 1])

def max_sum_seq():

    global list_length

    if not numbers:
        print("Lista este goala! Cititi mai intai o lista (optiunea 1).")

    else:

        max_index_start = 0
        max_index_stop = 0

        max_suma = -math.inf
        
        for index1 in range(list_length):
            suma = 0
            for index2 in range(index1, list_length):
                suma = suma + numbers[index2]

                if suma > max_suma:
                    max_suma = suma
                    max_index_start = index1
                    max_index_stop = index2

                if suma == max_suma and index2 - index1 > max_index_stop - max_index_start:
                    max_index_start = index1
                    max_index_stop = index2

        print("Secventa de lungime maxima cu proprietatea ca are suma maxima este: ")
        print(numbers[max_index_start:max_index_stop + 1])

def main():

    global numbers
    numbers = []

    while True:
        show_menu()
        option = input("Alege o optiune: ")
        print()

        if option == "1":
            read_list()

        elif option == "2":
            show_list()

        elif option == "3":
            equal_val_seq()

        elif option == "4":
            sign_diff_seq()

        elif option == "5":
            max_sum_seq()

        elif option == "6":
            print("La revedere!")
            break

        else:
            print("Optiune invalida! Va rugam incercati din nou.")
            

if __name__ == "__main__":
    main()
