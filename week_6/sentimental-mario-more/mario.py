# Loop to take input
while True:
    height = input("Height:")
    # Check weather input is a digit or not
    if (height.isdigit()):
        # Check if the input is between 0 and 8
        if (int(height) > 0 and int(height) <= 8):
            break
        else:
            continue
    else:
        continue
# Printing the pattern
height = int(height)
for i in range(1, height+1):
    print(" "*(height-i) + "#" * i, end='  ')
    print("#" * i)