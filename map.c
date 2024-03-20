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
    return MOVED_OKAY;
}

int is_wall(int y, int x) {
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
            // check if it is a new line character
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


            if (currentChar != ' ') {// ignore the char if it's a space
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
            }
        }



//        char currentChar = getc(pFile);
//        if (currentChar != NULL){
//            if (currentChar =='\n'){
//                *map_width = width;
//                width = 0;
//                height++;
//                continue;
//            }
//            if (currentChar == EOF){
//                *map_height = ++height;
//                return map;
//            }
//            width++;
//            *(map+map_size) = currentChar;
//            char* tempMap = (char*) realloc(map,++map_size*sizeof(char));
//            if (tempMap != NULL){
//                map = tempMap;
//                tempMap = NULL;
//                free(tempMap);
//            }else{
//                return NULL;
//            }
//        }


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
