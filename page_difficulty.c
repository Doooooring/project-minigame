#include "page_difficulty.h"

int page_difficulty() {

	menu* page_difficulty_menu = new_Menu(
		4, 
		difficult_select_step, 
		DIFFICULTY_PAGE_TITLE, 
		difficulty_menus, 
		difficulty_page_menu_select
	);

	initialize_page_map(page_difficulty_menu);
	execute_background();
	execute_menu(page_difficulty_menu);

	stop_background();

	return 0;
}
