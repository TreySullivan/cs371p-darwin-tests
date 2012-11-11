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
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        World w(8, 8);
        Creature f(food, 0, 0, EAST, &w); 
        Creature h(hopper, 3, 3, NORTH, &w);
        Creature h2(hopper, 3, 4, EAST, &w);
        Creature h3(hopper, 4, 4, SOUTH, &w);
        Creature h4(hopper, 4, 3, WEST, &w);
        Creature f2(food, 7, 7, NORTH, &w); 
        Controller c(&w);
        for ( int i = 0; i < 6; i++ ) {
          cout << "turn = " << i << endl;
          c.print_world();
          c.execute_turn();
          cout << endl;
          cout << endl;
        }
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
        World w(7,9);
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);

        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);

        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);

        Creature t(trap, 0, 0, SOUTH, &w);
        Creature h(hopper, 3, 2, EAST, &w);
        Creature r(rover, 5, 4, NORTH, &w);
        Creature t2(trap, 6, 8, WEST, &w);
        
        Controller c(&w);
        for (int i = 0; i < 6; i++) {
          cout << "turn = " << i << endl;
          c.print_world();
          c.execute_turn();
        } 
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
        
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);

        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);

        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);

        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);

        World w(72, 72);

        srand(0);
        int pos = rand() % (72 * 72);
        int row = pos / 72;
        int col = pos % 72;
        int dir = rand() % 4;
        Creature f(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f2(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f3(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f4(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f5(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f6(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f7(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f8(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f9(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f10(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h2(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h3(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h4(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h5(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h6(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h7(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h8(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h9(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h10(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r(rover, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r2(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r3(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r4(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r5(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r6(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r7(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r8(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r9(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r10(rover, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t2(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t3(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t4(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t5(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t6(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t7(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t8(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t9(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t10(trap, row, col, dir, &w);

        Controller c(&w);
        c.print_world();

        for ( int i = 1; i <= 1000; i++) {
          if ( i % 100 == 0 )
            c.print_world();
          c.execute_turn();
        }
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


        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);

        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);

        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);

        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);

        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(72, 72);

        srand(0);
        int pos = rand() % (72 * 72);
        int row = pos / 72;
        int col = pos % 72;
        int dir = rand() % 4;
        Creature f(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f2(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f3(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f4(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f5(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f6(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f7(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f8(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f9(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature f10(food, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h2(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h3(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h4(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h5(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h6(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h7(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h8(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h9(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature h10(hopper, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r(rover, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r2(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r3(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r4(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r5(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r6(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r7(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r8(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r9(rover, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature r10(rover, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t2(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t3(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t4(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t5(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t6(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t7(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t8(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t9(trap, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature t10(trap, row, col, dir, &w);

//Best
        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b(best, row, col, dir, &w);

    
        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b2(best, row, col, dir, &w);

    
        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b3(best, row, col, dir, &w);
    
        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b4(best, row, col, dir, &w);
    
        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b5(best, row, col, dir, &w);


        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b6(best, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b7(best, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b8(best, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b9(best, row, col, dir, &w);

        pos = rand() % (72 * 72);
        row = pos / 72;
        col = pos % 72;
        dir = rand() % 4;
        Creature b10(best, row, col, dir, &w);

        Controller c(&w);
        c.print_world();

        for ( int i = 1; i <= 1000; i++) {
          if ( i % 100 == 0 )
            c.print_world();
          c.execute_turn();
        }
      }

    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "TEST #5 " << endl;

        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);

        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);

        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);

        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);

        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);

        Creature b(best, 0, 0, SOUTH, &w);
        Creature f(food, 3, 3, NORTH, &w);
        Creature h(hopper, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature r(rover, 4, 4, EAST, &w);

        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
          cout << "Turn = " << i << endl;
          c.print_world();
          c.execute_turn();
        }
      }
    
      catch (const invalid_argument&) {
        assert(false);
      }
      catch (const out_of_range&) {
        assert(false);
      }  
    
    try {
        
        cout << "TEST #6" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature b2(best, 3, 3, NORTH, &w);
        Creature b3(best, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature r(rover, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  

    try {
        cout << "TEST #7" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature b2(best, 3, 3, NORTH, &w);
        Creature t3(trap, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature t2(trap, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  
    try {
        cout << "TEST #8" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature b2(best, 3, 3, NORTH, &w);
        Creature f(food, 2, 2, EAST, &w);
        Creature r2(rover, 1, 1, WEST, &w);
        Creature r(rover, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  
    try {
        cout << "TEST #9" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature f(food, 3, 3, NORTH, &w);
        Creature h(hopper, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature t2(trap, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  
    try {
        cout << "TEST #10" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature b2(best, 3, 3, NORTH, &w);
        Creature h(hopper, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature r(rover, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  
    try {
        cout << "TEST #11" << endl;
        Species trap("trap");
        trap.add_instruction(IF_ENEMY, 3);
        trap.add_instruction(LEFT);
        trap.add_instruction(GO, 0);
        trap.add_instruction(INFECT);
        trap.add_instruction(GO, 0);
        
        Species hopper("hopper");
        hopper.add_instruction(HOP);
        hopper.add_instruction(GO, 0);
        
        Species rover("rover");
        rover.add_instruction(IF_ENEMY, 9);
        rover.add_instruction(IF_EMPTY, 7);
        rover.add_instruction(IF_RANDOM, 5);
        rover.add_instruction(LEFT);
        rover.add_instruction(GO, 0); 
        rover.add_instruction(RIGHT);
        rover.add_instruction(GO, 0);
        rover.add_instruction(HOP);
        rover.add_instruction(GO, 0);
        rover.add_instruction(INFECT);
        rover.add_instruction(GO, 0);
        
        Species food("food");
        food.add_instruction(LEFT);
        food.add_instruction(GO, 0);
        
        Species best("best");
        best.add_instruction(IF_RANDOM, 3);
        best.add_instruction(LEFT);
        best.add_instruction(GO, 4);
        best.add_instruction(RIGHT);
        best.add_instruction(IF_ENEMY, 8);
        best.add_instruction(IF_WALL, 0);
        best.add_instruction(HOP);
        best.add_instruction(GO, 0);
        best.add_instruction(INFECT);
        best.add_instruction(GO, 0);
        World w(5, 5);
        
        Creature b(best, 0, 0, SOUTH, &w);
        Creature f(food, 3, 3, NORTH, &w);
        Creature f2(food, 2, 2, EAST, &w);
        Creature t(trap, 1, 1, WEST, &w);
        Creature r(rover, 4, 4, EAST, &w);
        
        Controller c(&w);
        for (int i = 0; i <= 5; i++) {
            cout << "Turn = " << i << endl;
            c.print_world();
            c.execute_turn();
        }
    }
    
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }  

    
    return 0;}
