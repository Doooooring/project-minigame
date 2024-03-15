#include "page_init.h"

int page_init() {

	menu* page_init_menu = new_Menu(
		3, 
		init_step, 
		INIT_PAGE_TITLE, 
		init_menus, 
		init_page_menu_select
	);

	initialize_page_map(page_init_menu);
	execute_background();
	execute_menu(page_init_menu);

	stop_background();

	return 0;
}
