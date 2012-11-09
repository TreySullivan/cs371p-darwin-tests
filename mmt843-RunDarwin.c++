// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ---------
// direction
// ---------
Direction direction(int dir)
{
    if(dir == 0)
        return NORTH;
    if(dir == 1)
        return EAST;
    if(dir == 2)
        return SOUTH;
    else
        return WEST;
}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    try {
        printf("*** Darwin 8x8 ***\n");
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin<8, 8> d;
        d.place(FOOD  , EAST, 0, 0);
        d.place(HOPPER, NORTH, 3, 3);
        d.place(HOPPER, EAST, 3, 4);
        d.place(HOPPER, SOUTH, 4, 4);
        d.place(HOPPER, WEST, 4, 3);
        d.place(FOOD  , NORTH, 7, 7);
        
        d.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------------------------
    // darwin 8x8 (food/traps only)
    // ----------------------------

    try {
        printf("*** Darwin 8x8 ***\n");
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Food, facing north, at (3, 3)
        Food, facing east,  at (3, 4)
        Food, facing south, at (4, 4)
        Trap, facing west,  at (4, 3)
        Trap,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin<8, 8> d;
        d.place(FOOD  , EAST, 0, 0);
        d.place(FOOD, NORTH, 3, 3);
        d.place(FOOD, EAST, 3, 4);
        d.place(FOOD, SOUTH, 4, 4);
        d.place(TRAP, WEST, 4, 3);
        d.place(TRAP  , NORTH, 7, 7);
        
        d.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------------------
    // darwin 8x8 (single rover only)
    // ------------------------------

    try {
        printf("*** Darwin 8x8 ***\n");
        /*
        8x8 Darwin
        Rover,   facing east,  at (0, 0)
        Simulate 50 moves.
        Print every 5 grids.
        */
        Darwin<8, 8> d;
        d.place(ROVER, EAST, 0, 0);
        
        d.simulate(50, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------------------
    // darwin 72x72 (single rover only)
    // ------------------------------

    try {
        printf("*** Darwin 8x8 ***\n");
        /*
        8x8 Darwin
        Rover,   facing east,  at (0, 0)
        Simulate 50 moves.
        Print every 10 grids.
        */
        Darwin<72, 72> d;
        d.place(ROVER, EAST, 0, 0);
        
        d.simulate(50, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ------------------
    // darwin 8x8 (empty)
    // ------------------

    try {
        printf("*** Darwin 8x8 (empty) ***\n");
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin<8, 8> d;
        
        d.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------------
    // darwin 4x4 (fat hopper)
    // -----------------------

    try {
        printf("*** Darwin 8x8 (fat hopper)***\n");
        /*
        4x4 Darwin
        Hopper, facing south, at (0, 0)
        Food,   facing east,  at (0, 1)
        Food,   facing east,  at (1, 0)
        Food,   facing east,  at (1, 1)
        Simulate 20 moves.
        Print every 5 grids.
        */
        Darwin<4, 4> d;
        d.place(HOPPER, SOUTH, 0, 0);
        d.place(FOOD, EAST, 0, 1);


        d.simulate(20, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        printf("*** Darwin 7x9 ***\n");
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Darwin<7, 9> d;
        d.place(TRAP  , SOUTH, 0, 0);
        d.place(HOPPER, EAST, 3, 2);
        d.place(ROVER, NORTH, 5, 4);
        d.place(TRAP, WEST, 6, 8);
        
        d.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        printf("*** Darwin 72x72 without Best ***\n");
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        Darwin<72, 72> d;

        for(unsigned int i = 0; i < 10; i++){
            unsigned int p = rand() % 5184;
            int dirNum = rand() % 4;
            unsigned int x, y, count;
            x = y = count = 0;
            for (int j = 0; j < 72; j++) {
                for (int k = 0; k < 72; k++) {
                    if (count++ == p) {
                        x = j;
                        y = k;
                    }
                }
            }
            Direction dir = direction(dirNum);
            d.place(FOOD, dir, x, y);  
        }
        for(unsigned int i = 0; i < 10; i++){
            unsigned int p = rand() % 5184;
            int dirNum = rand() % 4;
            unsigned int x, y, count;
            x = y = count = 0;
            for (int j = 0; j < 72; j++) {
                for (int k = 0; k < 72; k++) {
                    if (count++ == p) {
                        x = j;
                        y = k;
                    }
                }
            }
            Direction dir = direction(dirNum);
            d.place(HOPPER, dir, x, y);    
        }
        for(unsigned int i = 0; i < 10; i++){
            unsigned int p = rand() % 5184;
            int dirNum = rand() % 4;
            unsigned int x, y, count;
            x = y = count = 0;
            for (int j = 0; j < 72; j++) {
                for (int k = 0; k < 72; k++) {
                    if (count++ == p) {
                        x = j;
                        y = k;
                    }
                }
            }
            Direction dir = direction(dirNum);
            d.place(ROVER, dir, x, y); 
        }
        for(unsigned int i = 0; i < 10; i++){
            unsigned int p = rand() % 5184;
            int dirNum = rand() % 4;
            unsigned int x, y, count;
            x = y = count = 0;
            for (int j = 0; j < 72; j++) {
                for (int k = 0; k < 72; k++) {
                    if (count++ == p) {
                        x = j;
                        y = k;
                    }
                }
            }
            Direction dir = direction(dirNum);
            d.place(TRAP, dir, x, y);  
        }
        d.simulate(1000, 100);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    /*
    1x1 Grid
    Simulate 5 moves.
    Print every grid.
    */
    try {
        printf("*** Darwin 1x1***\n");
        Darwin<1, 1> d;
        srand(0);
        d.place(HOPPER, EAST, 0, 0);
        d.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 50x50
    // without best
    // ------------

    try {
        printf("*** Darwin 72x72 (rovers only) ***\n");
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        50 Rover
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        Darwin<72, 72> d;

        
        for(unsigned int i = 0; i < 50; i++){
            unsigned int p = rand() % 5184;
            int dirNum = rand() % 4;
            unsigned int x, y, count;
            x = y = count = 0;
            for (int j = 0; j < 72; j++) {
                for (int k = 0; k < 72; k++) {
                    if (count++ == p) {
                        x = j;
                        y = k;
                    }
                }
            }
            Direction dir = direction(dirNum);
            d.place(ROVER, dir, x, y); 
        }
        d.simulate(1000, 100);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
