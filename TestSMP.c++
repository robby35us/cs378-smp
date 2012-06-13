// --------------------------------
// projects/collatz/TestSMP.c++
// Copyright (C) 2011
// Glenn P. Downing
// --------------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -ansi -pedantic -lcppunit -ldl -Wall TestSMP.c++ -o TestSMP.c++.app
% valgrind TestSMP.c++.app >& TestSMP.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "SMP.h"

// -----------
// TestSMP
// -----------

struct TestSMP : CppUnit::TestFixture {

    // ----
    // PersonConstructor
    // ----

    void test_construct_1 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Person Jordan = Person(a2, 2);
        Person Sam = Person(a1, 1);}

    void test_construct_2 () {
        int a1[2] = {1, 2};
        Person Sam = Person(a1, 1);}

    // ----
    // Person.getNumber
    // ----

    void test_number_1 () {
        int a1[2] = {1, 2};
        Person Pat = Person(a1, 1);
        int n = Pat.getNumber();
        CPPUNIT_ASSERT(n == 1);}

   void test_number_2 () {
        int a2[2] = {2, 1};
        Person Chris  = Person(a2, 2);
        int n = Chris.getNumber();
        CPPUNIT_ASSERT(n == 2);}

   void test_number_3 () {
        static int a1[2] = {1, 2};
        Person Jordan = Person(a1, 2);
        int n = Jordan.getNumber();
        CPPUNIT_ASSERT(n == 2);}

   void test_number_4 () {
        int a2[2] = {2, 1};
        Person Sam = Person(a2, 1);
        int n = Sam.getNumber();
        CPPUNIT_ASSERT(n == 1);}

    // -----
    // Person.match
    // -----

    void test_match_1 () {
        static int a1[2] = {1, 2};
        Person Pat = Person(a1, 1);
        int m = Pat.getMatch();
        CPPUNIT_ASSERT(m == 0);}

    void test_match_2 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Pat.engage(Chris.getNumber());
        Chris.engage(Pat.getNumber());
        int m = Pat.getMatch();
        CPPUNIT_ASSERT(m == 2);
        CPPUNIT_ASSERT(m == Chris.getNumber());}

    void test_match_3 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Person Jordan = Person(a1, 2);
        Person Sam = Person(a2, 1);
        Pat.engage(Chris.getNumber());
        int m = Pat.getMatch();
	CPPUNIT_ASSERT(m == 2);
        CPPUNIT_ASSERT(m == Chris.getNumber());
        Pat.engage(Jordan.getNumber());
        m = Pat.getMatch();
	CPPUNIT_ASSERT(m == 2);
        CPPUNIT_ASSERT(m == Jordan.getNumber());
        Pat.engage(Sam.getNumber());
        m = Pat.getMatch();
	CPPUNIT_ASSERT(m == 1);
        CPPUNIT_ASSERT(m == Sam.getNumber());}



    // -----
    // Person.engage
    // -----

    void test_engage_1 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Pat.engage(Chris.getNumber());
        Chris.engage(Pat.getNumber());
        int m = Pat.getMatch();
        CPPUNIT_ASSERT(Pat.isFree() == false);
        CPPUNIT_ASSERT(m == Chris.getNumber());}

    void test_engage_2 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Pat.engage(Chris.getNumber());
        int m = Chris.getMatch();
        CPPUNIT_ASSERT(Chris.isFree() == true);
        CPPUNIT_ASSERT(m == 0);}

    void test_engage_3 () {
        int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Person Jordan = Person(a1, 2);
        Person Sam = Person(a2, 1);
        CPPUNIT_ASSERT(Pat.isFree() == true);
        Pat.engage(Sam.getNumber());
        CPPUNIT_ASSERT(Pat.isFree() == false);
        Sam.engage(Pat.getNumber());
        CPPUNIT_ASSERT(Pat.isFree() == false);
        CPPUNIT_ASSERT(Sam.isFree() == false);}
        
    //------
    // Person.disengage
    //-------

    void test_disengage_1() {
 	int a1[2] = {1, 2};
        int a2[2] = {2, 1};
        Person Pat = Person(a1, 1);
        Person Chris  = Person(a2, 2);
        Pat.engage(Chris.getNumber());
        Chris.engage(Pat.getNumber());
        CPPUNIT_ASSERT(Pat.isFree() == false);
        Pat.disengage();
        CPPUNIT_ASSERT(Pat.isFree() == true);
        CPPUNIT_ASSERT(Chris.isFree() == false);
        CPPUNIT_ASSERT(Pat.getMatch() == 0); }

   void test_disengage_2() {
  	static int a1[2] = {1, 2};
        Person Pat = Person(a1, 1);
        Pat.disengage();
        CPPUNIT_ASSERT(Pat.isFree() == true);
        CPPUNIT_ASSERT(Pat.getMatch() == 0); }

   void test_disengage_3() {
        static int a1[2] = {1, 2};
 	Person Sam = Person(a1, 1);
        Sam.engage(47);
        CPPUNIT_ASSERT(Sam.isFree() == false);
        Sam.disengage();
        CPPUNIT_ASSERT(Sam.isFree() == true);
        Sam.disengage();
        CPPUNIT_ASSERT(Sam.isFree() == true);
        CPPUNIT_ASSERT(Sam.getMatch() == 0); }

    // ---------------
    // Man.Constructor 
    // ---------------
    
    
    void test_ManConstruct_1() {
       int a1[2] = {1, 2};
       Man Matt = Man(a1, 1);
       CPPUNIT_ASSERT(Matt.getMatch() == 0);
       CPPUNIT_ASSERT(Matt.getNumber() == 1);}
       
    void test_ManConstruct_2() {
       int a2[2] = {2, 1};
       Man Barak = Man(a2, 2); 
       CPPUNIT_ASSERT(Barak.isFree() == true);
       Barak.engage(2);
       CPPUNIT_ASSERT(Barak.isFree() == false);
       Barak.disengage();
       CPPUNIT_ASSERT(Barak.isFree() == true);}
       
    void test_ManConstruct_3() {
      int a2[2] = {2, 1};
      Man Matt = Man(a2, 1);
      Person woman = Person(a2, 1);
      Matt.engage(woman.getNumber());
      CPPUNIT_ASSERT(Matt.isFree() == false);
      CPPUNIT_ASSERT(Matt.getMatch() == 1); }
    
    // ----------- 
    // Man.propose
    // -----------
    void test_propose_1() {
       int a1[2] = {1, 2};
       Man Matt = Man(a1, 1);
       CPPUNIT_ASSERT(Matt.propose() == 1);
       CPPUNIT_ASSERT(Matt.propose() == 2);}
       
    void test_propose_2() {
       int a2[2] = {2, 1};
       Man Matt = Man(a2, 1);
       CPPUNIT_ASSERT(Matt.propose() == 2);
       Man Dudeman = Man(a2, 2);
       CPPUNIT_ASSERT(Dudeman.propose() != 1); }
       
