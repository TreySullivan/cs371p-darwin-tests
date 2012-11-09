#include <iostream>
#include <sstream>
#include <string>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Darwin.h"

using namespace std;

struct TestDarwin : CppUnit::TestFixture {
// ~~~~~~~~~~~~~~~~~~~~~~~~~
// Species Tests
// ~~~~~~~~~~~~~~~~~~~~~~~~~
	// ------------------------
	// Constructor + const icon
	// ------------------------
	void test_species_1 () {
		Species s ('@');
		CPPUNIT_ASSERT(s.icon == '@');
	}
	void test_species_2 () {
		Species s ('!');
		CPPUNIT_ASSERT(s.icon == '!');
	}
	void test_species_3 () {
		Species s ('~');

		CPPUNIT_ASSERT(s.icon == '~');
	}

	// ---
	// add
	// ---
	void test_add_1 () {
		ostringstream w;
		Species p ('@');
		p.add(HOP);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. HOP\n");
	}
	void test_add_2 () {
		ostringstream w;
		Species p ('@');
		p.add(HOP);
		p.add(LEFT);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. HOP\n1. LEFT\n");
	}
	void test_add_3 () {
		ostringstream w;
		Species p ('@');
		p.add(HOP);
		p.add(LEFT);
		p.add(INFECT);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. HOP\n1. LEFT\n2. INFECT\n");
	}
	void test_add_4 () {
		ostringstream w;
		Species p ('@');
		p.add(HOP);
		p.add(LEFT);
		p.add(INFECT);
		p.add(RIGHT);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. HOP\n1. LEFT\n2. INFECT\n3. RIGHT\n");
	}
	void test_add_5 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_EMPTY, 2);
		p.add(LEFT);
		p.add(HOP);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. IF_EMPTY 2\n1. LEFT\n2. HOP\n3. GO 0\n");
	}
	void test_add_6 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_WALL, 3);
		p.add(HOP);
		p.add(LEFT);
		p.add(RIGHT);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. IF_WALL 3\n1. HOP\n2. LEFT\n3. RIGHT\n4. GO 0\n");
	}
	void test_add_7 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_RANDOM, 3);
		p.add(HOP);
		p.add(LEFT);
		p.add(RIGHT);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. IF_RANDOM 3\n1. HOP\n2. LEFT\n3. RIGHT\n4. GO 0\n");
	}
	void test_add_8 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_ENEMY, 2);
		p.add(LEFT);
		p.add(INFECT);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(w.str() == "0. IF_ENEMY 2\n1. LEFT\n2. INFECT\n3. GO 0\n");
	}
	
	// ----------------
	// getInstructionAt
	// ----------------
	void test_getInstructionAt_1 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_EMPTY, 2);
		p.add(LEFT);
		p.add(HOP);
		p.add(GO, 0);
		CPPUNIT_ASSERT(p.getInstructionAt(0).op == IF_EMPTY);
		CPPUNIT_ASSERT(p.getInstructionAt(0).line == 2);
		CPPUNIT_ASSERT(p.getInstructionAt(1).op == LEFT);
		CPPUNIT_ASSERT(p.getInstructionAt(2).op == HOP);
		CPPUNIT_ASSERT(p.getInstructionAt(3).op == GO);
		CPPUNIT_ASSERT(p.getInstructionAt(3).line == 0);
	}
	void test_getInstructionAt_2 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_WALL, 3);
		p.add(HOP);
		p.add(LEFT);
		p.add(RIGHT);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(p.getInstructionAt(0).op == IF_WALL);
		CPPUNIT_ASSERT(p.getInstructionAt(0).line == 3);
		CPPUNIT_ASSERT(p.getInstructionAt(3).op == RIGHT);
	}
	void test_getInstructionAt_3 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_ENEMY, 2);
		p.add(LEFT);
		p.add(INFECT);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(p.getInstructionAt(0).op == IF_ENEMY);
		CPPUNIT_ASSERT(p.getInstructionAt(0).line == 2);
		CPPUNIT_ASSERT(p.getInstructionAt(2).op == INFECT);
	}
	void test_getInstructionAt_4 () {
		ostringstream w;
		Species p ('@');
		p.add(IF_RANDOM, 2);
		p.add(LEFT);
		p.add(RIGHT);
		p.add(IF_EMPTY, 5);
		p.add(HOP);
		p.add(GO, 0);
		p.printProgram(w);
		CPPUNIT_ASSERT(p.getInstructionAt(0).op == IF_RANDOM);
		CPPUNIT_ASSERT(p.getInstructionAt(0).line == 2);
		CPPUNIT_ASSERT(p.getInstructionAt(3).op == IF_EMPTY);
		CPPUNIT_ASSERT(p.getInstructionAt(3).line == 5);
		CPPUNIT_ASSERT(p.getInstructionAt(5).op == GO);
		CPPUNIT_ASSERT(p.getInstructionAt(5).line == 0);
	}
