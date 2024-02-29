#define block_size 3
#define start_h 2
#define start_w (WIDTH%2==0? WIDTH/2 : WIDTH/2+1)
#define goal 10

int i, j, k;
//��� ������ ���� ����
int seed;
int randNum;
//����
int tetris_level, tetris_level_erased, num_erased;
//��� Ÿ��
int blockNum;
//��� ����
int next_block[4][2];
int block[4][2];
clock_t start_time, end_time;

int mem_for_move[4][2];

//Step3
void init_setting(int(*blocks)[4][2]);
void start_new_block(int(*blocks)[4][2]);
void move_block();
void set_for_next_block();

//�ʱ�ȭ
void reset();
void init_tetris_level();
void init_tetris_level_erased();
void init_num_erased();
void init_seed();
void init_score(); //source.c


//���
void print_outline();
void print_tetris(int speed);
void print_difficulty();
void print_next_block(int type);
void coloring_block(int color);

//����
void change_block();
void choose_next_block(int(*blocks)[4][2]);
int control_enabe_time();
void control_tetris_level(int num_erased);
void control_score(int num_erased);
void set_diff();


//��Ʈ���� �˰���
int check(int type);
void move(int type);
void modify(int change);
int erase();
int line_check_for_erase(int h, int w);
void line_drop_for_erase(int line);