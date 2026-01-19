from cs50 import get_int
number = get_int("Number: ")
length = len(str(number))
def main():
    if  not Luhn_algorithm():
        return print("INVALID")
    first = int(str(number)[0])
    second = int(str(number)[1])
    if (first == 3 and (second == 4 or second == 7) and length == 15):
        return print("AMEX")
    elif (first == 5 and (second == 1 or second == 2 or second == 3 or second == 4 or second == 5) and length == 16):
        return print("MASTERCARD")
    elif (first == 4 and (length == 13 or length == 16)):
        return print("VISA")
    else:
        return print("INVALID")
def Luhn_algorithm():
    num = str(number)[::-1]
    sum = 0
    for i in range(length):
        if (i % 2) == 1:
            if (int(num[i]) * 2) > 9:
                sum += int(num[i]) * 2 - 9
            else:
                sum += int(num[i]) * 2
        else:
            sum += int(num[i])
    if sum % 10 == 0:
        return True
    else:
        return False
main()
