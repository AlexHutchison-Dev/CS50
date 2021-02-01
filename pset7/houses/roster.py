# TODO
import cs50
import sys

db = cs50.SQL("sqlite:///students.db")

if len(sys.argv) == 2:
    houses = ["Ravenclaw", "Hufflepuff", "Gryffindor", "Slytherin"]
    house = sys.argv[1]
    if house not in houses:
        print("Please enter valid house name")
        sys.exit()
    query = ('SELECT * from students WHERE house = "{}" ORDER BY last, first'.format(house))
    studentData = db.execute(query)

    students = []
    for student in studentData:
        first = student["first"]
        last = student["last"]
        birth = student["birth"]
        if student["middle"]:
            middle = student["middle"]
            students.append("{} {} {} born {}".format(first, middle, last, birth))
        else:
            students.append("{} {} born {}".format(first, last, birth))
    for student in students:
        print(student)


else:
    print("usage: python roster.py <house name>")