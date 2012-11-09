/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#define class struct
#include "Darwin.h"
#include <cstdlib>

// -------------
// TestDarwin
// -------------

struct TestDarwin : CppUnit::TestFixture {
	
	//-------------------------------------------------------
	//		INSTRUCTION TESTING
	//-------------------------------------------------------
	void test_instruction1 () {
		Instruction i("hop");
		CPPUNIT_ASSERT(i.to_string().compare("hop") == 0);
		CPPUNIT_ASSERT(i.gotoLine() == -1);
	}
	
	void test_instruction2 () {
		Instruction i("go", 2);
		CPPUNIT_ASSERT(i.to_string().compare("go") == 0);
		CPPUNIT_ASSERT(i.gotoLine() == 2);
	}
	
	void test_instruction3 () {
		Instruction i("go", 1);
		Instruction j("go", 1);
		
		CPPUNIT_ASSERT(i.to_string().compare(j.to_string()) == 0);
		CPPUNIT_ASSERT(i.gotoLine() == j.gotoLine());
		CPPUNIT_ASSERT(&i != &j);
	}

	//-------------------------------------------------------
	//		SPECIES TESTING
	//-------------------------------------------------------

	void test_species_constructor1 () {
		char c = '.';
		Species s;
		CPPUNIT_ASSERT(c == s._c);
		CPPUNIT_ASSERT(s.instructLength() == 0);
	}

	void test_species_constructor2 () {
		char c = 'f';
		Species s('f');
		CPPUNIT_ASSERT(c == s._c);
		CPPUNIT_ASSERT(s.instructLength() == 0);
	}

	void test_species_constructor3 () {
		Species s('p');
		Species t('u');
		CPPUNIT_ASSERT(s._c != t._c);
		CPPUNIT_ASSERT(s.instructLength() == t.instructLength());
	}
	
	void test_species_addInstruction1 () {
		Species f('f');
		
		f.addAction("hop");
		CPPUNIT_ASSERT(f.instructLength() == 1);
		
		f.addAction("left");
		f.addAction("right");
		CPPUNIT_ASSERT(f.instructLength() == 3);
		CPPUNIT_ASSERT(f._ins[1].to_string().compare("left") == 0);
	}
	
	void test_species_addInstruction2 () {
		Species t('t');
		t.addAction("hop");
		t.addAction("left");
		t.addAction("right");
		t.addAction("infect");
		
		t.addControl("go", 0);
		t.addControl("if_empty", 1);
		t.addControl("if_wall", 2);
		t.addControl("if_random", 3);
		
		CPPUNIT_ASSERT(t.instructLength() == 8);
		CPPUNIT_ASSERT(t._ins[5].to_string().compare("if_empty") == 0);
		CPPUNIT_ASSERT(t._ins[5]._gotoLine == 1);
	}
	
	void test_species_addInstruction3 () {
		Species t('t');
		CPPUNIT_ASSERT_THROW(t.addAction("break"), std::invalid_argument);
		
	}

	void test_species_tile1 () {
		Species s;
		CPPUNIT_ASSERT(s.tile() == '.');
	}

	void test_species_tile2 () {
		Species s('a');
		CPPUNIT_ASSERT(s.tile() == 'a');
	}

	void test_species_tile3 () {
		Species s('x');
		Species t('y');
		CPPUNIT_ASSERT(s.tile() == 'x');
		CPPUNIT_ASSERT(t.tile() == 'y');
		CPPUNIT_ASSERT(s.tile() != t.tile());
	}

	void test_species_getInstruction1 () {
		Species t('t');
		t.addAction("hop");
		t.addControl("go", 0);

		Instruction i = t.getInstruction(0);
		CPPUNIT_ASSERT(i.to_string().compare("hop") == 0);
		CPPUNIT_ASSERT(i.gotoLine() == -1);

		i = t.getInstruction(1);
		CPPUNIT_ASSERT(i.to_string().compare("go") == 0);
		CPPUNIT_ASSERT(i.gotoLine() == 0);
	}

