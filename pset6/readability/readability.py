
text = input("Text: ")

words = 1
sentences = 0
letters = 0

for char in text :
    if(char == "!" or char == "?" or char ==".") :
        sentences += 1
    elif(char == " ") :
        words += 1
    elif(char.isalpha() == True) :
        letters += 1

L = 100.0 * (float(letters) / float(words))
S= 100.0 * (float(sentences) / float(words) )

grade = 0.0588 * L - 0.296 * S - 15.8
grade = round(grade)

if(grade >= 16 ) :
    print("Grade 16+")
elif(grade < 1) :
    print("Before Grade 1")
else :
    print(f"Grade {grade}")
    