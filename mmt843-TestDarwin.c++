/**
 * To test the program:
		g++ -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
		valgrind ./TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#include "Darwin.h"

#include <stdexcept>

// ----------
// TestDarwin
// ----------
struct TestDarwin : CppUnit::TestFixture {
	// --------
	// testGrid
	// --------
	void testGrid0 () 
    {
        srand(0);
    	try {
    		Darwin<2, 2> d;
    		// d.initGrid(2, 2);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	void testGrid1 () 
    {
        try {
    		Darwin<-1, 2> d;
    		// d.initGrid(1, 2);
    		CPPUNIT_ASSERT(false);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(true);
        }
	}

	void testGrid2 () 
    {
        try {
    		Darwin<10, 10> d;
    		// d.initGrid(10, 10);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	void testGrid3 () 
    {
       try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
            //CPPUNIT_ASSERT(false);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	// ---------
	// testPlace
	// ---------

	void testPlace0 () 
    {
    	try {
    		Darwin<3, 3> d;
    		// d.initGrid(3, 3);
    		d.place(HOPPER, NORTH, 1, 1);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
    }

	void testPlace1 () 
    {
        try {
    		Darwin<5, 5> d;
    		// d.initGrid(5, 5);
    		d.place(FOOD, EAST, 0, 0);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	void testPlace2 () 
    {
        try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
    		d.place(ROVER, SOUTH, 71, 71);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	void testPlace3 () 
    {
        try {
    		Darwin<72, 72> d;
    		d.initGrid(72, 72);
    		//d.place(TRAP, SOUTH, 72, 72);
    		CPPUNIT_ASSERT(false);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(true);
        }
	}

	// ---------
	// testPlace
	// ---------
    void testFindPrint () 
    {
        try {
    		Darwin<3, 3> d;
    		// d.initGrid(72, 72);
    		d.place(TRAP, WEST, 1, 1);
    		char t1 = d.look(1, 1);
            //d.print();
    		CPPUNIT_ASSERT(t1 == 't');
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
    	}
	}


	void testFind0 () 
    {
        try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
    		d.place(TRAP, WEST, 5, 70);
    		char t1 = d.look(5, 70);
    		CPPUNIT_ASSERT(t1 == 't');
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
    	}
	}

	void testFind1 () 
    {
        try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
    		d.place(ROVER, NORTH, 5, 70);
    		char t1 = d.look(0, 70);
    		CPPUNIT_ASSERT(t1 == '.');
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}

	void testFind2 () 
    {
        try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
    		d.place(TRAP, WEST, 5, 70);
    		d.place(ROVER, SOUTH, 4, 70);
    		char t1 = d.look(5, 70);
    		CPPUNIT_ASSERT(t1 == 't');
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
    	}
	}

	void testFind3 () 
    {
        try {
    		Darwin<72, 72> d;
    		// d.initGrid(72, 72);
    		d.place(ROVER, EAST, 0, 0);
    		d.place(ROVER, NORTH, 71, 71);
    		char t1 = d.look(0, 0);
    		char t2 = d.look(71, 71);
    		bool result = (t1 == t2);
    		CPPUNIT_ASSERT(result == true);
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
        }
	}



    void testHop0 () 
    {
        try {
    		Darwin<5, 5> d;
    		// d.initGrid(72, 72);
    		d.place(HOPPER, EAST, 1, 1);
            //d.print();
            d.step();
            char t1 = d.look(1, 2);
            //d.print();
    		CPPUNIT_ASSERT(t1 == 'h');
    	}

    	catch (const std::exception &e) {
    		CPPUNIT_ASSERT(false);
    	}
	}

    void testHop1 () 
    {
        try {
            Darwin<5, 5> d;
            // d.initGrid(72, 72);
            d.place(HOPPER, EAST, 1, 4);
            //d.print();
            d.step();
            char t1 = d.look(1, 4);
            //d.print();
            CPPUNIT_ASSERT(t1 == 'h');
        }

        catch (const std::exception &e) {
            CPPUNIT_ASSERT(false);
        }
    }

    void testHop2 () 
    {
        try {
            Darwin<5, 5> d;
            // d.initGrid(72, 72);
            d.place(HOPPER, EAST, 1, 1);
            d.place(ROVER, WEST, 1, 2);
            //d.print();
            d.step();
            char t1 = d.look(1, 1);
            char t2 = d.look(1, 2);
            //d.print();
            CPPUNIT_ASSERT(t1 == 'r');
            CPPUNIT_ASSERT(t2 == 'r');
        }

        catch (const std::exception &e) {
            CPPUNIT_ASSERT(false);
        }
    }

    void testHop3 () 
    {
        try {
            Darwin<5, 5> d;
            // d.initGrid(72, 72);
            d.place(HOPPER, EAST, 1, 4);
            //d.print();
            d.step();
            char t1 = d.look(1, 4);
            //d.print();
            CPPUNIT_ASSERT(t1 == 'h');
        }

        catch (const std::exception &e) {
            CPPUNIT_ASSERT(false);
        }
    }

    void testHop4 () 
    {
        try {
            Darwin<5, 5> d;
            // d.initGrid(72, 72);
            d.place(HOPPER, EAST, 1, 1);
            //d.print();
            d.step();
            char t1 = d.look(1, 2);
            //d.print();
            CPPUNIT_ASSERT(t1 == 'h');
        }

        catch (const std::exception &e) {
            CPPUNIT_ASSERT(false);
        }
    }

    void whatever()
    {
        srand(0);
        try {
    		Darwin<5, 5> d;
    		// d.initGrid(72, 72);
    		//d.place(TRAP, EAST, 1, 1);
            d.place(ROVER, NORTH, 0, 1);
            d.print();
            d.step();
            d.print();
            d.step();
            d.print();
            d.print();
            d.step();
            d.print();
            d.step();
            d.print();
            char t1 = d.look(0, 1);
    		CPPUNIT_ASSERT(t1 == 't');
    	}

    	catch (const std::exception &e) 
        {
    		CPPUNIT_ASSERT(false);
    	}
	}


	CPPUNIT_TEST_SUITE(TestDarwin);

	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testGrid1);
	CPPUNIT_TEST(testGrid2);
	CPPUNIT_TEST(testGrid3);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testPlace1);
	CPPUNIT_TEST(testPlace2);
	CPPUNIT_TEST(testPlace3);
    CPPUNIT_TEST(testFindPrint);
	CPPUNIT_TEST(testFind0);
    CPPUNIT_TEST(testHop0);
    CPPUNIT_TEST(testHop1);
    CPPUNIT_TEST(testHop2);
    CPPUNIT_TEST(testHop3);
	CPPUNIT_TEST(testFind1);
	CPPUNIT_TEST(testFind2);
	CPPUNIT_TEST(testFind3);

    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
