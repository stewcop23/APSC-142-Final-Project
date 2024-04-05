// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "ghost.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

void setup(void) {
    map = load_map(MAP_NAME, &height, &width);
    dot_map = load_dots(map,&height, &width);

}

void teardown(void) {
    map = NULL;
    dot_map=NULL;
    width = 0;
    height=0;
}

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    setup();

    //Confirm all types of values are read correctly
    CHECK(map[0]==GHOST);
    CHECK(map[1]==DOT);
    CHECK(map[4]==WALL);
    CHECK(map[4*width+4]==PACMAN);

    //confirm width and height are set properly
    CHECK(width == 9);

  CHECK(height == 9);

    //include tests to see if pacman loaded into the right spot
    teardown();
}

TEST_CASE("Testing load_dots"){
    setup();
    dot_map = load_dots(map,&height,&width);

    CHECK(dot_map[0]==EMPTY);//confirms that map has loaded correctly and that ghosts are ignored
    CHECK(dot_map[1]==DOT);//confirms that dots are being tracked correctly
    CHECK(dot_map[4]==EMPTY);//confirm that walls are being kept blank
    CHECK(dot_map[40]==EMPTY);//confirms that pacman is read as empty.

    teardown();
}

/*TEST_CASE("testing print_map") {

    char *testMap = (char *) malloc(3 * 4 * sizeof(char));
    char tempMap[12] = {'.', 'P', '.', '.', 'W', ' ', 'W', 'W', 'G', '.', '.', 'G'};
    for (int i = 0; i < 12; i++) {
        testMap[i] = tempMap[i];
    }
    int testWidth = 4;
    int testHeight = 3;

    print_map(testMap, &testHeight, &testWidth);
}*/

TEST_CASE("Testing is_wall"){
    setup();
    //Identify it is a wall
    CHECK(is_wall(0, 4));
    CHECK(is_wall(1, 1));
    CHECK(is_wall(8, 4));

    //Identify it isn't a wall
    CHECK(!is_wall(0, 0));
    CHECK(!is_wall(3, 6));
    teardown();
}

TEST_CASE("Testing move_actor"){
    setup();
    int ghostX;
    int ghostY;

    ghostX = 0;
    ghostY = 1;

    //move up correctly
    move_actor(&ghostY, &ghostX, UP, REPLACE_DOTS);
    CHECK(ghostX == 0);
    CHECK(ghostY == 0);

    ghostX = 0;
    ghostY = 0;

    //move down correctly
    move_actor(&ghostY, &ghostX, DOWN, REPLACE_DOTS);
    CHECK(ghostX == 0);
    CHECK(ghostY == 1);

    ghostX = 3;
    ghostY = 2;

    //move left correctly
    move_actor(&ghostY, &ghostX, LEFT, REPLACE_DOTS);
    CHECK(ghostX == 2);
    CHECK(ghostY == 2);

    ghostX = 2;
    ghostY = 2;

    //move right correctly
    move_actor(&ghostY, &ghostX, RIGHT, REPLACE_DOTS);
    CHECK(ghostX == 3);
    CHECK(ghostY == 2);

    ghostX = 0;
    ghostY = 0;

    //try to move into upper wall
    move_actor(&ghostY, &ghostX, UP, REPLACE_DOTS);
    CHECK(ghostX == 0);
    CHECK(ghostY == 0);

    ghostX = 2;
    ghostY = 6;

    //try to move into lower wall
    move_actor(&ghostY, &ghostX, DOWN, REPLACE_DOTS);
    CHECK(ghostX == 2);
    CHECK(ghostY == 6);

    ghostX = 2;
    ghostY = 6;

    //try to move into left wall
    move_actor(&ghostY, &ghostX, LEFT, REPLACE_DOTS);
    CHECK(ghostX == 2);
    CHECK(ghostY == 6);

    ghostX = 8;
    ghostY = 8;

    //try to move into right wall
    move_actor(&ghostY, &ghostX, RIGHT, REPLACE_DOTS);
    CHECK(ghostX == 8);
    CHECK(ghostY == 8);

    //DOT TESTING STILL NEEDS TO BE WRITTEN
    //dot_map code is not written, so i don't know how it should be tested lol

    //test if actor can remove dots
    int pacmanX=4;
    int pacmanY = 4;
    move_actor(&pacmanY,&pacmanX,RIGHT,EAT_DOTS);
    CHECK(map[4*width+4]==EMPTY);
    CHECK(map[4*width+5]==PACMAN);
    CHECK(dot_map[4*width+5]==EMPTY);

    //test if dot is succesfully removed
    move_actor(&pacmanY,&pacmanX,RIGHT,EAT_DOTS);
    CHECK(map[4*width+5]==EMPTY);
    CHECK(map[4*width+6]==PACMAN);

    //test that non-dot consuming actors leave dots untouched (print_map for debugging: print_map(map,&height,&width);)
    move_actor(&ghostY, &ghostX, UP, REPLACE_DOTS);
    CHECK(map[8*width+8]==EMPTY);
    CHECK(map[7*width+8]==GHOST);

    //test that the dot is successfully replaced
    move_actor(&ghostY, &ghostX, UP, REPLACE_DOTS);
    CHECK(map[7*width+8]==DOT);
    CHECK(map[6*width+8]==GHOST);

    teardown();
}

