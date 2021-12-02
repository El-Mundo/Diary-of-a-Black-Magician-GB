#include <stdio.h>
#include <gb/gb.h>
#include "gbt_player.h"
#include "main.h"
#include "sprites.h"
#include "background.h"
#include "sky_bkg.h"
#include "rand.h"

extern const unsigned char * constgb_music_Data[];

UINT8 enemy[5][6] = {{0,0,0,0,0,0},
                     {0,0,0,0,0,0},
                     {0,0,0,0,0,0},
                     {0,0,0,0,0,0},
                     {0,0,0,0,0,0}};//Type, X, Y, State, HP, Frame*/
UINT8 effect[3] = {0,0,0};
UINT8 enemy_width,enemy_height;
UINT8 i,n;
    UINT8 player_frame = 0;
    UINT8 player_x = 20;
    UINT8 player_y = 60;
    UINT8 player_hp = 3;
    UINT8 player_freeze = 0;
    UINT8 player_infinite = 0;
    UINT8 player_bullet[9] = {0,0,0,0,0,0,0,0,0};
    UINT8 time_span = 0;
    UINT8 total_time = 0;
    UINT8 game_pause = 0;

int main(void)
{   
    enemy[0][0] = 0;
    enemy[1][0] = 0;
    enemy[2][0] = 0;
    enemy[3][0] = 0;
    enemy[4][0] = 0;
    effect[0] = 0;
    effect[1] = 0;
    effect[2] = 0;

    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
    OBP1_REG = 0xD2;

    disable_interrupts();
    gbt_play(constgb_music_Data, 2, 4);
    gbt_loop(1);
    set_interrupts(VBL_IFLAG);
    enable_interrupts();

    set_bkg_data(0,8,Background_Tileset);
    set_bkg_tiles(0,0,40,18,sky_bkg);
    SHOW_BKG;

    SPRITES_8x16;
    /*Sprite 0~4 Player*/
    set_sprite_data(0,48,Tileset);
    set_sprite_tile(0,0);
    move_sprite(0,player_x,player_y+8);
    set_sprite_tile(1,2);
    move_sprite(1,player_x+8,player_y);
    set_sprite_tile(2,4);
    move_sprite(2,player_x+8,player_y+16);
    set_sprite_tile(3,6);
    set_sprite_prop(3,S_PALETTE);
    move_sprite(3,player_x+16,player_y);
    set_sprite_tile(4,8);
    set_sprite_prop(4,S_PALETTE);
    move_sprite(4,player_x+16,player_y+16);
    /*Sprite 5~7 Bullets*/
    set_sprite_tile(5,18);
    set_sprite_prop(5,S_PALETTE);
    move_sprite(5,0,0);
    set_sprite_tile(6,18);
    set_sprite_prop(6,S_PALETTE);
    move_sprite(6,0,0);
    set_sprite_tile(7,18);
    set_sprite_prop(7,S_PALETTE);
    move_sprite(7,0,0);
    /*Sprite 8~17 Enemies*/

    /*Sprite 18~20 Effects*/
    set_sprite_tile(18,38);
    set_sprite_tile(19,38);
    set_sprite_tile(20,38);
    set_sprite_prop(18,S_PALETTE);
    set_sprite_prop(19,S_PALETTE);
    set_sprite_prop(20,S_PALETTE);
    move_sprite(18,0,0);
    move_sprite(19,0,0);
    move_sprite(20,0,0);
    SHOW_SPRITES;

    while(1){
    if(game_pause==0){
        perform_delay(2);
        /*Controlling*/
        if(joypad() & J_UP){
            player_y -= 2;
        }else if (joypad() & J_DOWN){
            player_y += 2;
        }
        if(joypad() & J_RIGHT){
            player_x += 2;
        }else if (joypad() & J_LEFT){
            player_x -= 2;
        }
        if(player_freeze<=6){
            if(joypad() & J_A){         
                if(player_bullet[0]==0){
                    player_bullet[0] = player_x+16;
                    player_bullet[1] = player_y+8;
                    move_sprite(5,player_bullet[0],player_bullet[1]);
                    player_freeze = 12;
                        NR10_REG = 0x96;
                        NR11_REG = 0x81;
                        NR12_REG = 0x82;
                        NR13_REG = 0xC1;
                        NR14_REG = 0xFE;
                }else if (player_bullet[2]==0){
                    player_bullet[2] = player_x+16;
                    player_bullet[3] = player_y+8;
                    move_sprite(5,player_bullet[2],player_bullet[3]);
                    player_freeze = 12;
                        NR10_REG = 0x96;
                        NR11_REG = 0x81;
                        NR12_REG = 0x82;
                        NR13_REG = 0xC1;
                        NR14_REG = 0xFE;
                }else if (player_bullet[4]==0){
                    player_bullet[4] = player_x+16;
                    player_bullet[5] = player_y+8;
                    move_sprite(5,player_bullet[4],player_bullet[5]);
                    player_freeze = 12;
                        NR10_REG = 0x96;
                        NR11_REG = 0x81;
                        NR12_REG = 0x82;
                        NR13_REG = 0xC1;
                        NR14_REG = 0xFE;
                }
                
            }
        }
        /*Collision*/
        if(player_x<8){player_x=8;
        }else if(player_x>144){player_x=144;}
        if(player_y<16){player_y=16;
        }else if(player_y>136){player_y=136;}
        move_sprite(0,player_x,player_y+8);
        move_sprite(1,player_x+8,player_y);
        move_sprite(3,player_x+16,player_y);
        move_sprite(2,player_x+8,player_y+16);
        move_sprite(4,player_x+16,player_y+16);

        /*Bullet Update*/
        if(player_freeze>0){player_freeze--;}
        if(player_freeze==11){set_sprite_tile(3,22);
        }else if(player_freeze==1){set_sprite_tile(3,6);}
        if(player_bullet[0]>=168){
            player_bullet[0] = 0;
        }else if(player_bullet[0]>0){player_bullet[0] += 8;
        player_bullet[6]++;
        if(player_bullet[6]==2){set_sprite_tile(5,20);}else if(player_bullet[6]==4){set_sprite_tile(5,18);player_bullet[6]=0;}
        move_sprite(5,player_bullet[0],player_bullet[1]);}
        if(player_bullet[2]>=168){
            player_bullet[2] = 0;
        }else if(player_bullet[2]>0){player_bullet[2] += 8;
        player_bullet[7]++;
        if(player_bullet[7]==2){set_sprite_tile(5,20);}else if(player_bullet[7]==4){set_sprite_tile(5,18);player_bullet[7]=0;}
        move_sprite(6,player_bullet[2],player_bullet[3]);}
        if(player_bullet[4]>=168){
            player_bullet[4] = 0;
        }else if(player_bullet[4]>0){player_bullet[4] += 8;
        player_bullet[8]++;
        if(player_bullet[8]==2){set_sprite_tile(5,20);}else if(player_bullet[8]==4){set_sprite_tile(5,18);player_bullet[8]=0;}
        move_sprite(7,player_bullet[4],player_bullet[5]);}

        /*Update Enemy*/
        for(i=0;i<5;i++){
            if(enemy[i][0]>0){
                enemy_width = 0;
                enemy_height = 0;
                switch(enemy[i][0]){
                case 1:
                    enemy[i][5]++;
                    enemy[i][1]-=2;
                    enemy_width = 16;
                    enemy_height = 16;
                    if(enemy[i][5]==6){set_sprite_tile(i*2+8,30);set_sprite_tile(i*2+9,32);}
                    else if(enemy[i][5]>12){set_sprite_tile(i*2+8,34);set_sprite_tile(i*2+9,36);enemy[i][5]-=2;}
                    else if(enemy[i][5]==12){set_sprite_tile(i*2+8,26);set_sprite_tile(i*2+9,28);enemy[i][5]=0;}
                    move_sprite(i*2+8,enemy[i][1],enemy[i][2]);
                    move_sprite(i*2+9,enemy[i][1]+8,enemy[i][2]);
                    enemy[i][0]=2;
                    if(enemy[i][1]>160||enemy[i][4]<=0){erase_enemy(i);}
                    break;
                case 2:
                    enemy[i][5]++;
                    enemy[i][1]-=3;
                    enemy_width = 16;
                    enemy_height = 16;
                    if(enemy[i][5]==6){set_sprite_tile(i*2+8,30);set_sprite_tile(i*2+9,32);}
                    else if(enemy[i][5]>12){set_sprite_tile(i*2+8,34);set_sprite_tile(i*2+9,36);enemy[i][5]-=2;}
                    else if(enemy[i][5]==12){set_sprite_tile(i*2+8,26);set_sprite_tile(i*2+9,28);enemy[i][5]=0;}
                    move_sprite(i*2+8,enemy[i][1],enemy[i][2]);
                    move_sprite(i*2+9,enemy[i][1]+8,enemy[i][2]);
                    enemy[i][0]=2;
                    if(enemy[i][1]>160||enemy[i][4]<=0){erase_enemy(i);}
                    break;
                }

                for(n=0;n<3;n++){
                    if(player_bullet[2*n]>0){
                        if (collision(player_bullet[2*n],player_bullet[2*n+1],8,8,enemy[i][1],enemy[i][2],enemy_width,enemy_height)==1) {
                            enemy[i][5] = 15;
                            enemy[i][4]--;
                            if(enemy[i][4]<=0){
                                NR41_REG = 0x00;
                                NR42_REG = 0xE1;
                                NR43_REG = 0x42;
                                NR44_REG = 0xFF;
                                if(effect[0]==0){effect[0]=5;move_sprite(18,enemy[i][1],enemy[i][2]);}
                                else if(effect[1]==0){effect[1]=5;move_sprite(19,enemy[i][1],enemy[i][2]);}
                                else if(effect[2]==0){effect[2]=5;move_sprite(20,enemy[i][1],enemy[i][2]);}
                            }
                            player_bullet[2*n] = 0;
                            move_sprite(5+n,player_bullet[2*n],player_bullet[2*n+1]);
                        }
                    }
                }
                if(player_infinite==0){
                    if (collision(player_x+8,player_y,14,20,enemy[i][1],enemy[i][2],enemy_width,enemy_height)==1) {
                        set_sprite_tile(3,24);
                        player_infinite = 90;
                        player_freeze = 90;
                        player_hp-- ;
                        NR10_REG = 0xBC;
                        NR11_REG = 0x40;
                        NR12_REG = 0xF4;
                        NR13_REG = 0xCF;
                        NR14_REG = 0xFC; }
                }
            }
        }

        /*Spawn Enemy*/
        time_span++;
        if(time_span==127){total_time++;time_span=0;}
        if(total_time==127){total_time=0;}
        if(time_span==20){
            spawn_enemy(0,1,160,rand()%50);
            spawn_enemy(1,1,160,rand()%50+70);
        }else if(time_span==80){
            spawn_enemy(2,1,160,rand()%128);
        }else if(time_span==120){
            spawn_enemy(3,1,160,100);
            spawn_enemy(4,1,160,30);
        }

        /*Update Frame*/
        if(player_infinite>0){
            player_infinite--;
            if(player_infinite<=10){
                set_sprite_tile(0,0);
                set_sprite_tile(1,2);
                set_sprite_tile(2,4);
                set_sprite_tile(3,6);
                set_sprite_tile(4,8);
            }else if(player_infinite%10==6){
                set_sprite_tile(0,126);
                set_sprite_tile(1,126);
                set_sprite_tile(2,126);
                set_sprite_tile(3,126);
                set_sprite_tile(4,126);
            }else if(player_infinite%10==1){
                set_sprite_tile(0,0);
                set_sprite_tile(1,2);
                set_sprite_tile(2,4);
                set_sprite_tile(3,24);
                set_sprite_tile(4,8);
            }
        }else{
            player_frame = update_frame(player_frame);
        }
                scroll_bkg(1,0);
                update_effect();
                gbt_update();
    }
        if(joypad() & J_START){
            if(game_pause==0){game_pause = 1;}else{game_pause = 0;}
            waitpadup();
        }
        //delay(30);
    }
    return 0;
}

