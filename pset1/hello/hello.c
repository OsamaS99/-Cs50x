#include <stdio.h>
#include <cs50.h>

int main (void) {
    string name = get_string("What Is Your Name ?\n");
    printf("Hello %s\n",name);
    return 0;
}