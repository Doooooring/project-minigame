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