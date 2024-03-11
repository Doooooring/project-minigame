#include "main.h"

#define SHOOTINGHEIGHT 25
#define START_H SHOOTINGHEIGHT
#define START_W WIDTH/2


#define attack ":"
#define monster "◎"


int button;
int speed;


int goal;
int i, j;
int shooting_level;


int shooting_map[SHOOTINGHEIGHT + 1][WIDTH + 1];
int monster_map[SHOOTINGHEIGHT + 1][WIDTH + 1];
int total_map[SHOOTINGHEIGHT + 1][WIDTH + 1];
int shooting_mem[SHOOTINGHEIGHT + 1][WIDTH + 1];
int state_h, state_w;
int start_shooting, end_shooting;
int start_control, end_control;
int is_exit;
int monster_w, monster_h;
int nansu;
int score;

void init_shooting_mem();
void init_total_map();
void init_is_exit();
void init_speed();
void init_monster_map();
void init_shooting_map();
void init_state();
void init_shooting_level();
void print_shooting_game(int speed);
void print_shooting_outline();
void make_total_map();
void make_nansu();
int timer(int s_t, int e_t, int limit_time);



void move_monster();
void move_shooting();


void control(int button);
void make_shooting();
void make_monster();
void check_score();
void initiallize_setting();