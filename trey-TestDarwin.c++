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
using namespace std;
// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {
  
  // -----------
  // World Tests
  // ------------

  void test_world_constructor() {
    World w(8, 8);
    CPPUNIT_ASSERT( w.rows == 8 && w.cols == 8);
    CPPUNIT_ASSERT( w.grid.size() == 8 && w.grid[0].size() == 8);
  }

  void test_world_constructor_2() {
    World w(7, 8);
    CPPUNIT_ASSERT( w.rows == 7 && w.cols == 8);
    CPPUNIT_ASSERT( w.grid.size() == 7 && w.grid[0].size() == 8);
  }


  void test_world_constructor_3() {
    World w(3, 3);
    CPPUNIT_ASSERT( w.rows == 3 && w.cols == 3);
    CPPUNIT_ASSERT( w.grid.size() == 3 && w.grid[0].size() == 3);
  }

  // -------------
  // Species Tests
  // -------------

  // -------------
  // Constructors
  // ------------

  void test_species_constructor() {
    Species food("food");
    CPPUNIT_ASSERT(food.s_type == "food");
    CPPUNIT_ASSERT(food.piece() == 'f');
  }

   
  void test_species_constructor_2() {
    Species dog("dog");
    CPPUNIT_ASSERT(dog.s_type == "dog");
    CPPUNIT_ASSERT(dog.piece() == 'd');
  }

  void test_species_constructor_3() {
    Species rover("rover");
    CPPUNIT_ASSERT(rover.s_type == "rover");
    CPPUNIT_ASSERT(rover.piece() == 'r');
  }

  // ----------------
  // add_instruction 
  // --------------

  void test_add_instruction() {
    Species f("f");
    f.add_instruction(LEFT);
    f.add_instruction(RIGHT);
    f.add_instruction(GO, 0);
    CPPUNIT_ASSERT( f.program.size() == 3);
    CPPUNIT_ASSERT( f.program[0].op == LEFT );
    CPPUNIT_ASSERT( f.program[1].op == RIGHT );
    CPPUNIT_ASSERT( f.program[2].op == GO && f.program[2].line == 0);
  } 

  void test_add_instruction_2 () {
    Species g("goo");
    g.add_instruction(IF_ENEMY, 3);
    g.add_instruction(HOP);
    g.add_instruction(GO, 0);
    g.add_instruction(LEFT);
    g.add_instruction(GO, 0);
    CPPUNIT_ASSERT( g.program.size() == 5);
  }

  void test_add_instruction_3 () {
    Species h("hoo");
    h.add_instruction(HOP);
    h.add_instruction(GO, 3);
    CPPUNIT_ASSERT( h.program.size() == 2);
    CPPUNIT_ASSERT ( h.program[0].op == HOP);
    CPPUNIT_ASSERT ( h.program[1].op == GO && h.program[1].line == 3 );
  }

  //-------
  // piece
  // -----
  void test_piece() {
    Species h("hoo");
    CPPUNIT_ASSERT(h.piece() == 'h');
  }

  void test_piece_2() {
    Species hoo("h");
    CPPUNIT_ASSERT(hoo.piece() == 'h');
  }

  void test_piece_3() {
    Species boo("ya");
    CPPUNIT_ASSERT(boo.piece() == 'y');
  }

  // ------------------
  // fetch_instruction
  // ------------------
  void test_fetch() {
    Species wa("hoo");
    wa.add_instruction(GO, 1);
    wa.add_instruction(LEFT);
    instruction_t wahoo = wa.fetch_instruction(1);
    CPPUNIT_ASSERT(wahoo.op == LEFT);
  }

  void test_fetch_2() {
    Species yoo("hoo");
    yoo.add_instruction(IF_ENEMY, 2);
    yoo.add_instruction(GO, 3);
    yoo.add_instruction(HOP);
    instruction_t yoohoo = yoo.fetch_instruction(1);
    CPPUNIT_ASSERT(yoohoo.op == GO && yoohoo.line == 3);
  }

  void test_fetch_3() {
    Species ani("mal");
    ani.add_instruction(HOP);
    try {
      instruction_t animal = ani.fetch_instruction(2);
      CPPUNIT_ASSERT(false);
    }
    catch (...) {
      CPPUNIT_ASSERT(true);
    }
  }
  
  // ---------------
  // Creature Tests
  // --------------

  void test_creature_constructor () {
    World w(8, 8);
    Species food("food");
    Creature c(food, 1, 1, NORTH, &w);
    CPPUNIT_ASSERT ( c.direction == NORTH );
    CPPUNIT_ASSERT ( c.row == 1 );
    CPPUNIT_ASSERT ( c.pc == 0 );
    CPPUNIT_ASSERT ( c.specie == food );
    CPPUNIT_ASSERT ( &c == w.grid[1][1] );
  } 

  void test_creature_constructor_2 () {
    World w(7,8);
    Species dog("dog");
    Creature c(dog, 0, 0, SOUTH, &w);
    CPPUNIT_ASSERT(c.direction == SOUTH);
    CPPUNIT_ASSERT(c.row == 0);
    CPPUNIT_ASSERT(c.col == 0);
    CPPUNIT_ASSERT(c.pc == 0);
    CPPUNIT_ASSERT(c.specie == dog);
    CPPUNIT_ASSERT( &c == w.grid[0][0]);
  }

  void test_creature_constructor_3 () {
    World w(3, 3);
    Species d("d");
    Creature c(d, 1, 2, EAST, &w);
    CPPUNIT_ASSERT(c.direction == EAST);
    CPPUNIT_ASSERT(c.row == 1 && c.col == 2);
    CPPUNIT_ASSERT( c.pc == 0 );
    CPPUNIT_ASSERT( c.specie == d);;
    CPPUNIT_ASSERT( &c == w.grid[1][2]);
 }

  // -------------
  // execute_action
  // --------------

  void test_execute_action() {
    World w(3, 3);
    Species dog("dog");
    Creature d(dog, 1, 1, NORTH, &w);
    instruction_t instr;
    instr.op = HOP;
    instr.line = 0;
    d.execute_action(instr);
    CPPUNIT_ASSERT(d.pc == 1 );
    CPPUNIT_ASSERT(d.direction == NORTH );
    CPPUNIT_ASSERT(d.row == 0 );
    CPPUNIT_ASSERT(d.col == 1 );
    CPPUNIT_ASSERT( !( w.grid[1][1]));
    CPPUNIT_ASSERT( w.grid[0][1] == &d );
  }

  void test_execute_action_2() {
    World w(3, 3);
    Species dog("dog");
    Creature d(dog, 1, 1, SOUTH, &w);
    instruction_t instr;
    instr.op = LEFT;
    instr.line = 0;
    d.execute_action(instr);
    CPPUNIT_ASSERT(d.direction == EAST);
    CPPUNIT_ASSERT(d.row == 1);
    CPPUNIT_ASSERT(d.col == 1);
    CPPUNIT_ASSERT( w.grid[1][1] == &d );
    CPPUNIT_ASSERT( d.pc == 1 );
  } 

  void test_execute_action_3() {
    World w(3, 3);
    Species dog("dog");
    Creature d(dog, 1, 1, SOUTH, &w);
    instruction_t instr;
    instr.op = RIGHT;
    instr.line = 0;
    d.execute_action(instr);
    CPPUNIT_ASSERT(d.direction == WEST);
    CPPUNIT_ASSERT(d.row == 1);
    CPPUNIT_ASSERT(d.col == 1);
    CPPUNIT_ASSERT( w.grid[1][1] == &d );
    CPPUNIT_ASSERT( d.pc == 1 );
  } 

  //------------
  // is_control
  // ----------

  void test_is_control() {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    instruction_t instr;
    instr.op = HOP;
    instr.line = 5;
    CPPUNIT_ASSERT(!c.is_control(instr.op));
  }

  void test_is_control_2 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    instruction_t instr;
    instr.op = IF_ENEMY;
    instr.line = 5;
    CPPUNIT_ASSERT(c.is_control(instr.op));
  }

 
  void test_is_control_3 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    instruction_t instr;
    instr.op = IF_EMPTY;
    instr.line = 5;
    CPPUNIT_ASSERT(c.is_control(instr.op));
  }

  // -----
  // left
  // -----
  void test_left () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    c.execute_left();
    CPPUNIT_ASSERT( c.direction == WEST );
    CPPUNIT_ASSERT( c.pc == 1 );
  }

  void test_left_2 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, WEST, &w);
    c.execute_left();
    CPPUNIT_ASSERT( c.direction == SOUTH );
    CPPUNIT_ASSERT( c.pc == 1 );
  }
   
  void test_left_3 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, SOUTH, &w);
    c.execute_left();
    CPPUNIT_ASSERT( c.direction == EAST );
    CPPUNIT_ASSERT( c.pc == 1 );
  }

  // ------
  // Right
  // -----
  void test_right () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    c.execute_right();
    CPPUNIT_ASSERT( c.direction == EAST );
    CPPUNIT_ASSERT( c.pc == 1 );
  }

  void test_right_2 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, WEST, &w);
    c.execute_right();
    CPPUNIT_ASSERT( c.direction == NORTH );
    CPPUNIT_ASSERT( c.row == 1 && c.col == 1 );
    CPPUNIT_ASSERT( c.pc == 1 );
  }
   
  void test_right_3 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, SOUTH, &w);
    c.execute_right();
    CPPUNIT_ASSERT( c.direction == WEST );
    CPPUNIT_ASSERT( c.pc == 1 );
  }

  //-----
  // Hop
  // ----
  void test_hop () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, NORTH, &w);
    c.execute_hop();
    CPPUNIT_ASSERT( c.direction == NORTH );
    CPPUNIT_ASSERT( c.pc == 1);
    CPPUNIT_ASSERT( !w.grid[1][1] );
    CPPUNIT_ASSERT( w.grid[0][1] == &c );
  }

  void test_hop_2 () {
    World w(3, 3);
    Species s("s");
    Creature c(s, 1, 1, SOUTH, &w);
    c.execute_hop();
    CPPUNIT_ASSERT( c.pc == 1 );
    CPPUNIT_ASSERT( !w.grid[1][1] );
    CPPUNIT_ASSERT( w.grid[2][1] == &c );
  }

  void test_hop_3 () {
    World w(4, 4);
    Species s("s");
    Creature c(s, 0, 0, NORTH, &w);
    c.execute_hop();
    CPPUNIT_ASSERT( w.grid[0][0] == &c );
    CPPUNIT_ASSERT( c.pc == 1 );
  }

  // -------
  // Infect
  // -----
  void test_infect () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 2, NORTH, &w);
    Species f("bar");
    Creature c2(f, 1, 2, NORTH, &w);
    c2.pc = 3;
    c.execute_infect();
    CPPUNIT_ASSERT( c2.specie == s );
    CPPUNIT_ASSERT( w.grid[1][2] == &c2 );
    CPPUNIT_ASSERT( w.grid[2][2] == &c );
  }

  void test_infect_2 () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 2, SOUTH, &w);
    Species f("bar");
    Creature c2(f, 3, 2, NORTH, &w);
    c.execute_infect();
    CPPUNIT_ASSERT( c2.specie == s );
    CPPUNIT_ASSERT( w.grid[3][2] == &c2 );
    CPPUNIT_ASSERT( c2.direction == NORTH );
    CPPUNIT_ASSERT( c2.pc == 0 );
  }
    
  void test_infect_3 () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 2, EAST, &w);
    Species f("bar");
    Creature c2(f, 2, 3, SOUTH, &w);
    c2.pc = 4;
    c.execute_infect();
    CPPUNIT_ASSERT( c2.specie == s );
    CPPUNIT_ASSERT( w.grid[2][3] == &c2 );
    CPPUNIT_ASSERT( c2.direction == SOUTH );
    CPPUNIT_ASSERT( c2.pc == 0 );
    CPPUNIT_ASSERT( w.grid[2][2] == &c );
  }

  // --------
  // IS_WALL
  // --------
  
  void test_is_wall () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 0, 0, NORTH, &w);
    CPPUNIT_ASSERT (c.is_wall());
  }

  void test_is_wall_2 () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 3, EAST, &w);
    CPPUNIT_ASSERT (c.is_wall());
  }

  void test_is_wall_3 () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 2, SOUTH, &w);
    CPPUNIT_ASSERT (!c.is_wall() );
  }

  // --------
  // IS_EMPTY
  // -------

  void test_is_empty () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 2, 2, SOUTH, &w);
    CPPUNIT_ASSERT( c.is_empty() );
  }

  void test_is_empty_2 () {
    World w(4, 4);  
    Species s("foo");
    Creature c(s, 2, 2, NORTH, &w);
    Creature c2(s, 1, 2, NORTH, &w);
    CPPUNIT_ASSERT( !c.is_empty() );
    CPPUNIT_ASSERT( c2.is_empty() );
  }

  void test_is_empty_3 () {
    World w(4, 4);
    Species s("foo");
    Creature c(s, 0, 0, NORTH, &w);
    CPPUNIT_ASSERT ( !c.is_empty() );
  }

  //----------
  // IS_ENEMY
  // ---------

  void test_is_enemy () {
    World w(4, 4);
    Species foo("foo");
    Species bar("bar");
    Creature c(foo, 2, 2, NORTH, &w);
    Creature c2(bar, 1, 2, NORTH, &w);
    CPPUNIT_ASSERT( c.is_enemy() );
    CPPUNIT_ASSERT( !c2.is_enemy() );
  }

  void test_is_enemy_2 () {
    World w(4, 4);
    Species foo("foo");
    Species bar("bar");
    Creature c(foo, 2, 2, NORTH, &w);
    Creature c2(bar, 1, 2, SOUTH, &w);
    CPPUNIT_ASSERT( c.is_enemy() );
    CPPUNIT_ASSERT( c2.is_enemy() );
  }

  void test_is_enemy_3 () {
    World w(4, 4);
    Species foo("foo");
    Creature c(foo, 0, 0, NORTH, &w);
    CPPUNIT_ASSERT( !c.is_enemy());
  }

  // -----------
  // CONTROLLER 
  // -----------

  void test_controller_constructor () {
    World w(4, 4);
    Controller c(&w);
    CPPUNIT_ASSERT( c.w == &w );
  }

  void test_controller_constructor_2 () {
    World w(4, 4);
    Species foo("foo");
    Creature c(foo, 2, 2, NORTH, &w);
    Controller con(&w);
    CPPUNIT_ASSERT( c.w == &w);
  }

  void test_controller_constructor_3 () {
    World w(4, 4);
    Species foo("foo");
    Creature c(foo, 1, 2, SOUTH, &w);
    Controller con(&w);
    CPPUNIT_ASSERT( c.w == &w);
  }
  
  //---------------
  // SET_TURN_LIST
  // --------------

  void test_set_turn_list () {
    World w(4, 4);
    Species foo("foo");
    Creature c(foo, 1, 2, SOUTH, &w);
    Creature c2(foo, 1, 3, NORTH, &w);
    Creature c3(foo, 2, 2, EAST, &w);
    Controller cont(&w);
    cont.set_turn_list();
    queue<Creature*> q;
    q.push(&c);
    q.push(&c2);
    q.push(&c3);
    CPPUNIT_ASSERT( q == cont.turn_list );
  }

  void test_set_turn_list_2 () {
    World w(4, 4);
    Species foo("foo");
    Creature c(foo, 1, 1, SOUTH, &w);
    Creature c2(foo, 2, 2, SOUTH, &w);
    Creature c3(foo, 0, 0, NORTH, &w);
    Controller cont(&w);
    cont.set_turn_list();
    queue<Creature*> q;
    q.push(&c3);
    q.push(&c);
    q.push(&c2);
    CPPUNIT_ASSERT( q == cont.turn_list );
  }

  void test_set_turn_list_3 () {
    World w(4, 4);
    Controller c(&w);
    CPPUNIT_ASSERT ( c.turn_list.empty() );
  }  
 
