#include "menu_module.h"
#include "page_difficulty.h"

char* difficulty_menus[] = {
		"1. Advance",
		"2. Challenge",
		"3. Impossible",
		"4. Exit"
};

void difficulty_page_menu_select(int cur_menu_selected) {

	if (cur_menu_selected == 3) {
		cur_menu_selected = 0;
		set_cur_step(init_step);
		return;
	}

	difficulty = cur_menu_selected + 1;
	set_cur_step(tetris_step);
}

void initialize_difficulty_page_map() {

	int title_len = strlen(DIFFICULTY_PAGE_TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[TITLE_X][title_start_y + i] = 1;
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
