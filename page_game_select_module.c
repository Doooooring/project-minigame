#include "main.h"

GAME_TYPE cur_game_selected = tetris;

#define GAME_TITLE_X 4
#define GAME_TITLE "Select Game"

char game_menus[4][20] = {
	"1. Tetris",
	"2. Puzzle 2048",
	"3. Shooting 2024",
	"4. Exit"
};

void game_select_up() {
	if (cur_game_selected == 1) return;
	cur_game_selected--;
}

void game_select_down() {
	if (cur_game_selected == 4) return;
	cur_game_selected++;
}

void game_move_step() {

	if (cur_game_selected == 4) {
		cur_game_selected = tetris;
		set_cur_step(init_step);
		return;
	}

	set_cur_game(cur_game_selected);
	switch (cur_game_selected) {
	case (tetris):
		set_cur_step(difficult_select_step);
		break;
	case (puzzle_2048):
		set_cur_step(puzzle_2048_step);
		break;
	case (shooting):
		set_cur_step(shooting_step);
		break;
	}

}

bool get_user_game_input() {
	int input;
	input = _getch();
	switch (input) {
	case (ARROW_DOWN):
	case (ARROW_RIGHT):
		game_select_down();
		break;
	case (ARROW_UP):
	case (ARROW_LEFT):
		game_select_up();
		break;
	case (SPACEBAR):
		game_move_step();
		return false;
	}
	return true;
}


void print_game_title() {
	print_str_row(GAME_TITLE_X, GAME_TITLE);
}

void print_game_menu() {


	int start_x = (MAPHEIGHT - 8) / 2;
	int start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 4; i++) {

		char* cur = game_menus[i];

		if (i + 1 == cur_game_selected) {
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


void set_init_game_select() {


	int title_len = strlen(GAME_TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[GAME_TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 8) / 2;
	int menu_start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 4; i++) {

		char cur_str_len = strlen(game_menus[i]);

		for (int j = 0; j < cur_str_len + 1; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}