	void test_species_getInstruction2 () {
		Species t('t');
		Species u('u');

		t.addAction("hop");
		t.addControl("go", 0);
		CPPUNIT_ASSERT(t.instructLength() == 2);

		u.addAction("left");
		u.addAction("hop");
		u.addControl("go", 0);
		CPPUNIT_ASSERT(u.instructLength() == 3);

		Instruction i = t.getInstruction(0);
		Instruction j = u.getInstruction(1);
		CPPUNIT_ASSERT(i.to_string().compare(j.to_string()) == 0);
	}

	void test_species_getInstruction3 () {
		Species t('t');
		t.addAction("hop");
		t.addAction("left");
		t.addControl("if_empty", 0);
		CPPUNIT_ASSERT_THROW(t.getInstruction(3), std::out_of_range);
		CPPUNIT_ASSERT_THROW(t.getInstruction(-1), std::out_of_range);
	}



	//-------------------------------------------------------
	//		CREATURE TESTING
	//-------------------------------------------------------
	
	void test_creature_constructor1 () {
		Grid g(4,4);
		Species f('f');
		
		//creating a creature on it's own is pretty useless
		Creature c(g, f);
		CPPUNIT_ASSERT(c._g == &g);
		CPPUNIT_ASSERT(c._s == &f);
		CPPUNIT_ASSERT(c._d == 0);
		CPPUNIT_ASSERT(c._r == 0);
		CPPUNIT_ASSERT(c._c == 0);
		CPPUNIT_ASSERT(c._pc == 0);
		CPPUNIT_ASSERT(c._uc == 0);
	}
	
	void test_creature_constructor2 () {
		Grid g(4,4);
		Species t('t');
		
		Creature c = *(g.place(t, 3, 1, 0));
		CPPUNIT_ASSERT(c._d == 0);
		Creature d = *(g.place(t, 2, 3, 1));
		CPPUNIT_ASSERT(d._d == 1);
		
		CPPUNIT_ASSERT(c._g == d._g);
		CPPUNIT_ASSERT(c._s == d._s);
		CPPUNIT_ASSERT(c._d != d._d);
		CPPUNIT_ASSERT(c._r != d._r);
		CPPUNIT_ASSERT(c._c != d._c);
	}
	
	void test_creature_constructor3 () {
		Grid g(5,5);
		Species s('c');
		Creature c(g, s, 3, 4, 5);
		CPPUNIT_ASSERT(c._r == 3);
		CPPUNIT_ASSERT(c._c == 4);
		CPPUNIT_ASSERT(c._d == 1);
		CPPUNIT_ASSERT('c' == c.tile());
	}
	
	void test_creature_tile1 () {
		Grid g(4,4);
		Species t('t');
		
		Creature c(g, t);
		CPPUNIT_ASSERT(c.tile() == t.tile());
	}
	
	void test_creature_tile2 () {
		Grid g(4,4);
		Species t('t');
		
		Creature c(g, t);
		Creature d(g, t);
		CPPUNIT_ASSERT(c.tile() == d.tile());
	}

	void test_creature_tile3 () {
		Grid g(8,8);
		Species r('r');

		Creature* c = g.place(r, 4, 3, 3);
		CPPUNIT_ASSERT(c->_s == &r);
		CPPUNIT_ASSERT(c->tile() == r.tile());
		CPPUNIT_ASSERT(g.get(4, 3) == c);
		CPPUNIT_ASSERT(g.get(4, 3)->tile() == c->tile());
	}

	void test_creature_ahead1 () {
		Grid g(2,2);
		Species s('s');

		Creature* a = g.place(s, 0, 0, Creature::EAST);
		Creature* b = a->ahead();
		CPPUNIT_ASSERT(b == 0);
	}

	void test_creature_ahead2 () {
		Grid g(2,2);
		Species s('s');

		Creature* a = g.place(s, 0, 1, Creature::EAST);
		Creature* b = a->ahead();
		CPPUNIT_ASSERT(b == a);
	}

	void test_creature_ahead3 () {
		Grid g(2,2);
		Species s('s');

		Creature* a = g.place(s, 0, 0, Creature::EAST);
		Creature* b = g.place(s, 0, 1, Creature::SOUTH);
		Creature* c = a->ahead();
		CPPUNIT_ASSERT(b == c);
	}
	
