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

}

void teardown(void) {

}

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    setup();
    map = load_map("map.txt", &width, &height);
    for (int i = 0; i < width * height; i++) {
        printf("%c", map[i]);
    }
    CHECK(width == 9);
    CHECK(height == 9);
    teardown();
}

TEST_CASE("testing print_map") {

    char *map = (char *) malloc(3 * 4 * sizeof(char));
    char tempMap[12] = {'.', 'P', '.', '.', 'W', ' ', 'W', 'W', 'G', '.', '.', 'G'};
    for (int i = 0; i < 12; i++) {
        map[i] = tempMap[i];
    }
    width = 4;
    height = 3;

    print_map(map, &height, &width);
}
// tests for is_wall

// tests for move_actor

TEST_SUITE_END();

/* tests for ghost.c */
TEST_SUITE_BEGIN("Ghost tests");

// tests for sees_pacman

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win

// test for check_loss

TEST_SUITE_END();