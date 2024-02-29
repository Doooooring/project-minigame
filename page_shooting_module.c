#include "main.h"
#include "page_shooting.h"

void initiallize_setting() {
	init_is_exit();
	make_nansu();
	init_speed();
	init_shooting_mem();
	init_shooting_level();
	init_score();
	init_shooting_map();
	init_monster_map();
	init_total_map();
	init_state();
	print_shooting_outline();
	make_total_map();
	print_shooting_game(50);
}

void init_is_exit() {
}
void init_speed() {
	speed = 200;
}
void init_shooting_mem() {

	for (int i = 0; i < SHOOTINGHEIGHT + 1; i++)
		for (int j = 0; j < WIDTH + 1; j++)
			shooting_mem[i][j] = -2;
}
void init_total_map() {
	for (int i = 1; i < SHOOTINGHEIGHT + 1; i++)
		for (int j = 1; j < WIDTH + 1; j++)
			total_map[i][j] = 0;
}
void init_monster_map() {
	for (int i = 1; i < SHOOTINGHEIGHT + 1; i++)
		for (int j = 1; j < WIDTH + 1; j++)
			monster_map[i][j] = 0;
}
void init_shooting_map() {
	for (int i = 1; i < SHOOTINGHEIGHT + 1; i++)
		for (int j = 1; j < WIDTH + 1; j++)
			shooting_map[i][j] = 0;
}
void init_state() {
	state_h = START_H;
	state_w = START_W;
}

void init_shooting_timer() {
	start_shooting = (int)clock();
	end_shooting = (int)clock();
}

void init_control_timer() {
	start_control = (int)clock();
	end_control = (int)clock();
}

void init_shooting_level() {
	shooting_level = 1;
}


void make_nansu() {
	srand(time(NULL));
	nansu = rand() % 2023 + 1;
}


void print_shooting_outline() {
	print_str_row(1, "SHOOTING GAME");
	printf("%s", COLOR_WHITE_DARK_GRAY);
	for (i = 0; i < MAPHEIGHT + 2; i++) {
		print_str(i, 0, white);
		print_str(i, WIDTH + 1, white);
	}
	for (i = 0; i < WIDTH + 2; i++) {
		print_str(0, i, white);
		print_str(MAPHEIGHT + 1, i, white);
		print_str(MAPHEIGHT - SHOOTINGHEIGHT, i, white);
	}
}
void print_shooting_game(int speed) {
	int x, y;
	for (int i = 1; i <= SHOOTINGHEIGHT; i++) {
		for (int j = 1; j <= WIDTH; j++) {
			if (shooting_mem[i][j] == total_map[i][j]) continue;
			switch (total_map[i][j]) {
			case(0):
				printf("%s", COLOR_WHITE_DARK_GRAY);
				print_str(MAPHEIGHT - SHOOTINGHEIGHT + i, j, blank);
				break;
			case(1):
				printf("%s", COLOR_WHITE_DARK_GRAY);
				//printf("%s",);
				print_str(MAPHEIGHT - SHOOTINGHEIGHT + i, j, monster);
				break;
			case(-1):
				printf("%s", COLOR_YELLOW);
				print_str(MAPHEIGHT - SHOOTINGHEIGHT + i, j, attack);
				break;
			}
			shooting_mem[i][j] = total_map[i][j];
		}
	}
	printf("%s", COLOR_PURPLE);
	print_str(MAPHEIGHT - SHOOTINGHEIGHT + state_h, state_w, "бу");
	print_str(MAPHEIGHT - SHOOTINGHEIGHT + state_h, state_w - 1, "=");
	print_str(MAPHEIGHT - SHOOTINGHEIGHT + state_h, state_w + 1, "=");
	printf("%s", COLOR_RESET);
	switch (score % 2) {
	case(0):
		printf("%s", COLOR_RED);
		break;
	case(1):
		printf("%s", COLOR_BLUE);
		break;
	}
	print_str_int_format(MAPHEIGHT - SHOOTINGHEIGHT - 1, 1, "SCORE: %d", score);
	print_str_int_format(MAPHEIGHT - SHOOTINGHEIGHT - 3, 1, "LV%2d", shooting_level);
}

void make_total_map() {
	for (int i = 1; i <= SHOOTINGHEIGHT; i++)
		for (int j = 1; j <= WIDTH; j++) {
			total_map[i][j] = monster_map[i][j] + shooting_map[i][j];
			if (monster_map[i][j] > 0 && shooting_map[i][j] < 0) {
				score += (24 + shooting_level * 5);
				monster_map[i][j] = 0;
				shooting_map[i][j] = 0;
			}
		}
	if (total_map[state_h][state_w] == 1 || total_map[state_h][state_w - 1] == 1 || total_map[state_h][state_w + 1] == 1) {
		set_cur_step(ranking_step);
	}
	total_map[state_h][state_w] = 2;
	total_map[state_h][state_w - 1] = 2;
	total_map[state_h][state_w + 1] = 2;
	return;
}

void check_score() {
	if (score >= (shooting_level * goal)) {
		shooting_level += 1;
		speed -= 10;
	}
}


int timer(int s_t, int e_t, int limit_time) {
	if (e_t - s_t <= limit_time)
		return true;
	else
		return false;
}


void move_monster() {
	for (int i = SHOOTINGHEIGHT - 1; i >= 1; i--)
		for (int j = 1; j <= WIDTH; j++)
			monster_map[i + 1][j] = monster_map[i][j];
	for (j = 1; j <= WIDTH; j++)
		monster_map[1][j] = 0;
}
void move_shooting() {
	for (int i = 2; i <= SHOOTINGHEIGHT - 1; i++)
		for (int j = 1; j <= WIDTH; j++)
			shooting_map[i - 1][j] = shooting_map[i][j];
	for (j = 1; j <= WIDTH; j++)
		shooting_map[state_h - 1][j] = 0;
}
void make_shooting() {
	shooting_map[state_h - 1][state_w] = -1;
}

void make_three_shooting() {
	shooting_map[state_h - 1][state_w] = -1;
	shooting_map[state_h - 1][state_w - 1] = -1;
	shooting_map[state_h - 1][state_w + 1] = -1;
}



void make_monster() {
	srand(nansu);
	monster_w = rand() % (WIDTH)+1;
	monster_h = rand() % (SHOOTINGHEIGHT / 2) + 1;
	monster_map[monster_h][monster_w] = 1;
	nansu += (rand() % 7 + 1);
}

void control(int button) {
	switch (button) {
	case(left):
		if (state_w == 2)
			break;
		total_map[state_h][state_w + 1] = 0;
		state_w -= 1;
		break;
	case(right):
		if (state_w == WIDTH - 2)
			break;
		total_map[state_h][state_w - 1] = 0;
		state_w += 1;
		break;
	case(spacebar):
		make_shooting();
		break;
	default:
		break;
	}
}