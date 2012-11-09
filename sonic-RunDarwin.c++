// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app &> RunDarwin.out

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
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
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
        Grid g(8, 8);
        g.place(FOOD  , EAST, 0, 0);
        g.place(HOPPER, NORTH, 3, 3);
        g.place(HOPPER, EAST, 3, 4);
        g.place(HOPPER, SOUTH, 4, 4);
        g.place(HOPPER, WEST, 4, 3);
        g.place(FOOD  , NORTH, 7, 7);

        g.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Grid g(7, 9);
        srand(0);
        g.place(TRAP,   SOUTH, 0, 0);
        g.place(HOPPER, EAST, 3, 2);
        g.place(ROVER,  NORTH, 5, 4);
        g.place(TRAP,   WEST, 6, 8);

        g.simulate(5, 1);
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
        cout << "*** Darwin 72x72 without Best ***" << endl;
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
        Grid g(72, 72);
        srand(0);

        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(FOOD, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(HOPPER, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(ROVER, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(TRAP, rand()%4, pos/72, pos%72);
        }

        g.simulate(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
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
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */

        Grid g(72, 72);
        srand(0);

        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(FOOD, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(HOPPER, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(ROVER, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(TRAP, rand()%4, pos/72, pos%72);
        }
        for(int i=0;i<10;i++) {
            int pos = rand() % 5184;
            g.place(BEST, rand()%4, pos/72, pos%72);
        }

        g.simulate(1000, 100);
        g.print_count();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        /*
        10x10 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Rover,  facing south, at (1,1)
        Simulate 10 moves.
        Print every other grid.
        */
        Grid g(8, 8);
        g.place(FOOD  , EAST, 0, 0);
        g.place(HOPPER, NORTH, 3, 3);
        g.place(HOPPER, EAST, 3, 4);
        g.place(HOPPER, SOUTH, 4, 4);
        g.place(HOPPER, WEST, 4, 3);
        g.place(FOOD  , NORTH, 7, 7);
        g.place(ROVER , SOUTH, 1, 1);

        g.simulate(10, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        /*
        1x1 Darwin
        Food,   facing east,  at (0, 0)
        Simulate 3 moves.
        Print every grid.
        */
        Grid g(1, 1);
        g.place(FOOD  , EAST, 0, 0);

        g.simulate(3, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 1x1
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        /*
        1x1 Darwin
        rover,   facing east,  at (0, 0)
        Simulate 3 moves.
        Print every grid.
        */
        Grid g(1, 1);
        g.place(ROVER  , EAST, 0, 0);

        g.simulate(3, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 2x2
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        /*
        2x2 Darwin
        Rover,   facing east,  at (0, 0)
        Food,   facing east,  at (1, 0)
        Food,   facing east,  at (1, 1)
        Food,   facing east,  at (0, 1)
        Simulate 10 moves.
        Print every other grid.
        */
        Grid g(2, 2);
        g.place(ROVER  , EAST, 0, 0);
        g.place(FOOD  , EAST, 1, 0);
        g.place(FOOD  , EAST, 1, 1);
        g.place(FOOD  , EAST, 0, 1);


        g.simulate(10, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 100x100
    // ----------

    try {
        cout << "*** Darwin 100x100 ***" << endl;
        srand(0);
        /*
        100x100 Darwin
        rover,   facing east,  at (0, 0)
        Food ,   facing north, at (50, 50)
        Simulate 200 moves.
        Print every 100th grid.
        */
        Grid g(100, 100);
        g.place(ROVER  , EAST, 0, 0);
        g.place(FOOD  , NORTH, 50, 50);

        g.simulate(200, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 100x100
    // ----------

    try {
        cout << "*** Darwin 100x100 ***" << endl;
        srand(0);
        /*
        100x100 Darwin
        rover,   facing east,  at evens
        Food ,   facing north, at odds
        Simulate 200 moves.
        Print every 100th grid.
        */
        Grid g(100, 100);
        for(int i = 0; i < 10000; i++) {
            if(i%2) {
                g.place(FOOD  , NORTH, i/100, i%100);
            } else {
                g.place(ROVER  , EAST, i/100, i%100);
            }
        }
        
        g.simulate(200, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
