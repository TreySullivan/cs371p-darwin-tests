// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
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
// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----
     Species food ('f');
     food.add(LEFT);
     food.add(GO, 0);

    // ------
    // hopper
    // ------
     Species hopper ('h');
     hopper.add(HOP);
     hopper.add(GO, 0);

    // -----
    // rover
    // -----
     Species rover ('r');
     rover.add(IF_ENEMY, 9);
     rover.add(IF_EMPTY, 7);
     rover.add(IF_RANDOM, 5);
     rover.add(LEFT);
     rover.add(GO, 0);
     rover.add(RIGHT);
     rover.add(GO, 0);
     rover.add(HOP);
     rover.add(GO, 0);
     rover.add(INFECT);
     rover.add(GO, 0);

    // ----
    // trap
    // ----
     Species trap ('t');
     trap.add(IF_ENEMY, 3);
     trap.add(LEFT);
     trap.add(GO, 0);
     trap.add(INFECT);
     trap.add(GO, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
        World w (8, 8);
        w.addCreature(0, 0, EAST, &food);
        w.addCreature(3, 3, NORTH, &hopper);
        w.addCreature(3, 4, EAST, &hopper);
        w.addCreature(4, 4, SOUTH, &hopper);
        w.addCreature(4, 3, WEST, &hopper);
        w.addCreature(7, 7, NORTH, &food);

        w.simulate(5, 1);
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
        World w (7, 9);
        w.addCreature(0, 0, SOUTH, &trap);
        w.addCreature(3, 2, EAST, &hopper);
        w.addCreature(5, 4, NORTH, &rover);
        w.addCreature(6, 8, WEST, &trap);

        w.simulate(5, 1);
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
        World w (72, 72);
        for (int i=0; i<10; ++i) {
            int pos = rand() % 5184;
            Direction dir = Direction(rand() % 4);
            int r = pos / 72;
            int c = pos % 72;
            w.addCreature(r, c, dir, &food);
        }
        for (int i=0; i<10; ++i) {
            int pos = rand() % 5184;
            Direction dir = Direction(rand() % 4);
            int r = pos / 72;
            int c = pos % 72;
            w.addCreature(r, c, dir, &hopper);
        }
        for (int i=0; i<10; ++i) {
            int pos = rand() % 5184;
            Direction dir = Direction(rand() % 4);
            int r = pos / 72;
            int c = pos % 72;
            w.addCreature(r, c, dir, &rover);
        }
        for (int i=0; i<10; ++i) {
            int pos = rand() % 5184;
            Direction dir = Direction(rand() % 4);
            int r = pos / 72;
            int c = pos % 72;
            w.addCreature(r, c, dir, &trap);
        }
        w.simulate(1000, 100);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // --------
    // MyTest 1
    // --------
    try {
        cout << "*** MyTest 1 (1x4) ***" << endl;
        World w (1, 4);
        w.addCreature(0, 0, EAST, &trap);
        w.addCreature(0, 3, WEST, &hopper);
        w.simulate(10, 1);
    } catch (exception&) {
        assert(false);
    }

    // --------
    // MyTest 2
    // --------
    try {
        srand(0);
        cout << "*** MyTest 2 (3x3) ***" << endl;
        World w (3, 3);
        w.addCreature(0, 0, EAST, &rover);
        w.simulate(10, 1);
    } catch (exception&) {
        assert(false);
    }

    // --------
    // MyTest 3
    // --------
    try {
        srand(0);
        cout << "*** MyTest 3 (1x11) ***" << endl;
        World w (1, 11);
        w.addCreature(0, 0, EAST, &rover);
        w.addCreature(0, 2, EAST, &food);
        w.addCreature(0, 4, EAST, &food);
        w.addCreature(0, 6, EAST, &food);
        w.addCreature(0, 8, EAST, &food);
        w.addCreature(0, 10, EAST, &food);
        w.simulate(15, 1);
    } catch (exception&) {
        assert(false);
    }

    // --------
    // MyTest 4
    // --------
    try {
        cout << "*** MyTest 4 (4 x 6) ***" << endl;
        World w (4, 6);
        w.addCreature(0, 0, NORTH, &food);
        w.addCreature(0, 2, NORTH, &food);
        w.addCreature(0, 4, NORTH, &food);
        w.addCreature(1, 1, NORTH, &food);
        w.addCreature(1, 3, NORTH, &food);
        w.addCreature(1, 5, NORTH, &food);
        w.addCreature(2, 0, NORTH, &food);
        w.addCreature(2, 2, NORTH, &food);
        w.addCreature(2, 4, NORTH, &food);
        w.addCreature(3, 1, NORTH, &food);
        w.addCreature(3, 3, NORTH, &food);
        w.addCreature(3, 5, WEST, &rover);
        w.simulate(20, 2);
    } catch (exception&) {
        assert(false);
    }

    // --------
    // MyTest 5
    // --------
    try {
        srand(0);
        cout << "*** MyTest 5 (8 x 8) ***" << endl;
        World w (8, 8);
        w.addCreature(3, 4, NORTH, &rover);
        w.addCreature(4, 3, SOUTH, &rover);
        w.addCreature(0, 4, EAST, &food);
        w.addCreature(7, 3, WEST, &food);

        w.addCreature(7, 7, NORTH, &food);
        w.addCreature(0, 0, SOUTH, &food);
        w.simulate(20, 1);
    } catch (exception&) {
        assert(false);
    }

    // --------
    // MyTest 6
    // --------
    try {
        srand(0);
        cout << "*** MyTest 6 (10 x 10) ***" << endl;
        World w (10, 10);
        w.addCreature(0, 0, EAST, &rover);
        w.addCreature(0, 9, SOUTH, &rover);
        w.addCreature(9, 9, WEST, &rover);
        w.addCreature(9, 0, NORTH, &rover);

        w.addCreature(4, 4, NORTH, &food);
        w.addCreature(4, 5, EAST, &food);
        w.addCreature(5, 5, SOUTH, &food);
        w.addCreature(5, 4, WEST, &food);

        w.simulate(40, 5);
    } catch (exception&) {
        assert(false);
    }

    return 0;}
