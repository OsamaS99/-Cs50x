# TODO
import sys
import csv
from cs50 import SQL


if(len(sys.argv) != 2 ) :
    sys.exit(1)
open("students.db","w").close()
db = SQL("sqlite:///students.db")

db.execute("CREATE TABLE students (first TEXT , middle TEXT , last TEXT , house TEXT , birth NUMERIC)")

with open(sys.argv[1] , "r") as file :
    reader = csv.DictReader(file)
    for row in reader :
        name = row["name"]
        name_splitted = name.strip().split(" ")
        first , middle , last = ("",""  ,"")
        if(len(name_splitted) == 3 ) :
            first , middle , last = name_splitted
            print((first , middle , last))
        elif(len(name_splitted) == 2 ) :
            first,last = name_splitted
            middle = None
            print((first , middle , last))
        
        db.execute("INSERT INTO students (first , middle, last , house , birth ) VALUES (? , ? , ? , ? , ?)" , first , middle , last , row["house"] , int(row["birth"]))