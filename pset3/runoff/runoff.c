#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

#define MAX_CANDIDATES 4
#define MAX_VOTERS 10


typedef struct {
    string name ;
    int votes ;
    bool eliminated ;

}candidate ;


candidate candidates [MAX_CANDIDATES];
int preferences [MAX_VOTERS][MAX_CANDIDATES];
int voter_count , candidate_count;


bool vote(int voter , int rank , string name) ;
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min) ;
void eliminate(int min);

int main (int argc , string argv [] ) {
    if (argc-1 > MAX_CANDIDATES ) {
        return 1 ;
    }
    candidate_count = argc-1 ;
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS) {
        return 1 ;
    }
    for (int i = 0 ; i < voter_count ; i++) {
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false ;
    }
    for(int i = 0 ; i < voter_count  ; i++) {
        for (int j = 0 ; j < candidate_count ; j++) {
            string candidate_name = get_string("Rank %i",j+1);
            if (!vote(i,j,candidate_name)) {
                return 1 ;
            }
        }
    }
    while (!print_winner()) {
        tabulate () ;
        int min_votes = find_min();
        if(!is_tie(min_votes)) {
            eliminate(min_votes);
        }
    }
}

bool vote (int voter , int rank , string name) {
    int match_index = 0 ;
    for(int i = 0  ; i < candidate_count ; i++) {
        if(candidates[i].name == name) {
            match_index += i;
        }
    }
    if (match_index == 0 ) {
        return false ;
    }
    preferences[voter][rank] = match_index ;
    return true;
}

void tabulate(void) {
    for (int i = 0 ; i < voter_count ; i++) {
        for (int j = 0 ; j < candidate_count ; j++) {
            if(candidates[preferences[i][j]].eliminated){
                continue;
            }else{
                candidates[preferences[i][j]].votes ++;
                break;
            }
        }
    }
}
bool print_winner(void) {
    int majority ;
    if (voter_count % 2 == 0) {
        majority = (voter_count/2)+1;
    }else {
        majority = (voter_count +1) /2 ;
    }
    for (int i = 0 ; i < candidate_count ; i++) {
        if (candidates[i].votes >= majority){
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false ;
}

int find_min(void) {
    int min_votes = MAX_VOTERS ;
    for (int i = 0 ; i < candidate_count ;i++ ) {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes) {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes ;
}
bool is_tie(int min)  {
    int remaining = 0 ;
    int min_counter = 0;
    for (int i = 0 ; i< candidate_count ; i++) {
        if(!candidates[i].eliminated) {
            remaining ++;
        }
        if (candidates[i].votes == min) {
            min_counter ++;
        }
    }
    if(remaining == min_counter) {
        return true;
    }
    return false ;
}

void eliminate (int min) {
    for (int i = 0  ; i < candidate_count  ; i++) {
        if (candidates[i].votes == min) {
            candidates[i].votes = 0 ;
            candidates[i].eliminated = true;
        }
    }
}
