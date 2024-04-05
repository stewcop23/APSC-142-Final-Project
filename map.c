// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h> //error?

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

int move_actor(int * y, int * x, char direction, int eat_dots) {
    int changeInX = 0;
    int changeInY = 0;

    // While switch/case statements haven't been taught in this course, we are both taught them in high school and in different languages.
    // Additionally, using a switch statement is far more elegant and efficient than using many if/else statements.
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



    //replace actor with dot or EMPTY
    int startingX = *x;
    int startingY = *y;
    //update actor location
    *y += changeInY;
    *x += changeInX;

    map[*y*width+*x] = map[startingY * width+startingX];//symbol at the new position gets replaced by the symbol at the previous position
    map[startingY * width+startingX] = dot_map[startingY * width+startingX];//replace the starting point with whatever the dot map has there


    if (eat_dots){
        dot_map[*y*width+*x] = EMPTY;//either that index is already empty or it now is
    }



    return MOVED_OKAY;
}

int is_wall(int y, int x) {
    if (map != NULL){
        if(map[(y*width) +x] == WALL || y < 0 || x < 0 || y >= height || x >= width){
            return YES_WALL;
        }
    }

    return NOT_WALL;
}

char * load_map(char * filename, int *map_height, int *map_width) {
    FILE *pFile = NULL;
    pFile = fopen(filename,"r");
    int map_size = 0;//stores how many chars are in the map

    map = (char*) malloc(1 * sizeof(char));

    //check if file pointer and map are initialised properly
    if(pFile == NULL || map == NULL){
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
            char* tempMap = realloc(map, (++map_size + 1) * sizeof(char)); //map size needs to be incremented, and the +1 is because we want the new array to be larger than the map size to accommodate the next char.

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
                fclose(pFile);
                pFile = NULL;
                free(tempMap);
                return map;
            }

            getc(pFile);//this will always ignore the second space (if the previous character wasn't a newline or EOF, this will always be a space)
        }
    }
}


char * print_map(char* mainMap, int* map_height,int* map_width){
    //print the top line of walls (excluding the last one because of weird spacing things)
    change_text_colour(BLUE);
    for(int i = 0; i< *map_width+1;i++){
        printf("W ");
    }

    printf("W\n"); //end the first row of walls

    // loop through every row
    for(int row=0; row<*map_height; row++){
        //at the start of every row there is a wall (color will already be blue)
        printf("W ");
        for(int column=0; column< *map_width;column++){
            char currentTile = mainMap[row * *map_width + column];

            // While switch/case statements haven't been taught in this course, we are both taught them in high school and in different languages.
            // Additionally, using a switch statement is far more elegant and efficient than using many if/else statements.
            switch (currentTile) {
                case PACMAN:
                    change_text_colour(YELLOW);
                    break;
                case DOT:
                    change_text_colour(WHITE);
                    break;
                case GHOST:
                    change_text_colour(PINK);
                    break;
                default://should just be walls and spaces
                    change_text_colour(BLUE);
                    break;
            }

            printf("%c ",currentTile);
        }

        //at the end of every row there's a wall and a newline
        change_text_colour(BLUE);
        printf("W\n");
    }

    //print the bottom line of walls
    for(int i = 0; i< *map_width+1;i++){
        printf("W ");
    }
    printf("W\n");

    return NULL;
}

char* load_dots(char* mainMap,int* map_height,int* map_width){
    // Good memory practices
    if (mainMap==NULL){
        return NULL;
    }

    int mapSize = *map_width * *map_height;
    char* dotMap = (char*) malloc(mapSize*sizeof(char));

    //go through the main map and copy only dots over to the dot map
    for(int i = 0; i< mapSize; i++){
        dotMap[i] = ((mainMap[i]==DOT))?DOT:EMPTY;
    }

    return dotMap;
}

int get_ghosts(char* mainMap, int width, int height, int ghosts_x[NUM_GHOSTS], int ghosts_y[NUM_GHOSTS]){
    // ensure map is loaded correctly
    if (mainMap==NULL){
        return ERR_NO_MAP;
    }

    int ghostsFound = 0;// to track how many ghosts have been found (should be NUM_GHOSTS many)

    for(int i = 0; i< width*height;i++){//loop through every tile
        if(mainMap[i] == GHOST){// if the tile is a ghost...
            int x = i%width;//calculate the x coordinate of the ghost
            int y = (i-x)/width;//calculate the y coordinate of the ghost

            //update the ghost coordinate arrays
            ghosts_x[ghostsFound] = x;
            ghosts_y[ghostsFound] = y;

            //increment the number of ghosts that have been found.
            ghostsFound++;
        }
    }

    // check to see if ghosts have been loaded correctly
    if (ghostsFound==0){
        return ERR_NO_GHOSTS;
    }

    return NO_ERROR;
}

int get_pacman(char* map,int width, int height,int* pacman_x, int*pacman_y){
    for(int i =0; i<width*height;i++){
        if(map[i]==PACMAN){
            int x = i%width; // Get x coordinate
            int y = (i-x)/width; // Get y coordinate

            // Update Pacman coordinates
            *pacman_x = x;
            *pacman_y = y;
            return NO_ERROR;
        }
    }
    return ERR_NO_PACMAN;
}
