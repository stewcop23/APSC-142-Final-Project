// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {

    //loop through all dots, if there are any remaining the game is not over,
    // if all dots are eaten then the loop will fully complete, and YOU_WIN will be returned
    for(int i = 0; i<width*height;i++){
        if(dot_map[i]==DOT)
            return KEEP_GOING;
    }

    return YOU_WIN;
}

int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i<NUM_GHOSTS;i++){
        if (ghosts_y[i]==pacman_y && ghosts_x[i]==pacman_x){
            return YOU_LOSE;
        }
    }
    return KEEP_GOING;
}

