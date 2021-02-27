#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cs50.h>
int main() {
    string text = get_string("Text:\n");
    int  words = 1;
    int  sentences = 0;
    int  letters = 0;
    for (int i = 0, n = strlen(text); i <= n; i++) {
        if (isalpha(text[i])) {
            letters += 1;
        }
        else if (text[i] == '!' || text[i] == '?' || text[i] == '.') {
            sentences += 1;
        }
        else if (text[i] == ' ') {
            words += 1;
        }
    }

    float  L =  100 * ((float)(letters) / (float)(words));
    float S = 100 * ((float)(sentences) / (float)(words));
    double index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);
    if (index > 16) {
        printf("Grade 16+\n");
    }
    else if (index < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n", (int)(index));
    }
    return 0;
}