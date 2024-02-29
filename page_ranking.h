#include "main.h"

#define TOP_RANK 10
#define NAME_LENGTH 3

#define ADVANCE_FILE "advance.txt"
#define CHALLENGE_FILE "challenge.txt"
#define IMPOSSIBLE_FILE "impossible.txt"
#define PUZZLE_2048_FILE "2048.txt"
#define SHOOTING_FILE "shooting_file.txt"

#ifndef __define_rank_info
    typedef struct {
        int rank; // 가. 순위
        char name[NAME_LENGTH + 1]; // 나. 이름
        int score; // 다. 스코어
        char datetime[10]; // 라. datetime의 경우, 20개면 충분
    } rank_info;
    #define __define_rank_info 1
#endif

char file_arr[5][20];

rank_info (*cur_ranking)[TOP_RANK];

rank_info advance_rankings[TOP_RANK];
rank_info challenge_rankings[TOP_RANK];
rank_info impossible_rankings[TOP_RANK];
rank_info puzzle_2048_rankings[TOP_RANK];
rank_info shooting_rankings[TOP_RANK];

rank_info* rankings[5];

bool save_rank(int file_num);
bool load_rank();
bool add_rank(int score);
bool update_rank(int rank);

void load_step4_data();

void print_title();

void print_ranks();
void print_footer();

void get_name_input();


void get_page_input();

void rank_cpy(int prev, int next);


