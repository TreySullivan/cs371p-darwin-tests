/*
Benjamin Maxfield
bsm762
projects/darwin/RunDarwin.c++

compile:
  $ g++ -std=c++0x -ldl TestDarwin.c++ -lcppunit -o TestDarwin.c++.app
execute:
  $ valgrind TestDarwin.c++.app &> TestDarwin.out
*/

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"        // TestFixture
#include "cppunit/TextTestRunner.h"       // TestRunner
#include <sstream>

#define private public
#include "Darwin.h"

using std::ostringstream;


// TestDarwin
struct TestDarwin : CppUnit::TestFixture {

  //testInstruction
  void testInstruction1 () {
    Instruction i(HOP, 0);
    CPPUNIT_ASSERT(i.is_action() == true);
    CPPUNIT_ASSERT(i.line() == 0);
    CPPUNIT_ASSERT(i.instr() == HOP);
  }

  void testInstruction2 () {
    Instruction i(GO, 5);
    CPPUNIT_ASSERT(i.is_action() == false);
    CPPUNIT_ASSERT(i.line() == 5);
    CPPUNIT_ASSERT(i.instr() == GO);
  }

  void testInstruction3 () {
    Instruction i(INFECT, 6);
    CPPUNIT_ASSERT(i.is_action() == true);
    CPPUNIT_ASSERT(i.line() == 6);
    CPPUNIT_ASSERT(i.instr() == INFECT);
  }

  void testSpecies1 () {
    Species s('f');
    s.add_instr(Instruction(GO, 0));
    CPPUNIT_ASSERT(s.prog.size() == 1);
  }

  void testSpecies2 () {
    Species s('f');
    s.add_instr(Instruction(GO, 0));
    s.clear();
    CPPUNIT_ASSERT(s.prog.size() == 0);
  }

  void testSpecies3 () {
    Species s('f');
    s.add_instr(Instruction(GO, 0));
    CPPUNIT_ASSERT(s.get_instr(0).instr() == GO);
    CPPUNIT_ASSERT(s.echo() == 'f');
  }

  void testCreature1() {
    Creature c(FOOD, EAST);
    CPPUNIT_ASSERT(c.get_count() == 0);
    CPPUNIT_ASSERT(c.get_dir() == EAST);
    CPPUNIT_ASSERT(c.has_turn() == false);
    CPPUNIT_ASSERT(c.echo() == 'f');
  }

  void testCreature2() {
    Creature c(FOOD, EAST);
    CPPUNIT_ASSERT(c.get_count() == 0);
    c.incr_count();
    CPPUNIT_ASSERT(c.get_count() == 1);
    c.set_count(3);
    CPPUNIT_ASSERT(c.get_count() == 3);
  }

  void testCreature3() {
    Creature c(FOOD, EAST);
    CPPUNIT_ASSERT(c.get_dir() == EAST);
    c.left();
    CPPUNIT_ASSERT(c.get_dir() == NORTH);
    c.right();
    CPPUNIT_ASSERT(c.get_dir() == EAST);
  }

  void testCreature4() {
    Creature c(FOOD, EAST);
    CPPUNIT_ASSERT(c.has_turn() == false);
    c.give_turn();
    CPPUNIT_ASSERT(c.has_turn() == true);
    c.take_turn();
    CPPUNIT_ASSERT(c.has_turn() == false);
  }

  // testGrid
  void testGrid1 () {
    Grid g(2, 2);
    CPPUNIT_ASSERT(g._r == 2);
    CPPUNIT_ASSERT(g._c == 2);
    CPPUNIT_ASSERT(g._t == 0);
    CPPUNIT_ASSERT(g.pointless_holder.size() == 0);
  }

  void testGrid2 () {
    Grid g(1, 1);
    g.place(FOOD, EAST, 0, 0);
    g.simulate(2,1);
    CPPUNIT_ASSERT(g._r == 1);
    CPPUNIT_ASSERT(g._c == 1);
    CPPUNIT_ASSERT(g._t == 2);
    CPPUNIT_ASSERT(g.pointless_holder.size() == 1);
  }

  void testGrid3 () {
    Grid g(5, 5);
    g.place(ROVER, WEST, 3, 2);
    g.place(FOOD, NORTH, 1, 1);
    g.place(FOOD, SOUTH, 4, 4);
    g.simulate(1000,999);
    CPPUNIT_ASSERT(g._r == 5);
    CPPUNIT_ASSERT(g._c == 5);
    CPPUNIT_ASSERT(g._t == 1000);
    CPPUNIT_ASSERT(g.pointless_holder.size() == 3);
  }

  
  // -----
  // suite
  CPPUNIT_TEST_SUITE(TestDarwin);
  
  CPPUNIT_TEST(testInstruction1);
  CPPUNIT_TEST(testInstruction2);
  CPPUNIT_TEST(testInstruction3);
  CPPUNIT_TEST(testSpecies1);
  CPPUNIT_TEST(testSpecies2);
  CPPUNIT_TEST(testSpecies3);
  CPPUNIT_TEST(testCreature1);
  CPPUNIT_TEST(testCreature2);
  CPPUNIT_TEST(testCreature3);
  CPPUNIT_TEST(testCreature4);
  CPPUNIT_TEST(testGrid1);
  CPPUNIT_TEST(testGrid2);
  CPPUNIT_TEST(testGrid3);
  
  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
  cout << "TestDarwin.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestDarwin::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}