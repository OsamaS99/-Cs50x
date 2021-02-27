from cs50 import get_int
height = get_int("Height: ")

if(int(height) > 8 or int(height) < 1 ) :
    height = get_int("Height: ")

height = int(height)

for line in range(1 , height+1):
    spaces = height - line
    for space in range(spaces) :
        print(" ",end = "")
    for brick in range(line) :
        print("#", end = "")
    print("  ",end = "")
    for brick in range(line) :
        print("#", end = "")
    print("")
