# APSC 142 Final Project

## Project Requirements
* read the map file into dynamic memory with malloc
* map must contain one pacman and 2 ghosts
    * if non readable, have propper error codes
* get user input with `getchar` (wasd). if the

## Required Functions
```C
int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]);
int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]);
char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x);
char * load_map(char * filename, int * map_height, int * map_width);
int is_wall(int y, int x);
int move_actor(int * y, int * x, char direction, int eat_dots);
```
## General game loop
* check if ghosts see pacman
    * if yes, move towards pacman
    * if no, random walk
* get user input
    * see if input colides with wall
    * if yes, do not move pacman
    * if no, move pacman and ghosts
* if pacman lands on dot, remove the dot (from main map and dot map)
* if ghost is on top of pacman, game over
