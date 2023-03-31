# TODO take height, nest for loop for printing

from cs50 import get_int

#fake do-while
while (True):
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

#nested for loop
for i in range(height):
    for j in range(height - i - 1):
        print(" ",end="")
    print("#" * (i + 1), end="  ")
    print("#" * (i + 1))