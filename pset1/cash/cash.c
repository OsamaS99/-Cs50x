#include <stdio.h>
#include <cs50.h>
#include <math.h>



int main () {
    const int quarter = 25 ;
    const int dime  = 10 ;
    const int nickel = 5 ;
    const int penny = 1 ;
    float change = 0.0;
    do {
        change = get_float("Change owed:\n");
    }while(change <= 0.0);

    int cents = round(change * 100) ;
    int coins = 0 ;
    while (cents > 0) {
        if (cents/quarter != 0 ) {
            coins += cents / quarter ;
            cents = cents % quarter;
        }else if (cents / dime != 0) {
            coins += cents / dime ;
            cents = cents % dime;
        }else if (cents / nickel != 0){
            coins += cents / nickel ;
            cents = cents %  nickel;
        }else if (cents / penny != 0) {
            coins += cents / penny ;
            cents = cents % penny;
        }

    }
    printf ("%i\n" , coins);
    return 0;
}