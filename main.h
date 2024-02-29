#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#ifndef __step_define
typedef enum page_step {
	init_step = 0,
	game_select_step,
	difficult_select_step,
	tetris_step,
	puzzle_2048_step,
	shooting_step,
	ranking_step
} page_step;
#define __step_define 1
#endif

#ifndef __difficulty_define
typedef enum DIFFICULTY {
	advanced = 1,
	challenge,
	impossible
} DIFFICULTY;
#define __difficulty_define 1
#endif

#ifndef __game_define
typedef enum GAME_TYPE {
	tetris = 1,
	puzzle_2048,
	shooting
} GAME_TYPE;
#define __game_define 1
#endif

#ifndef __bool_define
typedef enum bool{ false = 0, true } bool;
#define __bool_define 1
#endif

#ifndef __game_define
typedef enum GAME_TYPE {
	tetris = 1,
	puzzle_2048,
	shooting
} GAME_TYPE;
#define __game_define 1
#endif

#ifndef __move_define
typedef enum INPUT {
	down = 1,
	left,
	right,
	up,
	spacebar
} ARROW_TYPE;
#define __move_define 1
#endif

#define WIDTH 22

#define MAPHEIGHT 30
#define TETRISHEIGHT 25

#define TIME 150

#define COLOR_BLACK  "\033[0;31m"
#define COLOR_RED    "\033[0;31m"
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE   "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN   "\033[0;36m" 
#define COLOR_WHITE	 "\033[0;37m"
#define COLOR_RESET  "\033[0m"

#define COLOR_WHITE_BLACK "\033[97;40m"
#define COLOR_WHITE_DARK_GRAY "\033[97;100m"
#define COLOR_WHITE_PASTEL_GREEN "\033[97;48;5;121m"
#define COLOR_WHITE_PASTEL_YELLOW "\033[97;48;5;187m"
#define COLOR_WHITE_PASTEL_BLUE "\033[97;48;5;74m"
#define COLOR_WHITE_PASTEL_MAGENTA "\033[97;48;5;171m"
#define COLOR_WHITE_PASTEL_CYAN "\033[97;48;5;81m"
#define COLOR_WHITE_PASTEL_LIGHT_GREY "\033[97;48;5;145m"
#define COLOR_WHITE_PASTEL_ORANGE "\033[97;48;5;215m"
#define COLOR_WHITE_PASTEL_PURPLE "\033[97;48;5;177m"
#define COLOR_WHITE_PASTEL_PINK "\033[97;48;5;211m"
#define COLOR_WHITE_PASTEL_BROWN "\033[97;48;5;166m"

#define RGB_DARK_GREY  "\033[38;2;51;51;51m"
#define RGB_LIGHT_GREY "\033[38;2;153;153;153m"

#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ARROW_UP 72
#define ARROW_DOWN 80
#define SPACEBAR 32
#define END 27

#define blank " "
#define black "¡à"
#define white "¡á"

page_step cur_step;
int speed;
int cur_game;

//tetris.h -> main.h
int button;
int score;
enum DIFFICULTY difficulty;

int map[MAPHEIGHT + 2][WIDTH + 2];
int mem[TETRISHEIGHT + 2][WIDTH + 2];
int tetris_map[TETRISHEIGHT + 2][WIDTH + 2];

int background[MAPHEIGHT][WIDTH];

// step;
int page_init();
int page_2048();
int page_game_select();
int page_difficulty();
int page_tetris();
int page_shooting();
int page_ranking();

// map.c
void cursor_view();
void init_mem();
void generate_map();
void gotoxy(int x, int y);
void print_char(int x, int y, char c);
void print_str(int x, int y, char* s);
void print_str_int_format(int x, int y, char* s, int d);
void print_str_cen(char(*s)[15], int count);
void print_str_row(int x, char* s);
void print_tetris(int time);
void print_all();
void erase_line(int x);
void erase_all();

//ÀÔ·Â
int get_input(int button);

// source.c
void set_cur_step(int ne_step);
void set_cur_score(int ne_score);
void set_cur_game(GAME_TYPE game);
void init_score();
void set_difficulty(enum DIFFICULTY diff);

void initialize_setting();

// background.c
void update_background();
void print_background();