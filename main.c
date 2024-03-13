#include "main.h"

int main() {

	
	cursor_view();


	while (1) {

		init_mem();
		generate_map();
		print_all();

		switch (cur_step) {
			case(init_step):
				page_init();
				break;
			case (game_select_step):
				page_game_select();
				break;
			case(difficult_select_step):
				page_difficulty();
				break;
			case (tetris_step):
				page_tetris();
				break;
			case (puzzle_2048_step):
				page_2048();
				break;
			case (shooting_step):
				page_shooting();
				break;
			case (ranking_step):
				page_ranking();
				break;		
		}
	
		erase_all();
	}

	return 0;
}