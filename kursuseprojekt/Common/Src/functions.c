/*
 * functions.c
 *
 *  Created on: 4. dets 2021
 *      Author: Lenovo T440
 */
#include "functions.h"
#include "stm32f429i_discovery_lcd.h"

uint16_t Radius = 10;
uint8_t bool = 0;
uint8_t reload_bool = 0;
uint16_t temp_x = 0;
uint8_t enemy[] = {1,1,1,1,1,1};
uint8_t eloc[6][2] = {{20,50},{60,50},{100,50},{140,50},{180,50},{220,50}};
uint8_t help_scorecount = 0;
uint8_t score[60];
uint8_t action[] = "FIRE!";
uint8_t reload[] = "RELOADING!";
uint8_t new_attack = 0;
uint8_t new_attack2 = 0;
uint8_t youwin[] = "YOU WIN";
uint8_t youlose1[] = "YOU LOSE";
uint8_t youlose2[] = "PRESS YLW BTN";
uint8_t youlose3[] = "TO START";
uint8_t gameover[] = "GAME OVER";
uint8_t livesleft = 3;
uint8_t displaylives[60];
uint8_t set_allowed = 1;

void fire_bullet(){
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillCircle (temp_x, distance, 3);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 5,0,reload,RIGHT_MODE);
}
void display_score_lives(){
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAtLine	(0, score );
	BSP_LCD_DisplayStringAtLine	(1, displaylives );
}
void display_fire(){
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 20,0,action,RIGHT_MODE);
}
void draw_rocket(){
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,Radius);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,8);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,5);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,4);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,3);
	BSP_LCD_DrawCircle(xy_mapped.x, 300,2);
}
void update_enemy_status(){
	if(enemy[0]){
		BSP_LCD_FillCircle (eloc[0][0], eloc[0][1], 10);
		}
	if(enemy[1]){
		BSP_LCD_FillCircle (eloc[1][0], eloc[1][1], 10);
	}
	if(enemy[2]){
		BSP_LCD_FillCircle (eloc[2][0], eloc[2][1], 10);
	}
	if(enemy[3]){
		BSP_LCD_FillCircle (eloc[3][0], eloc[3][1], 10);
	}
	if(enemy[4]){
		BSP_LCD_FillCircle (eloc[4][0], eloc[4][1], 10);
	}
	if(enemy[5]){
		BSP_LCD_FillCircle (eloc[5][0], eloc[5][1], 10);
	}

}
void check_btn_pressed(){
	if (!bool && HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3) == GPIO_PIN_RESET){
			temp_x = xy_mapped.x;
			bool = 1;
	}
}
void check_for_enemy_hit(){
	for(uint8_t i = 0;i<6;i++){
		if (((temp_x > eloc[i][0] - 10)&&(temp_x < eloc[i][0] + 10))&&((distance>50)&&(distance<55))){
			enemy[i] = 0;
		}
	}
}
void update_score_lives(){
	for(uint8_t i = 0; i<6; i++){
		if(enemy[i] == 0){
			help_scorecount++;
		}
	}

	scorecount = help_scorecount;
	sprintf(score,"SCORE: %d", scorecount);
	sprintf(displaylives,"LIVES: %d", livesleft);
	help_scorecount = 0;
}
void check_your_hit(){
	if( ((enemy_temp_x > xy_mapped.x - 5)&&(enemy_temp_x < xy_mapped.x + 5)) && ((enemy_distance > 295)&&(enemy_distance < 305))){
		gamestatus = LOSE;
		if(set_allowed){
			livesleft--;
			set_allowed = 0;
		}
	}

	if( ((enemy_temp_x2 > xy_mapped.x - 5)&&(enemy_temp_x2 < xy_mapped.x + 5)) && ((enemy_distance2 > 295)&&(enemy_distance2 < 305))){
		gamestatus = LOSE;
		if(set_allowed){
			livesleft--;
			set_allowed = 0;
		}
	}
}
void draw_enemy_bullets(){
	if(new_attack){
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		BSP_LCD_FillCircle (enemy_temp_x, enemy_distance, 3);
	}
	if(new_attack2){
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		BSP_LCD_FillCircle (enemy_temp_x2, enemy_distance2, 3);
	}

}
void you_win(){
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(10,150,youwin,CENTER_MODE);
}
void you_lose(){
	set_allowed = 1;
	sprintf(displaylives,"LIVES: %d", livesleft);
	if(livesleft !=0){
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_SetFont(&Font16);
		BSP_LCD_DisplayStringAt(10,120,youlose1,CENTER_MODE);
		BSP_LCD_DisplayStringAt(10,140,displaylives,CENTER_MODE);
		BSP_LCD_DisplayStringAt(10,160,youlose2,CENTER_MODE);
		BSP_LCD_DisplayStringAt(10,180,youlose3,CENTER_MODE);


		if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3) == GPIO_PIN_RESET){
			gamestatus = RUN;

		}
	} else {gamestatus = OVER;}
}
void game_over(){
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_DisplayStringAt(10,140,gameover,CENTER_MODE);
}
void manage_bullet_movement(){
	if (bool){
		distance-=3;
		if(distance <= 11){
			distance = BSP_LCD_GetYSize() - 40;
			bool = 0;
		}
	}
	if (new_attack){
		enemy_distance+=4;
		if(enemy_distance >=320){
			new_attack = 0;
		}
	}
	if (new_attack2){
		enemy_distance2+=6;
		if(enemy_distance2 >=320){
			new_attack2 = 0;
		}
	}
	if (scorecount == 6 ){
		gamestatus = WIN;
	}
}
void manage_enemy_shoot_order(){
	uint8_t rand_num1 = rand() % 6;
	if (new_attack == 0) {
		enemy_distance = eloc[2][1];
		if(enemy[rand_num1] == 1){
			enemy_temp_x = eloc[rand_num1][0];
			new_attack = 1;
		}
	}
	uint8_t rand_num2 = rand() % 6;
	if (new_attack2 == 0) {
		enemy_distance2 = eloc[5][1];
		if(enemy[rand_num2] == 1){
			enemy_temp_x2 = eloc[rand_num2][0];
			new_attack2 = 1;
		}
	}
}
