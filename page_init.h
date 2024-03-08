#pragma once
#include "menu_module.h"
#define INIT_PAGE_TITLE "DAOU MINI GAME"

extern char* init_menus[3];

void init_page_menu_select(int cur_menu_selected);
void initialize_init_page_map();

menu* page_init_menu;
