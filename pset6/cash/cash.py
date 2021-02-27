from cs50 import get_float

cash = get_float("Change owed: ")
while(cash <= 0) :
    cash = get_float("Change owed: ")

penny = 1
dime = 10
quarter = 25
nickel = 5

cents = cash * 100

coins = 0

while (cents > 0) :
    if (int(cents/quarter) != 0 ) :
        coins += int(cents / quarter) 
        cents = cents % quarter
    elif (int(cents / dime) != 0) :
        coins += int(cents / dime) 
        cents = cents % dime
    elif (int(cents / nickel) != 0) :
        coins += int(cents / nickel) 
        cents = cents %  nickel
    elif (int(cents / penny) != 0) : 
        coins += int(cents / penny) 
        cents = cents % penny
        
print(coins)

