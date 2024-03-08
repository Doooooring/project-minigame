#include "page_game_select.h"

int page_game_select() {

	menu* page_game_select_menu = new_Menu(
		4, game_select_step, GAME_SELECT_PAGE_TITLE, game_select_menus, game_select_page_menu_select
	);

	initialize_game_select_page_map();

	execute_background();
	execute_menu(page_game_select_menu);

	stop_background();

	return 0;
}