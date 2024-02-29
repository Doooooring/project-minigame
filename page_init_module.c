#include "main.h"

#define TITLE_X 4

#define TITLE "DAOU MINI GAME"

char menus[3][20] = {
		"1. Game Start",
		"2. Rank",
		"3. Exit",
};

int cur_menu_selected = 0;

void init_cur_menu_selected() {
	cur_menu_selected = 0;
}

void menu_select_up() {
	if (cur_menu_selected == 0) return;
	cur_menu_selected--;
}

void menu_select_down() {
	if (cur_menu_selected == 2) return;
	cur_menu_selected++;
}

void menu_move_step() {
	switch (cur_menu_selected) {
		case(0):
			cur_step = game_select_step;
			break;
		case(1):
			cur_step = ranking_step;
			break;
		case(2):
			exit("게임이 종료되었습니다.");
	}

}

bool get_user_menu_input() {
	int input;
	input = _getch();
	switch (input) {
	case (ARROW_DOWN):
	case (ARROW_RIGHT):
		menu_select_down();
		break;
	case (ARROW_UP):
	case (ARROW_LEFT):
		menu_select_up();
		break;
	case (SPACEBAR):
		menu_move_step();
		return false;
	}
	return true;
}

void print_init_title() {
	int start_x = 4;

	print_str_row(start_x, "DAOU MINI GAME");
}


void print_menu() {



	int start_x = (MAPHEIGHT - 6) / 2;
	int start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 3; i++) {

		char* cur = menus[i];


		if (i == cur_menu_selected) {
			printf("%s", COLOR_RED);
			print_str(start_x + 2 * i, start_y, cur);
			printf("%s", COLOR_RESET);
		}
		else {
			printf("%s", COLOR_RESET);
			print_str(start_x + 2 * i, start_y, cur);
		}

	}

}


void set_init_page_map() {


	int title_len = strlen(TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 6) / 2;
	int menu_start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 3; i++) {

		char cur_str_len = strlen(menus[i]);

		for (int j = 0; j < cur_str_len + 1; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}