// ~~~~~~~~~~~~~~
// Creature Tests
// ~~~~~~~~~~~~~~
	// --------------------
	// Creature constructor
	// --------------------
	void test_creature_1 () {
		Species s ('!');
		Creature c (NORTH, &s);
		CPPUNIT_ASSERT(c.direction == NORTH);
		CPPUNIT_ASSERT(c.species_pointer = &s);
		CPPUNIT_ASSERT(c.species_pointer->icon == '!');
	}
	void test_creature_2 () {
		Species s ('?');
		Creature c (EAST, &s);
		CPPUNIT_ASSERT(c.direction == EAST);
		CPPUNIT_ASSERT(c.species_pointer = &s);
		CPPUNIT_ASSERT(c.species_pointer->icon == '?');
	}
	void test_creature_3 () {
		Species s ('D');
		Creature c (SOUTH, &s);
		CPPUNIT_ASSERT(c.direction == SOUTH);
		CPPUNIT_ASSERT(c.species_pointer = &s);
		CPPUNIT_ASSERT(c.species_pointer->icon == 'D');
	}

	// ---------------
	// nextInstruction
	// ---------------
	void test_nextInstruction_1 () {
		Species s ('1');
		s.add(HOP);
		s.add(GO, 0);
		Creature c (NORTH, &s);
		Instruction i = c.nextInstruction(0);
		CPPUNIT_ASSERT(i.op == HOP);
	}
	void test_nextInstruction_2 () {
		Species s ('1');
		s.add(HOP);
		s.add(GO, 0);
		Creature c (NORTH, &s);
		c.program_counter = 1;
		Instruction i = c.nextInstruction(0);
		CPPUNIT_ASSERT(i.op == GO);
		CPPUNIT_ASSERT(i.line == 0);
	}
	void test_nextInstruction_3 () {
		Species s ('1');
		s.add(HOP);
		s.add(GO, 0);
		Creature c (NORTH, &s);
		c.turn_num = 2;
		Instruction i = c.nextInstruction(1);
		CPPUNIT_ASSERT(i.op == TURN_OVER);
	}