//    void test_propose_3() {
//      int a[] = {1};
//      Man OtherDudeMan = Man(a, 1);
//      try {
//	 OtherDudeMan.propose();
//         OtherDudeMan.propose();
//	 CPPUNIT_ASSERT(false);}
//      catch(){}}
      
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_construct_1);

    CPPUNIT_TEST(test_number_1);
    CPPUNIT_TEST(test_number_2);
    CPPUNIT_TEST(test_number_3);
    CPPUNIT_TEST(test_number_4);

    CPPUNIT_TEST(test_match_1);
    CPPUNIT_TEST(test_match_2);
    CPPUNIT_TEST(test_match_3);
    
    CPPUNIT_TEST(test_engage_1);
    CPPUNIT_TEST(test_engage_2);
    CPPUNIT_TEST(test_engage_3);

    CPPUNIT_TEST(test_disengage_1);
    CPPUNIT_TEST(test_disengage_2);
    CPPUNIT_TEST(test_disengage_3);
    
    CPPUNIT_TEST(test_ManConstruct_1);
    CPPUNIT_TEST(test_ManConstruct_2);
    CPPUNIT_TEST(test_ManConstruct_3);
    
    CPPUNIT_TEST(test_propose_1);
    CPPUNIT_TEST(test_propose_2);
//    CPPUNIT_TEST(test_propose_3);
    
    CPPUNIT_TEST_SUITE_END();};

    
// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestSMP.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestSMP::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
