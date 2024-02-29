#include "main.h"
#include "page_2048.h"


int page_2048() {

	erase_all();
	initiate_2048_arr();

	while (1) {
		generate_rand_num();


		print_arr_2048();

		get_2048_user_input();

		check_2048_validate();

		if (cur_step != puzzle_2048_step) break;

		Sleep(50);
	}


	return 0;
}