// ~~~~~~~~~~~~~~~~~~~~~~~~~
// World Tests
// ~~~~~~~~~~~~~~~~~~~~~~~~~
	// -----------------
	// getNeighboringRow
	// -----------------
	void test_getNeighboringRow_1 () {
		int i = World::getNeighboringRow(3, WEST);
		CPPUNIT_ASSERT(i == 3);
	}
	void test_getNeighboringRow_2 () {
		int i = World::getNeighboringRow(11, NORTH);
		CPPUNIT_ASSERT(i == 10);
	}
	void test_getNeighboringRow_3 () {
		int i = World::getNeighboringRow(5, EAST);
		CPPUNIT_ASSERT(i == 5);
	}
	void test_getNeighboringRow_4 () {
		int i = World::getNeighboringRow(1, SOUTH);
		CPPUNIT_ASSERT(i == 2);
	}

	// -----------------
	// getNeighboringCol
	// -----------------
	void test_getNeighboringCol_1 () {
		int i = World::getNeighboringCol(1, WEST);
		CPPUNIT_ASSERT(i == 0);
	}
	void test_getNeighboringCol_2 () {
		int i = World::getNeighboringCol(2, NORTH);
		CPPUNIT_ASSERT(i == 2);
	}
	void test_getNeighboringCol_3 () {
		int i = World::getNeighboringCol(3, EAST);
		CPPUNIT_ASSERT(i == 4);
	}
	void test_getNeighboringCol_4 () {
		int i = World::getNeighboringCol(4, SOUTH);
		CPPUNIT_ASSERT(i == 4);
	}

	// ------------------------
	// Constructor + const icon
	// ------------------------
	void test_world_1 () {
		ostringstream o;
		World world;
		world.print(o);
		CPPUNIT_ASSERT(o.str() == "  0\n0 .\n");
	}
	void test_world_2 () {
		ostringstream o;
		World world (3, 3);
		world.print(o);
		CPPUNIT_ASSERT(o.str() == "  012\n0 ...\n1 ...\n2 ...\n");
	}
	void test_world_3 () {
		ostringstream o;
		World world (2, 3);
		world.print(o);
		CPPUNIT_ASSERT(o.str() == "  012\n0 ...\n1 ...\n");
	}
	
	// ----------------
	// isWithinBoundary
	// ----------------
	void test_isWithinBoundary_1 () {
		World world (3, 3);
		CPPUNIT_ASSERT(world.isWithinBoundary(0, 0));
		CPPUNIT_ASSERT(world.isWithinBoundary(1,1));
		CPPUNIT_ASSERT(!world.isWithinBoundary(-1, -1));
	}
	void test_isWithinBoundary_2 () {
		World world;
		CPPUNIT_ASSERT(world.isWithinBoundary(0, 0));
		CPPUNIT_ASSERT(!world.isWithinBoundary(100, 200));
		CPPUNIT_ASSERT(!world.isWithinBoundary(-1, -1));
	}
	void test_isWithinBoundary_3 () {
		World world (3, 2);
		CPPUNIT_ASSERT(world.isWithinBoundary(0, 0));
		CPPUNIT_ASSERT(world.isWithinBoundary(2, 1));
		CPPUNIT_ASSERT(!world.isWithinBoundary(1, 2));
		CPPUNIT_ASSERT(!world.isWithinBoundary(3, 1));
		CPPUNIT_ASSERT(!world.isWithinBoundary(1, 3));
		CPPUNIT_ASSERT(!world.isWithinBoundary(-1, -1));
	}

	// -----------
	// addCreature
	// -----------
	void test_addCreature_1 () {
		ostringstream o;
		World w;
		Species s ('s');
		w.addCreature(0, 0, NORTH, &s);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  0\n0 s\n");
	}
	void test_addCreature_2 () {
		ostringstream o;
		World w(2, 3);
		Species s ('s');
		w.addCreature(1, 1, NORTH, &s);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  012\n0 ...\n1 .s.\n");
	}
	void test_addCreature_3 () {
		ostringstream o;
		World w(3, 3);
		Species s ('s');
		w.addCreature(2, 2, NORTH, &s);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  012\n0 ...\n1 ...\n2 ..s\n");
	}

	// --------------------
	// getCreaturePointerAt
	// --------------------
	void test_getCreaturePointerAt_1 () {
		World w;
		Species one ('1');
		w.addCreature(0, 0, WEST, &one);
		Creature* cp = w.getCreaturePointerAt(0, 0);
		CPPUNIT_ASSERT(cp->species_pointer == &one);
		CPPUNIT_ASSERT(cp->species_pointer->icon == '1');
	}
	void test_getCreaturePointerAt_2 () {
		World w(2, 2);
		Species one ('1');
		w.addCreature(0, 0, WEST, &one);
		Creature* cp = w.getCreaturePointerAt(0, 0);
		CPPUNIT_ASSERT(cp->species_pointer == &one);
		CPPUNIT_ASSERT(w.getCreaturePointerAt(1, 1) == 0);
	}
	void test_getCreaturePointerAt_3 () {
		World w(3, 3);
		Species one ('1');
		Species two ('2');
		w.addCreature(0, 0, WEST, &one);
		w.addCreature(2, 2, EAST, &two);
		CPPUNIT_ASSERT(w.getCreaturePointerAt(0, 0)->species_pointer == &one);
		CPPUNIT_ASSERT(w.getCreaturePointerAt(1, 1) == 0);
		CPPUNIT_ASSERT(w.getCreaturePointerAt(2, 2)->species_pointer == &two);
		CPPUNIT_ASSERT(w.getCreaturePointerAt(-1, 234) == 0);
	}

	void test_executeInstruction_1 () {
		ostringstream o;
		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 0, EAST, &s);
		Creature* cp = w.getCreaturePointerAt(0, 0);
		w.executeInstruction(cp, 0, 0);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 .!\n1 ..\n");
	}
	void test_executeInstruction_2 () {
		ostringstream o;
		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 0, NORTH, &s);
		Creature* cp = w.getCreaturePointerAt(0, 0);
		w.executeInstruction(cp, 0, 0);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 !.\n1 ..\n");
	}
	void test_executeInstruction_3 () {
		ostringstream o;
		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 0, SOUTH, &s);
		Creature* cp = w.getCreaturePointerAt(0, 0);
		w.executeInstruction(cp, 0, 0);
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 ..\n1 !.\n");
	}

	void test_simulateRound_1 () {
		ostringstream o;
		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 0, EAST, &s);
		w.addCreature(1, 1, WEST, &s);
		w.simulateRound();
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 .!\n1 !.\n");
	}

	void test_simulateRound_2 () {
		ostringstream o;
		Species t ('*');
		t.add(INFECT);
		t.add(GO, 0);

		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 1, WEST, &t);
		w.addCreature(0, 0, EAST, &s);
		w.simulateRound();
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 **\n1 ..\n");
	}

	void test_simulateRound_3 () {
		ostringstream o;
		Species f ('f');

		Species s ('!');
		s.add(IF_WALL, 2);
		s.add(HOP);
		s.add(RIGHT);
		s.add(GO, 0);
		World w (2, 2);
		w.addCreature(0, 1, WEST, &f);
		w.addCreature(0, 0, EAST, &s);
		w.simulateRound();
		w.print(o);
		CPPUNIT_ASSERT(o.str() == "  01\n0 !f\n1 ..\n");
	}

	void test_simulate_1 () {
		Species trap ('t');
		trap.add(IF_ENEMY, 3);
		trap.add(LEFT);
		trap.add(GO, 0);
		trap.add(INFECT);
		trap.add(GO, 0);
		
		Species hopper ('h');
     	hopper.add(HOP);
     	hopper.add(GO, 0);

		ostringstream o;
		World w (2, 4);
		w.addCreature(0, 0, EAST, &trap);
		w.addCreature(0, 3, WEST, &hopper);
		w.addCreature(3, 3, WEST, &trap);
		w.addCreature(3, 3, EAST, &hopper);
		w.simulate(5, 5, o);
		CPPUNIT_ASSERT(o.str() == "Turn = 0.\n  0123\n0 t..h\n1 ....\n\nTurn = 5.\n  0123\n0 tt..\n1 ....\n\n");
	}

	void test_simulate_2 () {
		srand(0);
		Species food ('f');
     	food.add(LEFT);
     	food.add(GO, 0);

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

		ostringstream o;
		World w (1, 6);
		w.addCreature(0, 0, EAST, &rover);
		w.addCreature(0, 5, NORTH, &food);
		w.simulate(5, 5, o);
		CPPUNIT_ASSERT(o.str() == "Turn = 0.\n  012345\n0 r....f\n\nTurn = 5.\n  012345\n0 ....rr\n\n");
	}
	void test_simulate_3 () {
		srand(0);
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

		ostringstream o;
		World w (3, 3);
		w.addCreature(0, 0, EAST, &rover);
		w.addCreature(2, 2, WEST, &rover);
		w.simulate(20, 20, o);
		CPPUNIT_ASSERT(o.str() == "Turn = 0.\n  012\n0 r..\n1 ...\n2 ..r\n\nTurn = 20.\n  012\n0 ...\n1 ...\n2 r.r\n\n");
	}


