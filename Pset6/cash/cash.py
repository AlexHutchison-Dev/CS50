from cs50 import get_float
import math


def main():
    # Declare global variables
    coins = 0
    change = 0
    coinvalue = [25, 10, 5, 1]

    # Get user input for cahnge owed
    while (change <= 0):

        change = round(get_float("Change owed: ") * 100)

    # while change owed cycle through coin values and divide
    while (change > 0):

        for i in range(0, len(coinvalue)):
            coins += int(calc_coins(change, coinvalue[i]))
            change = calc_change(change, coinvalue[i])
    print(f"{coins}")


# calculate numbe of coins of given value posible to give for change owed
def calc_coins(change, value):

    count = change / value
    return count


# calculate remaining change after macimum number of coins of current value given
def calc_change(change, value):

    change = int(change % value)
    return change


if __name__ == "__main__":

    main()
