#include <stdio.h>
#include <cs50.h>


int main() {
    int height = 0 ;
    do {
        height = get_int("Height:\n");
    }while(height > 8 || height <= 0);
    for (int i = 1 ; i <= height ; i++) {
        for(int space = 0 ; space < height -i ; space ++ ) {
            printf(" ");
        }
        for (int hash = 0 ; hash < i ; hash++ ) {
            printf("#");
        }
        printf("  ");
        for (int hash = 0 ; hash < i ; hash++ ) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}