	void test_creature_direction1 () 
	{
		Grid g(4,4);
		Species s('s');
		
		Creature c(g, s, 0, 0, 1);
		
		c.left();
		CPPUNIT_ASSERT(c._d == 0);
		
		c.right();
		CPPUNIT_ASSERT(c._d == 1);
	}

	void test_creature_direction2 () 
	{
		Grid g(4,4);
		Species s('s');
		
		Creature c(g, s, 0, 0, 3);
		c.left();
		c.left();
		CPPUNIT_ASSERT(c._d == 1);
		
		c.left();
		c.right();
		CPPUNIT_ASSERT(c._d == 1);
	}

	void test_creature_direction3 () 
	{
		Grid g(1,1);
		Species s('s');
		
		Creature* c = g.place(s, 0, 0, 3);
		CPPUNIT_ASSERT(c->_r == 0);
		CPPUNIT_ASSERT(c->_c == 0);
		c->right();
		CPPUNIT_ASSERT(c->_d == 0);
		
		c->left();
		CPPUNIT_ASSERT(c->_d == 3);
	}

	void test_creature_hop1 () {
		Grid g(6,6);
		Species h('h');
		h.addAction("hop");

		Creature* c_ptr = g.place(h, 2, 1, 1);
		CPPUNIT_ASSERT(c_ptr->_r == 2);
		CPPUNIT_ASSERT(c_ptr->_c == 1);
		CPPUNIT_ASSERT(c_ptr->_d == 1);
		//g.print();
		
		c_ptr->hop();
		CPPUNIT_ASSERT(c_ptr->_r == 1);
		CPPUNIT_ASSERT(c_ptr->_c == 1);
		CPPUNIT_ASSERT(c_ptr->_d == 1);
		//g.print();
	}
	
	void test_creature_hop2 () {
		Grid g(4, 4);
		Species t('t');
		Species s('s');

		Creature* a = g.place(t, 1, 1, 2);
		Creature* b = g.place(s, 1, 2, 1);
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 1);
		CPPUNIT_ASSERT(a->_d == 2);
		CPPUNIT_ASSERT(b->_r == 1);
		CPPUNIT_ASSERT(b->_c == 2);
		CPPUNIT_ASSERT(b->_d == 1);
		//g.print();

