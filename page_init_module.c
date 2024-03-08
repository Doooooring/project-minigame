#include "page_init.h"

char* init_menus[3] = {
		"1. Game Start",
		"2. Rank",
		"3. Exit",
};

void init_page_menu_select(int cur_menu_selected) {
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

void initialize_init_page_map() {
	int title_len = strlen(INIT_PAGE_TITLE);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 6) / 2;
	int menu_start_y = (WIDTH - 16) / 2;

	for (int i = 0; i < 3; i++) {
		char cur_str_len = strlen(init_menus[i]);
		for (int j = 0; j < cur_str_len + 1; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}