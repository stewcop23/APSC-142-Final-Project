// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win() {

 //loop through all dots, if there are any remaining the game is not over,
 // if all dots are eaten then the loop will fully complete, and YOU_WIN will be returned
    for(int i = 0; i<width*height;i++){
        if(dot_map[i]==DOT)
            return KEEP_GOING;
    }

    return YOU_WIN;
}

int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    return KEEP_GOING;
}
int get1DCoord (int x, int y, int mapWidth){
    return (y*mapWidth)+x;
}