// ~~~~~
// suite
// ~~~~~
	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(test_species_1);
	CPPUNIT_TEST(test_species_2);
	CPPUNIT_TEST(test_species_3);

	CPPUNIT_TEST(test_add_1);
	CPPUNIT_TEST(test_add_2);
	CPPUNIT_TEST(test_add_3);
	CPPUNIT_TEST(test_add_4);
	CPPUNIT_TEST(test_add_5);
	CPPUNIT_TEST(test_add_6);
	CPPUNIT_TEST(test_add_7);
	CPPUNIT_TEST(test_add_8);

	CPPUNIT_TEST(test_getInstructionAt_1);
	CPPUNIT_TEST(test_getInstructionAt_2);
	CPPUNIT_TEST(test_getInstructionAt_3);
	CPPUNIT_TEST(test_getInstructionAt_4);

	CPPUNIT_TEST(test_creature_1);
	CPPUNIT_TEST(test_creature_2);
	CPPUNIT_TEST(test_creature_3);

	CPPUNIT_TEST(test_nextInstruction_1);
	CPPUNIT_TEST(test_nextInstruction_2);
	CPPUNIT_TEST(test_nextInstruction_3);

	CPPUNIT_TEST(test_getNeighboringRow_1);
	CPPUNIT_TEST(test_getNeighboringRow_2);
	CPPUNIT_TEST(test_getNeighboringRow_3);
	CPPUNIT_TEST(test_getNeighboringRow_4);

	CPPUNIT_TEST(test_getNeighboringCol_1);
	CPPUNIT_TEST(test_getNeighboringCol_2);
	CPPUNIT_TEST(test_getNeighboringCol_3);
	CPPUNIT_TEST(test_getNeighboringCol_4);

	CPPUNIT_TEST(test_isWithinBoundary_1);
	CPPUNIT_TEST(test_isWithinBoundary_2);
	CPPUNIT_TEST(test_isWithinBoundary_3);

	CPPUNIT_TEST(test_world_1);
	CPPUNIT_TEST(test_world_2);
	CPPUNIT_TEST(test_world_3);

	CPPUNIT_TEST(test_addCreature_1);
	CPPUNIT_TEST(test_addCreature_2);
	CPPUNIT_TEST(test_addCreature_3);

	CPPUNIT_TEST(test_getCreaturePointerAt_1);
	CPPUNIT_TEST(test_getCreaturePointerAt_2);
	CPPUNIT_TEST(test_getCreaturePointerAt_3);

	CPPUNIT_TEST(test_executeInstruction_1);
	CPPUNIT_TEST(test_executeInstruction_2);
	CPPUNIT_TEST(test_executeInstruction_3);

	CPPUNIT_TEST(test_simulateRound_1);
	CPPUNIT_TEST(test_simulateRound_2);
	CPPUNIT_TEST(test_simulateRound_3);

	CPPUNIT_TEST(test_simulate_1);
	CPPUNIT_TEST(test_simulate_2);
	CPPUNIT_TEST(test_simulate_3);

	CPPUNIT_TEST_SUITE_END();
};

int main() {
	ios_base::sync_with_stdio(false);
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();
}