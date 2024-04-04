// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width, height;

//error?
int pacmanX,pacmanY;
int ghostX[NUM_GHOSTS], ghostY[NUM_GHOSTS];

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    setbuf(stdout, NULL);
//Load the map
    map = load_map(MAP_NAME,&width,&height);
    if (map == NULL){
        return ERR_NO_MAP;
    }
    // process the map to create the dot map
    dot_map = load_dots(map,&height,&width);

    //process the map to get the pacman (and process any errors)
    int pacError = get_pacman(map,width,height,&pacmanX,&pacmanY);
    if(pacError==ERR_NO_PACMAN){
        return ERR_NO_PACMAN;
    }

    //process the map to get all ghosts (and output any errors)
    int ghostError = get_ghosts(map,width,height,ghostX,ghostY);
    if (ghostError==ERR_NO_GHOSTS){
        return ERR_NO_GHOSTS;
    }

    //print the starting map
    print_map(map,&width,&height);
    while(1){
        char input = getch();
        // move the pacman in the direction pressed
        move_actor(&pacmanY,&pacmanX,input,EAT_DOTS);


        for (int i =0;i<NUM_GHOSTS;i++){//for each ghosts
            char seenDirection = sees_pacman(pacmanY, pacmanX, ghostY[i], ghostX[i]);//store the direction the ghost sees pacman...
            if(seenDirection == SEES_NOTHING) {// if it doesn't, pick a random direction...
                int ghostDirection = rand() % 4;

                if (ghostDirection==0){
                    move_actor(&ghostY[i], &ghostX[i], UP, REPLACE_DOTS);
                }
                else if(ghostDirection==1){
                    move_actor(&ghostY[i], &ghostX[i], LEFT, REPLACE_DOTS);
                }
                else if(ghostDirection==2){
                    move_actor(&ghostY[i], &ghostX[i], DOWN, REPLACE_DOTS);
                }else{
                    move_actor(&ghostY[i], &ghostX[i], RIGHT, REPLACE_DOTS);
                }

            }else{//if the ghost does see pacman, move in that direction
                move_actor(&ghostY[i], &ghostX[i], seenDirection, REPLACE_DOTS);
            }

        }

        if(check_loss(pacmanY,pacmanX,ghostY,ghostX)==YOU_LOSE){
            printf("Sorry, you lose.\n");
            return 0;
        }


        print_map(map,&width,&height);
        if(check_win(pacmanY, pacmanX, ghostY, ghostX)==YOU_WIN){
            printf("Congratulations! You win!\n");
            return 0;
        }



//        return 0;
    }
}
