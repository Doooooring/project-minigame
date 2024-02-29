#include "main.h"
#include "page_ranking.h"

#define INITIAL_ROW 6

int cursor = 0;
int cur_rank = -1;
int cur_page = 0;
char cur_inputs[4] = "";

char file_arr[5][20] = { ADVANCE_FILE, CHALLENGE_FILE, IMPOSSIBLE_FILE, PUZZLE_2048_FILE, SHOOTING_FILE };
char game_names[3][20] = { "Tetris", "2048", "Shooting" };

char cur_file[20] = ADVANCE_FILE;

int get_file_num(GAME_TYPE game, DIFFICULTY difficulty) {
    switch (game) {
    case (tetris):
        return difficulty - 1;
    case (puzzle_2048):
        return 3;
    case (shooting):
        return 4;
    }
}

void parse_info_from_file(int file_num, int buffer[2]) {

    if (file_num == 4) {
        buffer[0] = shooting;
        buffer[1] = 0;
    }
    else if (file_num == 3) {
        buffer[0] = puzzle_2048;
        buffer[1] = 0;
    }
    else {
        buffer[0] = tetris;
        buffer[1] = file_num + 1;
    }

}

void set_cur_file(int file_num) {
    cur_page = file_num;
    cur_ranking = rankings[file_num];
    strcpy(cur_file, file_arr[file_num]);
}

void load_step4_data() {
    int file_num = get_file_num(cur_game, difficulty);
    set_cur_file(file_num);
    if (score > 0) add_rank(score);
}

void step4_initialize() {
    cursor = 0;
    cur_rank = -1;
    int cur_page = 0; 
    char* tmp = cur_inputs;
    while (*tmp) {
        *tmp = NULL;
        tmp++;
    }
}

// cur_ranking 저장
bool save_rank(int file_num) {
    FILE* fp; 
    fp = fopen(cur_file, "wb");
    if (fp == NULL) { 
        printf("파일 열기 실패! \n");
        return false;
    }

    fwrite(rankings[file_num], sizeof(rank_info), TOP_RANK, fp); 
    fclose(fp);
    return true;
}

// cur_ranking 불러오기
bool load_rank() 
{
    int size;

    FILE* fp = fopen(ADVANCE_FILE, "rb");
    if (fp == NULL)
    {
        printf("파일 열기 실패! \n");
        return false;
    }

   size = fread(advance_rankings, sizeof(rank_info), TOP_RANK, fp); 

   fp = fopen(CHALLENGE_FILE, "rb");
   if (fp == NULL)
   {
       printf("파일 열기 실패! \n");
       return false;
   }

   size = fread(challenge_rankings, sizeof(rank_info), TOP_RANK, fp);


   fp = fopen(IMPOSSIBLE_FILE, "rb");
   if (fp == NULL)
   {
       printf("파일 열기 실패! \n");
       return false;
   }

   size = fread(impossible_rankings, sizeof(rank_info), TOP_RANK, fp);

   fp = fopen(PUZZLE_2048_FILE, "rb");
   if (fp == NULL)
   {
       printf("파일 열기 실패! \n");
       return false;
   }

   size = fread(puzzle_2048_rankings, sizeof(rank_info), TOP_RANK, fp);


   fp = fopen(SHOOTING_FILE, "rb");
   if (fp == NULL)
   {
       printf("파일 열기 실패! \n");
       return false;
   }

   size = fread(shooting_rankings, sizeof(rank_info), TOP_RANK, fp);


   fclose(fp);

   rankings[0] = advance_rankings;
   rankings[1] = challenge_rankings;
   rankings[2] = impossible_rankings;
   rankings[3] = puzzle_2048_rankings;
   rankings[4] = shooting_rankings;

    return true;
}

// 새로운 rank 추가하기
bool add_rank(int score) {

    int r = -1;
    
    for (int i = 0; i < TOP_RANK; i++) {
        if (score > (*cur_ranking + i)->score) {
            r = i;
            break;
        }
    }
    
    if (r == -1) return false;

    for (int i = TOP_RANK - 1; i > r; i--) {
        rank_cpy(i - 1, i);
        (*cur_ranking + i)->rank = i + 1;
    }

    char s[9]; 
    
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    strftime(s, sizeof(s), "%y%m%d", tm_info);
    
    rank_info new_rank = { r + 1, "", score, ""};
    strcpy(new_rank.datetime, s);

    *(*cur_ranking + r) = new_rank;
    cur_rank = r;

    return true;
}

// rank 업데이트
bool update_rank(int rank) {
    strcpy((*cur_ranking + rank)->name, cur_inputs);
    return true;
}