		a->hop();
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 1);
		CPPUNIT_ASSERT(a->_d == 2);
		//g.print();

		b->hop();
		CPPUNIT_ASSERT(b->_r == 0);
		CPPUNIT_ASSERT(b->_c == 2);
		CPPUNIT_ASSERT(b->_d == 1);
		//g.print();

		a->hop();
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 2);
		CPPUNIT_ASSERT(a->_d == 2);
		//g.print();
	}

	void test_creature_hop3 () {
		Grid g(5,5);
		Species t('t');

		Creature* a = g.place(t, 2, 2, 1);
		CPPUNIT_ASSERT(a->_r == 2);
		CPPUNIT_ASSERT(a->_c == 2);
		CPPUNIT_ASSERT(a->_d == 1);

		a->hop();
		a->hop();
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 2);
		CPPUNIT_ASSERT(a->_d == 1);

		a->hop();
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 2);
		CPPUNIT_ASSERT(a->_d == 1);
	}

	void test_creature_infect1 () {
		Grid g(3,3);
		Species s('s');
		Species t('t');

		Creature* a = g.place(s, 0, 0, 2);
		Creature* b = g.place(t, 0, 1, 1);
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 0);
		CPPUNIT_ASSERT(a->_d == 2);
		CPPUNIT_ASSERT(a->_c + 1 == b->_c);
		CPPUNIT_ASSERT(a->_s != b->_s);

		b->_pc = 3;
		a->infect();
		CPPUNIT_ASSERT(a->_s == b->_s);
		CPPUNIT_ASSERT(b->_pc == 0);
		CPPUNIT_ASSERT(b->_d == 1);
	}

	void test_creature_infect2 () {
		Grid g(3,3);
		Species t('t');

		Creature* a = g.place(t, 0, 0, 2);
		Creature* b = g.place(t, 0, 1, 2);
		CPPUNIT_ASSERT(a->_s == b->_s);

		b->_pc = 3;
		a->infect();
		CPPUNIT_ASSERT(a->_s == b->_s);
		CPPUNIT_ASSERT(b->_pc == 3);
	}

	void test_creature_infect3 () {
		Grid g(3,3);
		Species t('t');

		Creature* a = g.place(t, 0, 0, 2);

		a->infect();
		CPPUNIT_ASSERT(g._m[0][1] == 0);
	}

	void test_creature_control1 () {
		srand(0);
		Grid g(5,5);
		Species t('t');

		Creature* a = g.place(t, 1, 1, Creature::WEST);
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 1);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_pc == 0);

		a->if_empty(1);
		CPPUNIT_ASSERT(a->_pc == 1);

		a->if_wall(300);
		CPPUNIT_ASSERT(a->_pc == 2);

		a->if_random(5);
		CPPUNIT_ASSERT(a->_pc == 5);

		a->if_enemy(300);
		CPPUNIT_ASSERT(a->_pc == 6);

		//a->go(0);
		//CPPUNIT_ASSERT(a->_pc == 0);
	}

	void test_creature_control2 () {
		srand(0);
		Grid g(5,5);
		Species t('t');

		Creature* a = g.place(t, 1, 0, Creature::WEST);
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 0);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_pc == 0);

		a->if_empty(300);
		CPPUNIT_ASSERT(a->_pc == 1);

		a->if_wall(4);
		CPPUNIT_ASSERT(a->_pc == 4);

		a->if_random(3);
		CPPUNIT_ASSERT(a->_pc == 3);

		a->if_enemy(300);
		CPPUNIT_ASSERT(a->_pc == 4);
	}

	void test_creature_control3 () {
		srand(0);
		Grid g(5,5);
		Species t('t');
		Species u('u');

		Creature* a = g.place(t, 1, 2, Creature::SOUTH);
		Creature* b = g.place(u, 2, 2, Creature::WEST);

		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 2);
		CPPUNIT_ASSERT(a->_d == 3);
		CPPUNIT_ASSERT(a->_pc == 0);
		CPPUNIT_ASSERT(a->ahead() == b);

		a->if_empty(300);
		CPPUNIT_ASSERT(a->_pc == 1);

		a->if_wall(300);
		CPPUNIT_ASSERT(a->_pc == 2);

		a->if_random(8); //first is odd
		CPPUNIT_ASSERT(a->_pc == 8);

		a->if_random(8); //second is even
		CPPUNIT_ASSERT(a->_pc == 9);

		a->if_random(8); // third is odd
		CPPUNIT_ASSERT(a->_pc == 8);

		a->if_enemy(0);
		CPPUNIT_ASSERT(a->_pc == 0);
	}

	void test_creature_update1 () {
		srand(0);
		Grid g(2, 2);
		Species t('t');
		t.addAction("hop");
		t.addAction("left");
		t.addControl("go", 0);

		Creature* a = g.place(t, 0, 1, Creature::WEST); //creates creature
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 1);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_pc == 0);
		CPPUNIT_ASSERT(a->_uc == 0);

		a->update();	//creature hops
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 0);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_pc == 1);
		CPPUNIT_ASSERT(a->_uc == 1);
		g._t = 1;
		
		a->update();	//creature turns left
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 0);
		CPPUNIT_ASSERT(a->_d == Creature::SOUTH);
		CPPUNIT_ASSERT(a->_pc == 2);
		CPPUNIT_ASSERT(a->_uc == 2);
		g._t = 2;

		a->update();	//creature hops again
		CPPUNIT_ASSERT(a->_r == 1);
		CPPUNIT_ASSERT(a->_c == 0);
		CPPUNIT_ASSERT(a->_d == Creature::SOUTH);
		CPPUNIT_ASSERT(a->_pc == 1);
		CPPUNIT_ASSERT(a->_uc == 3);
		g._t = 3;
	}

	void test_creature_update2 () {
		srand(0);
		Grid g(3, 3);
		Species t('t');
		t.addControl("if_wall", 3);
		t.addAction("hop");
		t.addControl("go", 0);
		t.addAction("left");
		t.addControl("go", 0);

		Creature* a = g.place(t, 1, 1, Creature::EAST);
		//g.print();
		int n = 0;
		while (n < 5)
		{
			a->update();
			++g._t;
			//g.print();
			++n;
		}

		CPPUNIT_ASSERT(g._t == 5);
		CPPUNIT_ASSERT(a->_uc == 5);
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 1);
		CPPUNIT_ASSERT(a->_d == Creature::WEST);
	}


	//-------------------------------------------------------
	//		GRID TESTING
	//-------------------------------------------------------

	void test_grid_construct1 () {
		
		Grid g(3, 4);
		CPPUNIT_ASSERT(g.numRows() == 3);
		CPPUNIT_ASSERT(g.numCols() == 4);
		
		CPPUNIT_ASSERT(g._m[0][0] == 0);
		CPPUNIT_ASSERT(g._m[0][1] == 0);
		CPPUNIT_ASSERT(g._m[0][2] == 0);
		CPPUNIT_ASSERT(g._m[0][3] == 0);
		CPPUNIT_ASSERT(g._m[1][0] == 0);
		CPPUNIT_ASSERT(g._m[1][1] == 0);
		CPPUNIT_ASSERT(g._m[1][2] == 0);
		CPPUNIT_ASSERT(g._m[1][3] == 0);
		CPPUNIT_ASSERT(g._m[2][0] == 0);
		CPPUNIT_ASSERT(g._m[2][1] == 0);
		CPPUNIT_ASSERT(g._m[2][2] == 0);
		CPPUNIT_ASSERT(g._m[2][3] == 0);
	}
	
	void test_grid_construct2 () {
		int n = 8;
		Grid g (n, n);
		CPPUNIT_ASSERT(g.numRows() == 8);
		CPPUNIT_ASSERT(g.numCols() == 8);
		CPPUNIT_ASSERT(g._m[0][0] == 0);
		CPPUNIT_ASSERT(g._m[4][5] == 0);
		CPPUNIT_ASSERT(g._m[7][7] == 0);
	}
	
	void test_grid_construct3 () {
		CPPUNIT_ASSERT_THROW(Grid g(-1, 5), std::out_of_range);
	}

	void test_grid_get1 () {
		Grid g(3, 4);
		Creature* c_ptr = g.get(1, 2);
		CPPUNIT_ASSERT(c_ptr == 0);
	}
	
	void test_grid_get2 () {
		Grid g(7, 9);
		Species f('f');
		Creature& c = *g.place(f, 3, 4, 0);
		Creature* c_ptr = g.get(3, 4);
		
		CPPUNIT_ASSERT(c_ptr != 0);
		CPPUNIT_ASSERT(c_ptr == &c);
	}

	void test_grid_get3 () {
		Grid g(10, 10);

		CPPUNIT_ASSERT_THROW(g.get(-1, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.get(0, -1), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.get(10, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.get(4, 10), std::out_of_range);
	}
	
	void test_grid_place1 () {
		Species food('f');
		Grid g(8, 8);
		
		Creature* c = g.place(food, 0, 0);
		
		CPPUNIT_ASSERT(c->_g == &g);
		CPPUNIT_ASSERT(g._cage.size() == 1);
		CPPUNIT_ASSERT(&(g._cage[0]) == c);
		CPPUNIT_ASSERT(c->_s == &food);
		CPPUNIT_ASSERT(c->_d == 0);
		CPPUNIT_ASSERT(c->_r == 0);
		CPPUNIT_ASSERT(c->_c == 0);
		
		
	}
	
	void test_grid_place2 () {
		Species food('f');
		Grid g(8, 8);
		
		g.place(food, 0, 1);
		g.place(food, 1, 1);
		g.place(food, 7, 7);
		
		CPPUNIT_ASSERT(food.tile() == 'f');
		CPPUNIT_ASSERT(g._m[0][1]->tile() == food.tile());
		CPPUNIT_ASSERT(g._m[1][1]->tile() == food.tile());
		CPPUNIT_ASSERT(g._m[7][7]->tile() == 'f');
	}

	void test_grid_place3 () {
		Grid g (4, 4);
		Species t('t');
		Species s('s');

		Creature* a = g.place(t, 0, 0, Creature::WEST);
		Creature* b = g.place(t, 0, 1, Creature::WEST);
		Creature* c = g.place(s, 1, 0, Creature::SOUTH);

		CPPUNIT_ASSERT(g._cage.size() == 3);
		CPPUNIT_ASSERT(a == g.get(0,0));
		CPPUNIT_ASSERT(b == g.get(0,1));
		CPPUNIT_ASSERT(c == g.get(1, 0));
		CPPUNIT_ASSERT(a->_g == b->_g);
		CPPUNIT_ASSERT(b->_g == c->_g);
		CPPUNIT_ASSERT(a->_g == &g);

		
		//std::cout << "\n\n\n\n" << &g._cage[0] << std::endl;
		//std::cout << a << "\n\n\n\n" << std::endl;
		
		//std::cout << "\n\n\n\n" << &g._cage[1] << std::endl;
		//std::cout << b << "\n\n\n\n" << std::endl;

		//std::cout << "\n\n\n\n" << &g._cage[2] << std::endl;
		//std::cout << c << "\n\n\n\n" << std::endl;

//		CPPUNIT_ASSERT(a == &(g._cage[0]));
//		CPPUNIT_ASSERT(b == &(g._cage[1]));
//		CPPUNIT_ASSERT(c == &(g._cage[2]));

		CPPUNIT_ASSERT_THROW(g.place(t, -1, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.place(t, 0, -1), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.place(t, 5, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.place(t, 0, 5), std::out_of_range);
	}
	
	void test_grid_move1 () {
		Grid g(4,4);
		Species t('t');

		Creature* a = g.place(t, 0, 0);
		g.move(0,0, 2, 2);
		CPPUNIT_ASSERT(a == g.get(2, 2));
		CPPUNIT_ASSERT(g.get(0,0) == 0);
	}

	void test_grid_move2 () {
		Grid g(4,4);

		g.move(0,0, 2, 2);
		CPPUNIT_ASSERT(g.get(2,2) == 0);
		CPPUNIT_ASSERT(g.get(0,0) == 0);
	}

	void test_grid_move3 () {
		Grid g(4,4);

		CPPUNIT_ASSERT_THROW(g.move(-1, 0, 0, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.move(0, 0, 0, -1), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.move(0, 4, 0, 0), std::out_of_range);
		CPPUNIT_ASSERT_THROW(g.move(0, 0, 4, 0), std::out_of_range);

	}

	void test_grid_print1 () {
		Grid g(4, 4);

		/* uncomment these two lines to see the print
		 * messes up Valgrinds output format otherwise
		 * Should look like:
		 * 
		 * Turn = 0.
		 *   0123
		 * 0 ....
		 * 1 ....
		 * 2 ....
		 * 3 ....
		 * 
		 */
		std::cout << std::endl;
		g.print();
	}

	void test_grid_print2 () {
		Species f('f');
		Grid g(8,8);

		g.place(f, 0, 0);
		g.place(f, 1, 1);
		g.place(f, 7, 7);

		/* uncomment these two lines to see the print
		 * messes up Valgrinds output format otherwise
		 * Should look like:
		 * 
		 * Turn = 0.
		 *   01234567
		 * 0 f.......
		 * 1 .f......
		 * 2 ........
		 * 3 ........
		 * 4 ........
		 * 5 ........
		 * 6 ........
		 * 7 .......f
		 * 
		 */
		std::cout << std::endl;
		g.print();
	}

	void test_grid_print3 () {
		Species f('f');
		Species h('h');
		Species r('r');
		Grid g(5,5);

		g.place(f, 1, 2);
		g.place(h, 3, 1);
		g.place(r, 3, 3);

		/* uncomment these two lines to see the print
		 * messes up Valgrinds output format otherwise
		 * Should look like:
		 * 
		 * Turn = 0.
		 *   01234
		 * 0 .....
		 * 1 ..f..
		 * 2 .....
		 * 3 .h.r.
		 * 4 .....
		 * 
		 */
		std::cout << std::endl;
		g.print();
	}

	void test_grid_update1 () {
		Grid g(4,4);
		CPPUNIT_ASSERT(g._t == 0);

		g.update();
		CPPUNIT_ASSERT(g._t == 1);

		g.update();
		g.update();
		CPPUNIT_ASSERT(g._t == 3);
	}

	void test_grid_update2 () {
		Grid g(5, 5);
		Species h('h');
		h.addControl("if_wall", 3);
		h.addAction("hop");
		h.addControl("go", 0);
		h.addAction("right");
		h.addControl("go", 0);
		Creature* a = g.place(h, 0, 0, Creature::EAST);

		g.update();
		CPPUNIT_ASSERT(g.get(0, 1) == a);
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 1);
		
		g.update();
		g.update();
		g.update();
		g.update();
		CPPUNIT_ASSERT(g.get(0,3) == 0);
		CPPUNIT_ASSERT(g.get(0,4) == a);
		CPPUNIT_ASSERT(a->_d == Creature::SOUTH);
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 4);
		CPPUNIT_ASSERT(a->_uc == 5);
		CPPUNIT_ASSERT(g._t == 5);
	}

	void test_grid_update3 () {
		Grid g(5, 5);
		Species h('h');
		Species i('i');
		h.addAction("hop");
		i.addAction("hop");
		i.addControl("go", 0);

		Creature* a = g.place(h, 1, 1, Creature::SOUTH);
		Creature* b = g.place(i, 2, 3, Creature::NORTH);

		g.update();
		//g.print();
		CPPUNIT_ASSERT(a->_r == 2);
		CPPUNIT_ASSERT(b->_r == 1);
		CPPUNIT_ASSERT(a->_uc == 1);
		CPPUNIT_ASSERT(b->_uc == 1);

		g.update();
		//g.print();
		CPPUNIT_ASSERT(a->_r == 2);
		CPPUNIT_ASSERT(b->_r == 0);
		CPPUNIT_ASSERT(a->_uc == 2);
		CPPUNIT_ASSERT(b->_uc == 2);
	}

	void test_grid_simulate1 () {
		Grid g(5, 5);
		Species t('t');
		t.addControl("if_wall", 3);
		t.addAction("hop");
		t.addControl("go", 0);
		t.addAction("right");
		t.addControl("go", 0);

		Creature* a = g.place(t, 0, 0, Creature::EAST);
		g.simulate(5);
		CPPUNIT_ASSERT(a->_r == 0);
		CPPUNIT_ASSERT(a->_c == 4);
		CPPUNIT_ASSERT(a->_d == 3);
		CPPUNIT_ASSERT(a->_uc == 5);
		CPPUNIT_ASSERT(g._t == 5);
	}

	void test_grid_simulate2 () {
		Grid g(5, 5);
		Species t('t');
		t.addControl("if_wall", 3);
		t.addAction("hop");
		t.addControl("go", 0);
		t.addAction("right");
		t.addControl("go", 0);

		Creature* a = g.place(t, 0, 0, Creature::EAST);
		g.simulate(10);
		CPPUNIT_ASSERT(a->_r == 4);
		CPPUNIT_ASSERT(a->_c == 4);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_uc == 10);
		CPPUNIT_ASSERT(g._t == 10);
	}

	void test_grid_simulate3 () {
		Grid g(5, 5);
		Species t('t');
		t.addControl("if_wall", 3);
		t.addAction("hop");
		t.addControl("go", 0);
		t.addAction("right");
		t.addControl("go", 0);

		Creature* a = g.place(t, 0, 0, Creature::EAST);
		Creature* b = g.place(t, 4, 4, Creature::EAST);

		g.simulate(10);
		CPPUNIT_ASSERT(a->_r == 4);
		CPPUNIT_ASSERT(a->_c == 4);
		CPPUNIT_ASSERT(a->_d == 0);
		CPPUNIT_ASSERT(a->_uc == 10);
		CPPUNIT_ASSERT(b->_r == 1);
		CPPUNIT_ASSERT(b->_c == 0);
		CPPUNIT_ASSERT(b->_d == 1);
		CPPUNIT_ASSERT(b->_uc == 10);
		CPPUNIT_ASSERT(g._t == 10);
	}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    
	CPPUNIT_TEST(test_instruction1);
	CPPUNIT_TEST(test_instruction2);
	CPPUNIT_TEST(test_instruction3);

	CPPUNIT_TEST(test_species_constructor1);
	CPPUNIT_TEST(test_species_constructor2);
	CPPUNIT_TEST(test_species_constructor3);
	CPPUNIT_TEST(test_species_addInstruction1);
	CPPUNIT_TEST(test_species_addInstruction2);
	CPPUNIT_TEST(test_species_addInstruction3);
	CPPUNIT_TEST(test_species_tile1);
	CPPUNIT_TEST(test_species_tile2);
	CPPUNIT_TEST(test_species_tile3);
	CPPUNIT_TEST(test_species_getInstruction1);
	CPPUNIT_TEST(test_species_getInstruction2);
	CPPUNIT_TEST(test_species_getInstruction3);
	
	CPPUNIT_TEST(test_creature_constructor1);
	CPPUNIT_TEST(test_creature_constructor2);
	CPPUNIT_TEST(test_creature_constructor3);
	CPPUNIT_TEST(test_creature_tile1);
	CPPUNIT_TEST(test_creature_tile2);
	CPPUNIT_TEST(test_creature_tile3);
	CPPUNIT_TEST(test_creature_ahead1);
	CPPUNIT_TEST(test_creature_ahead2);
	CPPUNIT_TEST(test_creature_ahead3);
	CPPUNIT_TEST(test_creature_direction1);
	CPPUNIT_TEST(test_creature_direction2);
	CPPUNIT_TEST(test_creature_direction3);
	CPPUNIT_TEST(test_creature_hop1);
	CPPUNIT_TEST(test_creature_hop2);
	CPPUNIT_TEST(test_creature_hop3);
	CPPUNIT_TEST(test_creature_infect1);
	CPPUNIT_TEST(test_creature_infect2);
	CPPUNIT_TEST(test_creature_infect3);
	CPPUNIT_TEST(test_creature_control1);
	CPPUNIT_TEST(test_creature_control2);
	CPPUNIT_TEST(test_creature_control3);
	CPPUNIT_TEST(test_creature_update1);
	CPPUNIT_TEST(test_creature_update2);

	CPPUNIT_TEST(test_grid_construct1);
	CPPUNIT_TEST(test_grid_construct2);
	CPPUNIT_TEST(test_grid_construct3);
	CPPUNIT_TEST(test_grid_get1);
	CPPUNIT_TEST(test_grid_get2);
	CPPUNIT_TEST(test_grid_get3);
	CPPUNIT_TEST(test_grid_place1);
	CPPUNIT_TEST(test_grid_place2);
	CPPUNIT_TEST(test_grid_place3);
	CPPUNIT_TEST(test_grid_move1);
	CPPUNIT_TEST(test_grid_move2);
	CPPUNIT_TEST(test_grid_move3);
	CPPUNIT_TEST(test_grid_print1);
	CPPUNIT_TEST(test_grid_print2);
	CPPUNIT_TEST(test_grid_print3);
	CPPUNIT_TEST(test_grid_update1);
	CPPUNIT_TEST(test_grid_update2);
	CPPUNIT_TEST(test_grid_update3);
	CPPUNIT_TEST(test_grid_simulate1);
	CPPUNIT_TEST(test_grid_simulate2);
	CPPUNIT_TEST(test_grid_simulate3);

    CPPUNIT_TEST_SUITE_END();

};



// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);    // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;

    tr.addTest(TestDarwin::suite());

    tr.run();

    cout << "Done." << endl;
    return 0;}
