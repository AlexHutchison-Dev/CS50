# TODO
import csv
import cs50
import sys

open(f"students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC);")

if len(sys.argv) != 2:
    print("usage: python import.py <source data>")
    sys.exit()

with open(sys.argv[1], "r") as file:

    reader = csv.DictReader(file)

    for index, row in enumerate(reader):

        house = row["house"]
        birth = int(row["birth"])
        names = row["name"].split(" ")
        first = names[0]
        if len(names) > 2:
            middle = names[1]
            last = names[2]
            db.execute("INSERT into students (first, middle, last,  house, birth) VALUES (?,?,?,?,?)", first, middle, last, house, birth)
            continue
        else:
            last = names[1]
            db.execute("INSERT into students (first, last,  house, birth) VALUES (?,?,?,?)",  first, last, house, birth)


