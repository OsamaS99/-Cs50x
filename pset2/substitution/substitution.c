#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

string lower_case (string input) {
    char * cpy  = (char *)malloc(sizeof(char) * (strlen(input) +1) )  ;
    strcpy(cpy , input);
    for(int i = 0 , n = strlen(cpy) ; i < n ; i ++) {
      cpy[i] = tolower(cpy[i]) ;
    }
    return cpy ;
}
string upper_case (string input) {
    char * cpy  = (char *)malloc(sizeof(char) * (strlen(input) +1) ) ;
    strcpy(cpy , input);
    for(int i = 0 , n = strlen(cpy) ; i < n ; i ++) {
      cpy[i] = toupper(cpy[i]) ;
    }
    return cpy ;
}
bool contain_number (string input) {
    for (int i = 0 , n = strlen(input) ; i < n ; i++ ) {
        if(!isalpha(input[i])) {
            return true ;
        }
    }
    return false;
}
bool repeated (string input) {
    input = lower_case(input) ;
    for(int i = 0  , n = strlen(input) ; i < n; i++) {
        for(int j = i+1 ; j < n ; j++) {
            if(input[i] == input[j]) {
                return true ;
            }
        }
    }
    return false ;
}
bool check_key(int argc , string argv[]) {
    if (argc == 1) {
        printf("Usage: ./substitution key\n");
        return false ;
    }else if(strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return false ;
    }else if (contain_number(argv[1])) {
         printf("Key must only contain alphabetic characters.\n");
        return false ;
    }else if(repeated(argv[1])) {
        printf("Key must not contain repeated characters.\n");
        return false ;
    }else{
        return true;
    }
}

int main (int argc , string argv[])  {
    if (!check_key(argc , argv)) {
        return 1;
    }
    string upper_key = upper_case(argv[1]);
    string lower_key = lower_case(argv[1]);
    string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower_alpha = "abcdefghijklmnopqrstuvwxyz";
    string plain = get_string("plaintext: ");
    for (int i = 0  , n = strlen(plain) ; i < n ; i++) {

        if(isupper(plain[i])) {
            char * indexp_u = strchr(upper_alpha , plain[i]);
            int index_u = indexp_u - upper_alpha;
            plain[i] = upper_key[index_u] ;
        }else if (islower(plain[i])) {
            char * indexp_l = strchr(lower_alpha , plain[i]);
            int index_l = indexp_l - lower_alpha;
            plain[i] = lower_key[index_l] ;
        }

    }
    printf("ciphertext: %s\n",plain);
    return 0;
}