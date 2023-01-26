from cs50 import get_int

def loop(i):
    for j in range(i):
        print("#", end="")

height = get_int("Height ")
while height > 8 or height < 1:
    height = get_int("Height ")
width = 1
for i in range(height):
    for j in range(height - width):
        print(" ", end="")
    loop(width)
    print("  ", end="")
    loop(width)
    print()
    width += 1


# TODO