void print_rank_info(int x, rank_info* info) {
    char str_to_print[30] = "";
 
    char rank_str[3];

    _itoa(info->rank, rank_str, 10);
    if (strlen(rank_str) < 2) {
        char temp[3] = "0";
       strcat(temp, rank_str);
       strcpy(rank_str, temp);
    }

    char name_str[NAME_LENGTH + 1];
    strcpy(name_str, info->name);

    while (strlen(name_str) < NAME_LENGTH) {
       strcat(name_str, "-");
    }

    char score_str[8];
    if (info->score > 99999) info->score = 99999;
    _itoa(info->score, score_str, 10);
    while (strlen(score_str) < 5) {
        char temp[11] = "0";
        strcat(temp, score_str);
        strcpy(score_str, temp);
    }
    char date_str[9];
    strcpy(date_str, info->datetime);
    
    strcat(str_to_print, rank_str);
    strcat(str_to_print, " ");
    strcat(str_to_print, name_str);
    strcat(str_to_print, " ");
    strcat(str_to_print, score_str);
    strcat(str_to_print, " ");
    strcat(str_to_print, date_str);
    print_str_row(x, str_to_print);

}

void print_title() {

    erase_line(2);

    char title_to_print[20] = "";

  
    if (cur_page == 0) {
        strcat(title_to_print, "  ");
    }
    else {
        strcat(title_to_print, "< ");
    }
   
    int page_title_info[2];

    parse_info_from_file(cur_page, page_title_info);

    strcat(title_to_print, game_names[page_title_info[0] - 1]);

    if (page_title_info[0] == tetris) {

        strcat(title_to_print, " ");
        char c[2] = " ";
        _itoa(page_title_info[1], c, 10);
        strcat(title_to_print, c);
    }
 

    
    if (cur_page == 4) {
        strcat(title_to_print, "  ");
    }
    else {
        strcat(title_to_print, " >");
    }
    
    print_str_row(2, title_to_print);

}

void print_ranks() {
    for (int i = 0; i < TOP_RANK; i++) {
        print_rank_info(INITIAL_ROW + 2 * i, *cur_ranking + i);
    }
}

void print_input() {

    erase_line(INITIAL_ROW + 2 * TOP_RANK + 2);

    char input_to_show[20] = "";    

    strcpy(input_to_show, cur_inputs);
    
    if (strlen(cur_inputs) == 3) {
        strcat(input_to_show, " SAVE? : SPACE");
        print_str_row(INITIAL_ROW + 2 * TOP_RANK + 2, input_to_show);
    }
    else {
        while (strlen(input_to_show) < 3) {
            strcat(input_to_show, "_");
        }

        int col_to_start = (WIDTH + 2 - 3) / 2;

        print_str_row(INITIAL_ROW + 2 * TOP_RANK + 2, input_to_show);
        print_str(INITIAL_ROW + 2 * TOP_RANK + 2, col_to_start + cursor, COLOR_CYAN);
        print_char(INITIAL_ROW + 2 * TOP_RANK + 2, col_to_start + cursor, input_to_show[cursor]);
        printf("%s", COLOR_RESET);
    }
}

void print_exit_message() {
    erase_line(INITIAL_ROW + 2 * TOP_RANK + 2);
    print_str_row(INITIAL_ROW + 2 * TOP_RANK + 2, "ESC to back");
}


void print_footer() {
    if (score > 0) {
        print_input();
        get_name_input();
    }
    else {
        print_exit_message();
        get_page_input();
    }
}


void save() {
    int file_num = get_file_num(cur_game, difficulty);
    save_rank(file_num);
    init_score();
    step4_initialize();
    erase_line(INITIAL_ROW + 2 * TOP_RANK + 2);
};

void get_name_input() {
    int input;
    input = _getch();
   
    if (input == 8) {
        if (cursor == 0 || cur_inputs[cursor - 1] == NULL) return;
        cur_inputs[cursor - 1] = NULL;
        update_rank(cur_rank);
        cursor--;
    }
    else if (input >= 33 && input < 126) {
        if (cursor >= 3) return;
        cur_inputs[cursor] = input;
        update_rank(cur_rank);
        cursor++;
    }
    else if (input == 224) {
        input = _getch();
        switch (input) {
            case (ARROW_RIGHT):
                if (cur_inputs[cursor] == NULL) return;
                cursor++;
                break;
            case (ARROW_LEFT):
                if (cursor == 0) return;
                cursor--;
                break;
            }
    }
    else {
        switch (input) {
            case (SPACEBAR):
                if (strlen(cur_inputs) < 3) return;
                save();
                break;

         }
    }
}

void get_page_input() {
    int input;
    input = _getch();
    if (input == 224) {
        input = _getch();
        switch (input) {
            int page_info[2];
        case (ARROW_RIGHT):
            if (cur_page == 4) return;
            cur_page++;
            set_cur_file(cur_page);
            break;
        case (ARROW_LEFT):
            if (cur_page == 0) return;
            cur_page--;
            set_cur_file(cur_page);
            break;
        }
    }
    else if (input == END) {
        initialize_setting();
    }
}



// rank 복사 용 유틸 함수
void rank_cpy(int prev, int next) {
    rank_info prev_rank = *(*cur_ranking + prev);
    *(*cur_ranking + next) = prev_rank;
}

void set_first_data() {
    for (int n = 0; n < 5; n++) {
        rank_info(*ranks)[TOP_RANK];

        ranks = rankings[n];
        for (int i = 0; i < 10; i++) {
            (*ranks + i)->rank = i + 1;
            strcpy((*ranks + i)->name, "");
            (*ranks + i)->score = 0;
            strcpy((*ranks + i)->datetime, "------");
        }
        set_cur_file(n);
        save_rank(n);
    }
}