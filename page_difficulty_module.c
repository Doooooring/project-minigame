#include "main.h"
#include "page_difficulty.h"

#define DIFFICULTY_TITLE_X 4
#define DIFFICULTY_TITLE "Difficulty"

int cur_difficult_selected = 0;

char difficulty_menus[4][20] = {
	"1. Advance",
	"2. Challenge",
	"3. Impossible",
	"4. Exit"
};

void difficulty_select_up() {
	if (cur_difficult_selected == 0) return;
	cur_difficult_selected--;
}

void difficulty_select_down() {
	if (cur_difficult_selected == 3) return;
	cur_difficult_selected++;
}

void difficulty_move_step() {

	if (cur_difficult_selected == 3) {
		cur_difficult_selected =  0;
		set_cur_step(init_step);
		return;
	}

	difficulty = cur_difficult_selected + 1;
	set_cur_step(tetris_step);
}

bool get_user_difficulty_input() {
	int input;
	input = _getch();
	switch (input) {
	case (ARROW_DOWN):
	case (ARROW_RIGHT):
		difficulty_select_down();
		break;
	case (ARROW_UP):
	case (ARROW_LEFT):
		difficulty_select_up();
		break;
	case (SPACEBAR):
		difficulty_move_step();
		return false;
	}
	return true;
}

void print_difficulty_title() {
	print_str_row(DIFFICULTY_TITLE_X, DIFFICULTY_TITLE);
}


void print_difficulties() {

	int start_x = (MAPHEIGHT - 8) / 2;
	int start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 4; i++) {

		char* cur = difficulty_menus[i];

		if (i == cur_difficult_selected) {
			print_str(start_x + 2 * i, start_y, COLOR_RED);
			print_str(start_x + 2 * i, start_y, cur);
			printf("%s", COLOR_RESET);
		}
		else {
			print_str(start_x + 2 * i, start_y, COLOR_RESET);
			print_str(start_x + 2 * i, start_y, cur);
		}
	}
}

void set_difficulty_page() {


	int title_len = strlen(DIFFICULTY_TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[DIFFICULTY_TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 8) / 2;
	int menu_start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 4; i++) {

		char cur_str_len = strlen(difficulty_menus[i]);

		for (int j = 0; j < cur_str_len + 1; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}

