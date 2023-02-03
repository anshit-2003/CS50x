import cs50
# While loop to reject invalid input
while True:
    try:
        change = cs50.get_float("Change owed: ")
        # Change dollars to cents
        if (change > 0):
            change = change * 100
            break
        elif (change < 0):
            continue
    except ValueError:
        continue
# Quarters Formula
quarters = int(change / 25)
change = change % 25
# Dimes Formula
dimes = int(change / 10)
change = change % 10
# Nickels Formula
nickels = int(change / 5)
change = change % 5
# Pennies Formula
pennies = int(change / 1)
# Print total number of Coins
print(quarters+dimes+nickels+pennies)