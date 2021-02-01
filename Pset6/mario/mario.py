from cs50 import get_int

# Get inuput from user
height = get_int("Height: ")

# Validate user input
while True:
    if height < 1 or height > 8:
        height = get_int("Height: ")
    else:
        break

height += 1
row = 1
# itterate over rows
for row in range(1, height):
    # print spaces foe row
    for i in range(1, height - row):
        print(f"_", end="")
    # print blocks in pyramid
    for j in range(0, row):
        print(f"#", end="")
    # print space in middle of pyramid
    print(f"__", end="")
    # print right side of pyramid
    for k in range(0, row):
        print(f"#", end="")
    # print spaces to right of pyrmid
    for l in range(1, height - row):
        print(f"_", end="")
    # print new line
    print("")

    row += 1

