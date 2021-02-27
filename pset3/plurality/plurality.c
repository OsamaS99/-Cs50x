#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define MAX 9


typedef struct {
    int votes ;
    string name ;
}candidate;

candidate candidates [MAX] ;

int candidate_count ;

bool vote(string name) ;

void print_winner(void) ;

void set_counter(int cnt){
    candidate_count = cnt;
}


int main (int argc , string argv[]) {
    if(argc > MAX +1) {
       return 1 ;
    }
    set_counter(argc-1);
    for (int i = 1 ; i < argc ;i++ ) {
        candidates[i-1].votes = 0 ;
        candidates[i-1].name  = argv[i];
    }
    int NOV = get_int("Number of voters: ");
    for (int i = 0 ; i < NOV ; i ++) {
        string name = get_string("Vote: ");
        if(!vote(name)) {
            printf("Invalid\n");
        }
    }
    print_winner();
    return 0;

}

bool vote (string cname) {
    for (int i = 0 ; i < candidate_count ; i++) {
        if (strcmp(cname , candidates[i].name) == 0) {
            candidates[i].votes ++;
            return true ;
        }
    }
    return false ;
}


void print_winner (void) {
    int biggest_vote = candidates[0].votes;
    for (int i = 0 ; i < candidate_count ; i++) {
        if(candidates[i].votes > biggest_vote){
            biggest_vote = candidates[i].votes;
        }
    }
    for (int i = 0 ; i < candidate_count ; i++) {
        if(candidates[i].votes  == biggest_vote) {
            printf("%s\n",candidates[i].name);
        }
    }
}