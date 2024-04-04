// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "ghost.h"
#include "map.h" // error?

char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    //check if pacman and ghost are in the same column
    if(pacman_x == ghost_x){
        //check if the ghost is eating pacman
        if (pacman_y == ghost_y){
            return EATING_PACMAN;
        }//check if there is a wall between them
        else if(pacman_y < ghost_y){
            //check each character between them to see if it is a wall
            for(int i = pacman_y; i < ghost_y; i++){
                if(is_wall(i, pacman_x)){
                    //the ghost doesn't see pacman
                    return SEES_NOTHING;
                }
            }

            //ghost should move up
            return UP;
        }
        //ghost has to be above pacman
        //check each character between them to see if it is a wall
        for(int i = ghost_y; i < pacman_y; i++) {
            if (is_wall(i, pacman_x)) {
                //the ghost doesn't see pacman
                return SEES_NOTHING;
            }
        }

        //ghost should move down
        return DOWN;
    }
    else if(pacman_y == ghost_y){ //check if pacman and ghost are in the same row
        //don't need to check if the ghost is eating pacman since that was done earlier
        //check if pacman is to the left of the ghost
        if(pacman_x < ghost_x){
            //check each character between them to see if it is a wall
            for(int i = pacman_x; i < ghost_x; i++){
                if(is_wall(pacman_y, i)){
                    //the ghost doesn't see pacman
                    return SEES_NOTHING;
                }
            }

            //ghost should move left
            return LEFT;
        }
        //pacman has to be to the right of the ghost
        //check each character between them to see if it is a wall
        for(int i = ghost_x; i < pacman_x; i++){
            if(is_wall(pacman_y, i)){
                //the ghost doesn't see pacman
                return SEES_NOTHING;
            }
        }

        //the ghost should move right
        return RIGHT;
    }
    return SEES_NOTHING;
}
