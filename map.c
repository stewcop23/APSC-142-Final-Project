// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

int move_actor(int * y, int * x, char direction, int eat_dots) {
    int changeInX = 0;
    int changeInY = 0;

    switch (direction){
        case UP:
            //check if there is a wall above it
            if(is_wall(*y - 1, *x)){
                return MOVED_WALL;
            }

            changeInY = -1;
            break;
        case DOWN:
            //check if there is a wall below it
            if(is_wall(*y + 1, *x)){
                return MOVED_WALL;
            }

            changeInY = 1;
            break;
        case LEFT:
            //check if there is a wall to the left of it
            if(is_wall(*y, *x -1)){
                return MOVED_WALL;
            }

            changeInX = -1;
            break;
        case RIGHT:
            //check if there is a wall to the right of it
            if(is_wall(*y, *x + 1)){
                return MOVED_WALL;
            }

            changeInX = 1;
            break;
        default:
            return MOVED_INVALID_DIRECTION;
    }

    /*
     * This is from map.h, and I'm not 100% sure what it means.
     * Specifically, I don't understand: "the global map should be updated
     * at the passed coordinates, but not at the new coordinates"
     *
     * Full section I'm referencing:
     * "The function also takes a parameter to either update the global map
     * with dots from the global dot_map (REPLACE_DOTS) or not (EAT_DOTS),
     * in which case the vacated coordinates should be replaced by EMPTY.
     * In either case, the global map should be updated at the passed
     * coordinates, but not at the new coordinates, if moving was successful."
     *
     * So the order of this area of the function might have to be changed? Not sure
     */

    //replace actor with dot or EMPTY
    if (eat_dots){
        /*
         * replace with EMPTY - dot_map has not been coded
         */
    }
    else{
        /*
         * replace with dot - dot_map has not been coded
         */
    }

    //update actor location
    *y += changeInY;
    *x += changeInX;

    return MOVED_OKAY;
}

int is_wall(int y, int x) {
    if(map[(y*width) +x] == 'W' || y < 0 || x < 0 || y >= width || x >= width){
        return YES_WALL;
    }

    return NOT_WALL;
}

char * load_map(char *filename, int *map_height, int *map_width) {
    FILE *pFile = NULL;
    pFile = fopen(filename,"r");
    int map_size = 0;//stores how many chars are in the map

    char* map = (char*) malloc(1*sizeof(char));

    if(pFile==NULL){
        return NULL;
    }

    width = 0;

    while(1){
        // read next char
        char currentChar = getc(pFile);

        // check that it actually read something
        if (currentChar != NULL){
            width++;
            *(map + map_size) = currentChar;// map should already have 1 empty index, this is where the latest char is placed

            // dynamically reallocate memory.
            char* tempMap = realloc(map,(++map_size+1)*sizeof(char)); //map size needs to be incremented, and the +1 is because we want the new array to be larger than the map size to accommodate the next char.

            if (tempMap != NULL){//if memory is allocated properly...
                //swap the tempMap and Map variables
                map = tempMap;
                //free tempMap to avoid memory leaks
                tempMap = NULL;
                free(tempMap);
            }else{
                return NULL;
            }
            currentChar = getc(pFile);// we're allowed to assume 2 spaces after every character, unless the next character is a new line or the end of the file
            if(currentChar == '\n'){
                *map_width = width; // update the map width storage variable
                width = 0; // reset the map width tracker variable
                continue;
            }
            else if (currentChar == EOF){
                *map_width = width;
                *map_height = map_size / (*map_width);
                return map;
            }
            getc(pFile);//this will always ignore the second space
        }

    }


    return NULL;
}

char * print_map(char* map, int* map_height,int* map_width){

    //print the top line of walls (excluding the last one because of weird spacing things)
    for(int i = 0; i< *map_width+1;i++){
        printf("W ");
    }
    printf("W\n");

    // loop through every row
    for(int row=0; row<*map_height; row++){
        // at the start of every row there is a wall
        printf("W ");
        for(int column=0; column< *map_width;column++){
            printf("%c ",map[row* *map_width+column]);
        }
        //at the end of every row there's a wall and a newline
        printf("W\n");
    }
    //print the bottom line of walls
    for(int i = 0; i< *map_width+1;i++){
        printf("W ");
    }
    printf("W\n");

    return NULL;
}
