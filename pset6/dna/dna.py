import csv
import sys

def find (datas , STR) :
    for person in datas.keys():
        if (datas[person] == STR):
            return person
    return "No Match"


csv_data = list()
sequence_data = ""

with open(sys.argv[1] , "r") as csv_file :
    csv_data = list(csv.reader(csv_file))

with open(sys.argv[2] , "r") as dna_file :
    sequence_data = dna_file.read().strip()

possible_STR = csv_data[0][1:]

STR = {}
datas = {}
for person in csv_data[1:] :
    name = person[0]
    name_STR = {}
    for dat , str_name  in zip(person[1:] , possible_STR) :
        name_STR[str_name] = int(dat)
    datas[name] = name_STR

for str in possible_STR :
    STR[str] = 0

for str in possible_STR :
    for index in range(len(sequence_data)) :
        while (True) :
           if((str * STR[str]) in sequence_data[index: index+len(str * STR[str])]) :
              STR[str] += 1
           else :
              break
    STR[str] -= 1
print(find(datas, STR))


