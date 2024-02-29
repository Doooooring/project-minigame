#include "main.h"
#include "page_ranking.h"


int page_ranking()
{

	load_rank();
	load_step4_data();

	while (1) {

		print_title();
		print_ranks();
		print_footer();
		

		if (cur_step != ranking_step) break;
		
		Sleep(50);
	}
	return 0;
}