TEST_CASE("Testing get_ghosts"){
    setup();
    int ghostsx[NUM_GHOSTS];
    int ghostsy[NUM_GHOSTS];

    get_ghosts(map,width,height,ghostsx,ghostsy);

    CHECK(ghostsx[0]==0);
    CHECK(ghostsy[0]==0);

    CHECK(ghostsx[1]==8);
    CHECK(ghostsy[1]==8);

    teardown();
}

TEST_CASE("Testing get_pacman"){
    setup();
    int pacmanx,pacmany;

    get_pacman(map,width,height,&pacmanx,&pacmany);
    CHECK(pacmanx==4);
    CHECK(pacmany==4);



    teardown();
}

TEST_SUITE_END();

/* tests for ghost.c */
TEST_SUITE_BEGIN("Ghost tests");

TEST_CASE("Testing sees_pacman to the right"){
    setup();
    //check that it sees to the right
    CHECK(sees_pacman(2, 6, 2, 2) == RIGHT);

    //check that it notices walls to the right
    CHECK(sees_pacman(2, 6, 2, 0) == SEES_NOTHING);
    teardown();
}

TEST_CASE("Testing sees_pacman to the left"){
    setup();
    //check that it sees to the left
    CHECK(sees_pacman(2, 2, 2, 6) == LEFT);

    //check that it notices walls to the right
    CHECK(sees_pacman(2, 2, 2, 8) == SEES_NOTHING);
    teardown();
}

TEST_CASE("Testing sees_pacman up"){
    setup();
    //check that it sees above it
    CHECK(sees_pacman(2, 2, 4, 2) == UP);

    //check that it notices walls above it
    CHECK(sees_pacman(4, 4, 6, 4) == SEES_NOTHING);
    teardown();
}

TEST_CASE("Testing sees_pacman down"){
    setup();
    //check that it sees below it
    CHECK(sees_pacman(4, 2, 2, 2) == DOWN);

    //check that it notices walls below it
    CHECK(sees_pacman(6, 4, 4, 4) == SEES_NOTHING);
    teardown();
}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
/*TEST_CASE("Testing check_win"){
    setup();
    //check that the game starts unbeaten
    CHECK(check_win()==KEEP_GOING);

    //set all dots to EMPTY to check that the game is win-able
    for(int i = 0; i<width*height;i++){
        dot_map[i]=EMPTY;
    }
    CHECK(check_win()==YOU_WIN);

    teardown();
}*/

// test for check_loss
TEST_CASE("Testing check_loss"){
    setup();

    int pacman_x = 0;
    int pacman_y = 0;

    //ghosts not touching pacman
    int ghost_x[NUM_GHOSTS] = {1,0};
    int ghost_y[NUM_GHOSTS] = {0,1};
    CHECK(check_loss(pacman_y,pacman_x,ghost_y,ghost_x)==KEEP_GOING);

// now the first ghost is on top of pacman
    ghost_x[0] = 0;
    ghost_y[0] = 0;
    CHECK(check_loss(pacman_y,pacman_x,ghost_y,ghost_x)==YOU_LOSE);

    teardown();
}

TEST_SUITE_END();