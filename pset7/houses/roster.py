# TODO
import csv
from cs50 import SQL
import sys

if(len(sys.argv) != 2) :
    sys.exit(1)

db = SQL("sqlite:///students.db")
output_dict = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first;", sys.argv[1])

for dic in output_dict :
    first , last = (dic["first"] , dic["last"])
    middle = dic["middle"]
    birth = dic["birth"]
    if(middle == None) :
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")