UINT8 collision(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return 1;
	} else {	
    	return 0;
	}
}
UINT8 spawn_enemy(UINT8 num, UINT8 type, UINT8 x, UINT8 y)
{
    enemy[num][0] = type;
    enemy[num][1] = x;
    enemy[num][2] = y;
    enemy[num][5] = 0;
    if(type==1){
        set_sprite_tile(num*2+8,26);
        set_sprite_tile(num*2+9,28);
        move_sprite(num*2+8,x,y);
        move_sprite(num*2+9,x+8,y);
        enemy[num][3] = 0;
        enemy[num][4] = 3;
    }else{
        enemy[num][3] = 0;
        enemy[num][4] = 0;
    }
    return enemy[num][0];
}
UINT8 update_frame(UINT8 player_frame){
    player_frame++;
    if(player_frame==3||player_frame==10){
        set_sprite_tile(1,10);
        set_sprite_tile(0,14);
    }else if (player_frame==6)
    {
        set_sprite_tile(1,12);
        set_sprite_tile(0,16);
    }else if (player_frame==12)
    {
        set_sprite_tile(1,2);
        set_sprite_tile(0,0);
        player_frame = 0;
    }
    return player_frame;
}
UINT8 erase_enemy(UINT8 num){
    enemy[num][0] = 0;
    set_sprite_tile(num*2+8,126);
    set_sprite_tile(num*2+9,126);
    return 0;
}
UINT8 update_effect() {
    for(i=0;i<3;i++){
        if(effect[i]>0){
            effect[i]--;
            set_sprite_tile(i+18,38+effect[i]);
            scroll_sprite(i+18,-1,0);
            if(effect[i]==0){move_sprite(i+18,0,0);set_sprite_tile(i+18,38);}
        }
    }
    return 0;
}
void perform_delay(UINT8 time)
{
    for(i=0;i<time;i++){
        wait_vbl_done();
    }
}