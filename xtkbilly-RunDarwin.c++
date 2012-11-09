// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.app
    % valgrind RunDarwin.app > RunDarwin.out

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
	Species food('f');
	food.addAction("left");
	food.addControl("go", 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

	Species hopper('h');
	hopper.addAction("hop");
	hopper.addControl("go", 0);

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

	Species rover('r');
	rover.addControl("if_enemy", 9);
	rover.addControl("if_empty", 7);
	rover.addControl("if_random", 5);
	rover.addAction("left");
	rover.addControl("go", 0);
	rover.addAction("right");
	rover.addControl("go", 0);
	rover.addAction("hop");
	rover.addControl("go", 0);
	rover.addAction("infect");
	rover.addControl("go", 0);

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

	Species trap('t');
	trap.addControl("if_enemy", 3);
	trap.addAction("left");
	trap.addControl("go", 0);
	trap.addAction("infect");
	trap.addControl("go", 0);


	// ----
    // best
    // ----
	Species best('b');
	best.addControl("if_enemy", 6);
	best.addControl("if_empty", 4);
	best.addAction("left");
	best.addControl("go", 0);
	best.addAction("hop");
	best.addControl("go", 0);
	best.addAction("infect");
	best.addControl("go", 0);


    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
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
		Grid g1(8, 8);
		g1.place(food, 0, 0, Creature::EAST);
		g1.place(hopper, 3, 3, Creature::NORTH);
		g1.place(hopper, 3, 4, Creature::EAST);
		g1.place(hopper, 4, 4, Creature::SOUTH);
		g1.place(hopper, 4, 3, Creature::WEST);
		g1.place(food, 7, 7, Creature::NORTH);

		g1.simulate(5);
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
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
		Grid g2(7, 9);
		g2.place(trap, 0, 0, Creature::SOUTH);
		g2.place(hopper, 3, 2, Creature::EAST);
		g2.place(rover, 5, 4, Creature::NORTH);
		g2.place(trap, 6, 8, Creature::WEST);

		g2.simulate(5);
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
		Grid g3(72, 72);
		int n;

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g3.place(food, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g3.place(hopper, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g3.place(rover, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g3.place(trap, p / 72, p % 72, d);
			++n;
		}

		g3.simulate(1000);

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
		Grid g4(72, 72);
		int n;

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g4.place(food, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g4.place(hopper, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g4.place(rover, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g4.place(trap, p / 72, p % 72, d);
			++n;
		}

		n = 0;
		while (n < 10) {
			int p = rand() % 5184;
			int d = rand() % 4;
			g4.place(best, p / 72, p % 72, d);
			++n;
		}

		g4.simulate(1000);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // darwin 1x5
    // ----------

    try {
        cout << "*** Darwin 1x5 ***" << endl;

		Grid g5(1, 5);
		g5.place(hopper, 0, 0, Creature::EAST);
		g5.place(trap, 0, 4, Creature::SOUTH);

		g5.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // darwin 5x5
    // ----------

    try {
        cout << "*** Darwin 5x5 ***" << endl;

		Grid g6(5, 5);
		g6.place(best, 0, 0, Creature::EAST);
		g6.place(best, 0, 4, Creature::SOUTH);
		g6.place(best, 4, 0, Creature::NORTH);
		g6.place(best, 4, 4, Creature::WEST);

		g6.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // darwin 30x30
    // ----------

    try {
        cout << "*** Darwin 30x30 ***" << endl;

		Grid g7(30, 30);
		int n = 0;
		while (n < 30) {
			int m = 0;
			while (m < 30) {
				if (n == 15 && m == 15) {
					g7.place(trap, n, m, 0);
				} else {
					g7.place(food, n, m, 0);
				}
				++m;
			}
			++n;
		}

		g7.simulate(15);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // darwin 50x50
    // ----------

	try {
        cout << "*** Darwin 50x50 ***" << endl;
		srand(0);

		Grid g8(50, 50);
		int n = 0;
		while (n < 50) {
			int p = rand() % 2500;
			g8.place(food, p / 50, p % 50);
			++n;
		}

		int q = rand() % 2500;
		g8.place(best, q / 50, q % 50);

		g8.simulate(15);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	// darwin 10x10
	try {
        cout << "*** Darwin 10x10 ***" << endl;
		srand(0);

		Grid g9(10, 10);
		int p = rand() % 100;
		g9.place(food, p / 10, p % 10);
		g9.place(rover, p/ 10, p % 10);

		g9.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// darwin 7x7
	try {
        cout << "*** Darwin 7x7 ***" << endl;
		Grid g10(7, 7);

		g10.place(food, 3, 3);
		g10.place(best, 0, 0, Creature::SOUTH);

		g10.simulate(10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	
    return 0;}
