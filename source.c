#include "main.h"

cur_step = init_step;
void set_cur_step(int ne_step) {
	cur_step = ne_step;
}

score = 0;
void set_cur_score(int ne_score) {
	score = ne_score;
}

void init_score() {
	score = 0;
}

difficulty = advanced;
void set_difficulty(enum DIFFICULTY diff) {
	difficulty = diff;
}

void initialize_setting() {
	set_cur_step(0);
	init_score();
	set_difficulty(advanced);
	set_cur_game(tetris);
}

cur_game = tetris;
void set_cur_game(GAME_TYPE game) {
	cur_game = game;
}
