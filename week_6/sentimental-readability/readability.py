import cs50
# Get String Input
string = cs50.get_string("Sentence :")
# Initialize Variables
letters = sentences = 0
words = 1
# Loops to count everything
for i in string:
    if ((ord(i) > 64 and ord(i) < 91) or (ord(i) > 96 and ord(i) < 123)):
        letters += 1
    if (ord(i) == 32):
        words += 1
    if (ord(i) == 33 or ord(i) == 46 or ord(i) == 63):
        sentences += 1

L = (letters/words) * 100
S = (sentences/words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)
if (index > 0 and index < 17):
    print("Grade : "+str(index))
elif (index < 0):
    print("Before Grade 1")
else:
    print("Grade 16+")