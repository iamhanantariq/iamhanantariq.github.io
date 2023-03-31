# TODO imports
from cs50 import get_int
from math import ceil

# Globals
number = get_int("Number: ")
n = number
cardlen = ceil(len(str(n))/2)

# Main for determine front end
def main():
    global n
    if n // 1000000000000000 == 4:
        if algo():
            print("VISA")
        else:
            print("INVALID")
    elif n // 1000000000000 == 4:
        if algo():
            print("VISA")
        else:
            print("INVALID")
    elif n // 100000000000000 >= 51 and n // 100000000000000 <= 55:
        if algo():
            print("MASTERCARD")
        else:
            print("INVALID")
    elif n // 10000000000000 == 34 or n // 10000000000000 == 37:
        if algo():
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")

# Luhn's algorithim for each scenario
def algo():
    s = 0
    f = 0
    for i in range(1,cardlen+1):
        global n
        s = s + n % 10
        n = n // 10
        r = n % 10
        n = n // 10
        x = r * 2
        f = f + x // 10 + x % 10
    sum = s + f
    if sum % 10 == 0:
        return True
    else:
        return False

main()