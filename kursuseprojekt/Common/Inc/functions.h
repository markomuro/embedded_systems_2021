/*
 * functions.h
 *
 *  Created on: 4. dets 2021
 *      Author: Lenovo T440
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "stdio.h"
#include "joystick.h"
#include "stdlib.h"

enum {
        RUN,
        WIN,
		LOSE,
        OVER
}gamestatus;

uint16_t Radius;
joy_data xy;
joy_data xy_mapped;
uint32_t distance;
uint32_t enemy_distance;
uint32_t enemy_distance2;
uint16_t enemy_temp_x;
uint16_t enemy_temp_x2;
uint8_t scorecount;
uint16_t Radius;
uint8_t bool;
uint8_t reload_bool;
uint16_t temp_x;
uint8_t enemy[];
uint8_t eloc[6][2];
uint8_t help_scorecount;
uint8_t score[60];
uint8_t action[];
uint8_t reload[];
uint8_t new_attack;
uint8_t new_attack2;
uint8_t youwin[];
uint8_t youlose1[];
uint8_t youlose2[];
uint8_t youlose3[];
uint8_t gameover[];
uint8_t livesleft;
uint8_t displaylives[60];
uint8_t set_allowed;

void fire_bullet();
void display_score_lives();
void display_fire();
void draw_rocket();
void update_enemy_status();
void check_btn_pressed();
void check_for_enemy_hit();
void update_score_lives();
void check_your_hit();
void draw_enemy_bullets();
void you_win();
void you_lose();
void game_over();
void manage_bullet_movement();
void manage_enemy_shoot_order();

#endif /* INC_FUNCTIONS_H_ */
