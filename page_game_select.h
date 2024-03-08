#pragma once
#include "menu_module.h"
#define GAME_SELECT_PAGE_TITLE "Select Game"

extern char* game_select_menus[];

void game_select_page_menu_select(int cur_menu_selected);
void initialize_game_select_page_map();

menu* page_game_select_menu;