#include "menu_module.h"
#include "page_game_select.h"

char* game_select_menus[] = {
		"1. Tetris",
		"2. Puzzle 2048",
		"3. Shooting 2024",
		"4. Exit"
};

void game_select_page_menu_select(int cur_menu_selected) {
	if (cur_menu_selected == 3) {
		cur_menu_selected = tetris;
		set_cur_step(init_step);
		return;
	}

	set_cur_game(cur_menu_selected + 1);
	switch (cur_menu_selected + 1) {
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

void initialize_game_select_page_map() {
	int title_len = strlen(GAME_SELECT_PAGE_TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 8) / 2;
	int menu_start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 4; i++) {

		char cur_str_len = strlen(game_select_menus[i]);

		for (int j = 0; j < cur_str_len + 1; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}