// ------
// suite
// ------


  CPPUNIT_TEST_SUITE(TestDarwin);
  CPPUNIT_TEST(test_world_constructor);
  CPPUNIT_TEST(test_world_constructor_2);
  CPPUNIT_TEST(test_world_constructor_3);
  CPPUNIT_TEST(test_species_constructor);
  CPPUNIT_TEST(test_species_constructor_2);
  CPPUNIT_TEST(test_species_constructor_3);
  CPPUNIT_TEST(test_add_instruction); 
  CPPUNIT_TEST(test_add_instruction_2);
  CPPUNIT_TEST(test_add_instruction_3);
  CPPUNIT_TEST(test_piece);
  CPPUNIT_TEST(test_piece_2);
  CPPUNIT_TEST(test_piece_3);
  CPPUNIT_TEST(test_fetch);
  CPPUNIT_TEST(test_fetch_2);
  CPPUNIT_TEST(test_fetch_3);
  CPPUNIT_TEST(test_creature_constructor);
  CPPUNIT_TEST(test_creature_constructor_2);
  CPPUNIT_TEST(test_creature_constructor_3);
  CPPUNIT_TEST(test_execute_action);
  CPPUNIT_TEST(test_execute_action_2);
  CPPUNIT_TEST(test_execute_action_3);
  CPPUNIT_TEST(test_is_control);
  CPPUNIT_TEST(test_is_control_2);
  CPPUNIT_TEST(test_is_control_3);
  CPPUNIT_TEST(test_left);
  CPPUNIT_TEST(test_left_2);
  CPPUNIT_TEST(test_left_3);
  CPPUNIT_TEST(test_right);
  CPPUNIT_TEST(test_right_2);
  CPPUNIT_TEST(test_right_3);
  CPPUNIT_TEST(test_hop);
  CPPUNIT_TEST(test_hop_2);
  CPPUNIT_TEST(test_hop_3);
  CPPUNIT_TEST(test_infect);
  CPPUNIT_TEST(test_infect_2);
  CPPUNIT_TEST(test_infect_3);
  CPPUNIT_TEST(test_is_wall);
  CPPUNIT_TEST(test_is_wall_2);
  CPPUNIT_TEST(test_is_wall_3);
  CPPUNIT_TEST(test_is_empty);
  CPPUNIT_TEST(test_is_empty_2);
  CPPUNIT_TEST(test_is_empty_3);
  CPPUNIT_TEST(test_is_enemy);
  CPPUNIT_TEST(test_is_enemy_2);
  CPPUNIT_TEST(test_is_enemy_3);
  CPPUNIT_TEST(test_controller_constructor);
  CPPUNIT_TEST(test_controller_constructor_2);
  CPPUNIT_TEST(test_controller_constructor_3);
  CPPUNIT_TEST(test_set_turn_list);
  CPPUNIT_TEST(test_set_turn_list_2);
  CPPUNIT_TEST(test_set_turn_list_3);
  CPPUNIT_TEST_SUITE_END();};

int main() {
  ios_base::sync_with_stdio(false);
  cout << "TestDarwin.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestDarwin::suite());
  tr.run();
  
  cout << "Done." << endl;
  return 0;} 
