from cs50 import get_string


# Get text from user
s = get_string("Text: ")

words = 0
inword = False
letters = 0
words = 0
sentences = 0


# Itterate over characters in user inputted string
for c in s:

    # stop sample if we hit 100 words
    if (words > 100):
        break

    # check for alpha and deal as apropriate
    if c.isalpha():

        if inword == False:
            inword = True
            words += 1

        letters += 1
    # check for space and deal as apropriate
    if (c == " "):

        if inword:
            inword = False

    # check for sentence end and deal as appropriate
    if (c == "." or c == "!" or c == "?"):

        sentences += 1

# Initialise worfactor variable and if text has less than 100 words secipher factor for multiplication
wordfacor = 0

if (words < 100):
    wordfactor = 100 / words

# calculate averages per 100 words
meanletters = letters * wordfactor
meansentence = (sentences * wordfactor)

# calculate grade
grade = 0.0588 * meanletters - 0.296 * meansentence - 15.8


# Print relevant grade statement for result
if (grade > 0 and grade < 17):

    print(f"Float Grade: {grade}")
    print(f"Grade: {round(grade)}")

elif (grade < 1):

    print(f"Before Grade 1")

else:

    print(f"Grade: 16+")

