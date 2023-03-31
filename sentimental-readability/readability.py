# TODO import library
from cs50 import get_string

text = get_string("Text: ")

w = 0
l = 0
s = 0

# Iterate over each character
for c in text:
    if c == "." or c == "!" or c == "?":
        s += 1
    elif c == " ":
        w += 1
    elif ord(c) >= 65 and ord(c) <= 90 or ord(c) >= 97 and ord(c) <= 122:
        l += 1
w += 1

# Formula to determine grade
cl = round(0.0588 * (l / w * 100) - 0.296 * (s / w * 100) - 15.8)

# Printing strategy
if cl >= 16:
    print("Grade 16+")
elif cl < 1:
    print("Before Grade 1")
else:
    print(f"Grade {cl}")
