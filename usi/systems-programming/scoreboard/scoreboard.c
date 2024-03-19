// MOST DIFFICULT
// input:
// team1 team2 score1 score2
// team names only ascii, scores non negative integers
// each winning team get 3 points
// ties = 1 point for both
// output:
// descreasing order by score and team names
// team name, score, #gamesplayed
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_TEAMS 10
#define MAX_TEAMNAME_LEN 20
#define WIN 3
#define TIE 1

struct team {
  char name[MAX_TEAMNAME_LEN + 1];
  int score;
  int games;
};

struct team_array {
    struct team * teams;
    int count;
    int max_count;
};

struct team * get_team(struct team_array * T, const char * name) {
    // look for team
    for (int i = 0; i < T->count; i++) {
        if (strcmp(T->teams[i].name, name) == 0) {
            // found
            return T->teams + i;    // pointer arithmatic
        }
    }

    // create new team if not at maximum
    if (T->count < T->max_count) {
        struct team * newteam = T->teams + T->count;
        if (!newteam) return 0;
        strcpy(newteam->name, name);
        newteam->games = 0;
        newteam->score = 0;
        T->count += 1;
        return newteam;
    } else {
        fprintf(stderr, "too many teams\n");
        return 0;
    }
}

int compare_teams(struct team * a, struct team * b) {
    return a->score > b->score || (a->score == b->score && strcmp(a->name, b->name) < 0);
}

int print_scores(struct team_array * T) {
    struct team ** teams = malloc(sizeof(struct team *) * T->count);
    if (!teams) return 0;
    // insertion sort
    for (int i = 0; i < T->count; i++) {
        //by default insert the team
        teams[i] = T->teams + i;
        for (int j = i; j > 0 && compare_teams(teams[j], teams[j-1]); j--) {
            struct team * tmp = teams[j];
            teams[j] = teams[j-1];
            teams[j-1] = tmp;
        }
    }

    //print
    for (int i = 0; i < T->count; i++) {
        if (printf("%s %d %d\n", teams[i]->name, teams[i]->score, teams[i]->games) < 3) {
            free(teams);
            return 0;
        }
    }

    free(teams);
    return 1;
}

int main(int argc, char * argv[]) {
    //create teams structure and setup
    struct team_array T;
    T.count = 0;
    T.max_count = MAX_TEAMS;
    if (argc > 1) {
        T.max_count = atoi(argv[1]);
    }
    T.teams = malloc(sizeof(struct team) * T.max_count);
    if (!T.teams) return EXIT_FAILURE;

    // start reading teams
    char teamname1[MAX_TEAMNAME_LEN + 1];
    char teamname2[MAX_TEAMNAME_LEN + 1];
    int score_a, score_b;
    int res;
    while ((res = scanf("%20s %20s %d %d", teamname1, teamname2, &score_a, &score_b)) == 4) {
        // using method that get or create automatically the teams
        struct team * team1 = get_team(&T, teamname1);
        struct team * team2 = get_team(&T, teamname2);
        if (!team1 || !team2) {
            free(T.teams);    // free the teams
            return EXIT_FAILURE;
        }

        // update games played and scores
        team1->games += 1;
        team2->games += 1;
        if (score_a > score_b) {
            team1->score += WIN;
        } else if (score_a < score_b) {
            team2->score += WIN;
        } else {
            team1->score += TIE;
            team2->score += TIE;
        }
    }

    if (res == EOF && print_scores(&T)) {
        free(T.teams);
        return EXIT_SUCCESS;
    } else {
        free(T.teams);
        return EXIT_FAILURE;
    }
}
