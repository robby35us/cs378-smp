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
        Person Pat = Person(a1, 1);
	CPPUNIT_ASSERT(Pat.getNumber() == 1);}

    void test_construct_2 () {
        int a1[2] = {1, 2};
        Person Sam = Person(a1, 3);
	Person Matt = Person(a1, 2);
	CPPUNIT_ASSERT(Sam.getNumber() != Matt.getNumber());}

    void test_construct_3 () {
	int a1[1] = {};
	Person Sam = Person(a1, 250);
	CPPUNIT_ASSERT(Sam.getNumber() == 250);
	CPPUNIT_ASSERT(Sam.getMatch() == 0);} 

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
        Man Matt = Man(a2, 1);
        CPPUNIT_ASSERT(Matt.propose() == 2);
        Man Dudeman = Man(a2, 2);
        CPPUNIT_ASSERT(Dudeman.propose() != 1);
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
       
    void test_propose_3() {
       int a2[1] = {2};
       Man Matt = Man(a2, 1);
       CPPUNIT_ASSERT(Matt.propose() == 2);
       CPPUNIT_ASSERT(Matt.propose() == 0); }




   //---------
   //Woman Constructor
   //-----------


    void test_WomanConstruct_1() {
       int a1[2] = {1, 2};
       Woman Matt = Woman(a1,2, 1);
       CPPUNIT_ASSERT(Matt.getMatch() == 0);
       CPPUNIT_ASSERT(Matt.getNumber() == 1);}
       
    void test_WomanConstruct_2() {
       int a2[2] = {2, 1};
       Woman Barak = Woman(a2, 2, 2); 
       CPPUNIT_ASSERT(Barak.isFree() == true);
       Barak.engage(2);
       CPPUNIT_ASSERT(Barak.isFree() == false);
       Barak.disengage();
       CPPUNIT_ASSERT(Barak.isFree() == true);}
       
    void test_WomanConstruct_3() {
      int a2[2] = {2, 1};
      Woman Matt = Woman(a2,2, 1);
      Person woman = Person(a2, 1);
      Matt.engage(woman.getNumber());
      CPPUNIT_ASSERT(Matt.isFree() == false);
      CPPUNIT_ASSERT(Matt.getMatch() == 1); }
    
 //woman.wants_to_change   
    
    void test_wct_1() {
       int a1[5] = {1, 2, 3, 4, 5};
       Woman Drew = Woman(a1,5, 1); 
       Drew.engage(3);
       CPPUNIT_ASSERT(Drew.getMatch() == 3);
       CPPUNIT_ASSERT(Drew.wants_change_to(1));}
       
    void test_wct_2() {
       int a1[5] = {1, 2, 3, 4, 5};
       Woman Drew = Woman(a1,5, 1); 
       Drew.engage(3);
       CPPUNIT_ASSERT(Drew.getMatch() == 3);
       CPPUNIT_ASSERT(!Drew.wants_change_to(5));}
       
   void test_wct_3() {
       int a1[5] = {1, 2, 3, 4, 5};
       Woman Drew = Woman(a1,5, 1); 
       Drew.engage(3);
       CPPUNIT_ASSERT(Drew.getMatch() == 3);
       CPPUNIT_ASSERT(!Drew.wants_change_to(3));}
 
 //woman.acceptProposal
 
   void test_acceptProposal_1() {
       int a1[5] = {3, 2, 4, 1, 5};
       Woman Drew = Woman(a1,5, 1); 
       Man Keanu = Man(a1, 1);
       CPPUNIT_ASSERT(Drew.acceptProposal(1) == 1);}
       
   void test_acceptProposal_2() {
       int a1[5] = {3, 2, 4, 1, 5};
       Woman Drew = Woman(a1,5, 1); 
       Drew.engage(1);
       CPPUNIT_ASSERT(Drew.acceptProposal(2) == 1);}
       
    void test_acceptProposal_3() {
       int a1[5] = {3, 2, 4, 1, 5};
       Woman Drew = Woman(a1,5, 1); 
       Drew.engage(3);
       CPPUNIT_ASSERT(Drew.acceptProposal(2) == 0);}


///SMP_print ------ void SMP_print(int finalMatches[], std::ostream& w, int numOfMatches)

   void test_SMP_print_1() {
	int finalMatches[1] = {3};
	std::ostringstream w;
	SMP_print(finalMatches, w, 1);
	CPPUNIT_ASSERT(w.str() == "1 3\n"); } 

   void test_SMP_print_2() {
	int finalMatches[4] = {3,2,1,4};
	std::ostringstream w;
	SMP_print(finalMatches, w, 4);
	CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n");}

   void test_SMP_print_3() {
	int finalMatches[4] = {0 ,0 ,0, 0};
 	std::ostringstream w;
	SMP_print(finalMatches, w, 4);
	CPPUNIT_ASSERT(w.str() == "1 0\n2 0\n3 0\n4 0\n"); } 


//fillManArray ---- void fillManArray(Man men[], std::istream& r, int numOfMarriages)

    void test_fillManArray_1() {
	Man men[500];
	std::istringstream r("1 3 2\n");
	fillManArray(men, r , 2);
	CPPUNIT_ASSERT(men[0].getNumber() == 1); }

    void test_fillManArray_2 () {
	Man men[500];
	std::istringstream r("1 4 3 1 2\n2 2 1 3 4 \n3 1 3 4 2\n4 4 3 1 2\n");	
	fillManArray(men, r , 4);
	CPPUNIT_ASSERT(men[0].getNumber() == 1);
	CPPUNIT_ASSERT(men[1].getNumber() == 2);
	CPPUNIT_ASSERT(men[2].getNumber() == 3);
	CPPUNIT_ASSERT(men[3].getNumber() == 4);}

    void test_fillManArray_3() {
	Man men[500];
	std::istringstream r("1 1\n");
	fillManArray(men, r , 1);
	CPPUNIT_ASSERT(men[0].getMatch() == 0);
	CPPUNIT_ASSERT(men[0].getNumber() == 1);}
	
//fillWomanArray ---- void fillWomanArray(Woman women[], std::istream& r, int numOfMarriages)

    void test_fillWomanArray_1() {
	Woman men[500];
	std::istringstream r("1 3 2\n");
	fillWomanArray(men, r , 2);
	CPPUNIT_ASSERT(men[0].getNumber() == 1); }

    void test_fillWomanArray_2 () {
	Woman men[500];
	std::istringstream r("1 4 3 1 2\n2 2 1 3 4 \n3 1 3 4 2\n4 4 3 1 2\n");	
	fillWomanArray(men, r , 4);
	CPPUNIT_ASSERT(men[0].getNumber() == 1);
	CPPUNIT_ASSERT(men[1].getNumber() == 2);
	CPPUNIT_ASSERT(men[2].getNumber() == 3);
	CPPUNIT_ASSERT(men[3].getNumber() == 4);}

    void test_fillWomanArray_3() {
	Woman men[500];
	std::istringstream r("1 1\n");
	fillWomanArray(men, r , 1);
	CPPUNIT_ASSERT(men[0].getMatch() == 0);
	CPPUNIT_ASSERT(men[0].getNumber() == 1);}
  //SMP_eval ----------void SMP_eval (Man men[], Woman women[], int finalMatches[], int numOfMatches ) {

   void test_SMP_eval_1() {
		int a1[1] =  {1};		
		Man m = Man(a1, 1);
		Woman w = Woman(a1, 1, 1); 
		Man men[1] = {m};
		Woman women[1] = {w};
		int finalMatches[500];
		SMP_eval(men, women, finalMatches, 1);
		CPPUNIT_ASSERT(finalMatches[0] == 1); }

    void test_SMP_eval_2() {
		//woman prefs
	int wprefs1[4] = {4,3,1,2};
        int wprefs2[4] = {2,1,3,4};
        int wprefs3[4] = {1,3,4,2};
        int wprefs4[4] = {4,3,1,2};
		//man prefs
	int mprefs1[4] = {3,2,4,1};
	int mprefs2[4] = {2,3,1,4};
	int mprefs3[4] = {3,1,2,4};
	int mprefs4[4] = {3,2,4,1};

	Woman w1 = Woman(wprefs1, 4, 1);
	Woman w2 = Woman(wprefs2, 4, 2);
	Woman w3 = Woman(wprefs3, 4, 3);
	Woman w4 = Woman(wprefs4, 4, 4);

	Man m1 = Man(mprefs1, 1);
	Man m2 = Man(mprefs2, 2);
	Man m3 = Man(mprefs3, 3);
	Man m4 = Man(mprefs4, 4);

	Man men[4] = {m1, m2, m3, m4};
	Woman women[4] = {w1, w2, w3, w4};

	int finalMatches[4];

		//SMP_eval(menArray, womenArray, finalMatches, numOfMarriages);

	SMP_eval(men, women, finalMatches, 4);
	CPPUNIT_ASSERT(finalMatches[0] == 3);
	CPPUNIT_ASSERT(finalMatches[1] == 2);
	CPPUNIT_ASSERT(finalMatches[2] == 1);
	CPPUNIT_ASSERT(finalMatches[3] == 4);  }

    void test_SMP_eval_3() {
		//woman prefs
	int wprefs1[7] = {3,4,2,1,6,7,5};
        int wprefs2[7] = {6,4,2,3,5,1,7};
        int wprefs3[7] = {6,3,5,7,2,4,1};
        int wprefs4[7] = {1,6,3,2,4,7,5};
	int wprefs5[7] = {1,6,5,3,4,7,2};
	int wprefs6[7] = {1,7,3,4,5,6,2};
	int wprefs7[7] = {5,6,2,4,3,7,1};
		//man prefs
	int mprefs1[7] = {4,5,3,7,2,6,1};
	int mprefs2[7] = {5,6,4,7,3,2,1};
	int mprefs3[7] = {1,6,5,4,3,7,2};
	int mprefs4[7] = {3,5,6,7,2,4,1};
	int mprefs5[7] = {1,7,6,4,3,5,2};
	int mprefs6[7] = {6,3,7,5,2,4,1};
	int mprefs7[7] = {1,7,4,2,6,5,3};

	Woman w1 = Woman(wprefs1, 7, 1);
	Woman w2 = Woman(wprefs2, 7, 2);
	Woman w3 = Woman(wprefs3, 7, 3);
	Woman w4 = Woman(wprefs4, 7, 4);
	Woman w5 = Woman(wprefs5, 7, 5);
	Woman w6 = Woman(wprefs6, 7, 6);
	Woman w7 = Woman(wprefs7, 7, 7); 


	Man m1 = Man(mprefs1, 1);
	Man m2 = Man(mprefs2, 2);
	Man m3 = Man(mprefs3, 3);
	Man m4 = Man(mprefs4, 4);
	Man m5 = Man(mprefs5, 5);
	Man m6 = Man(mprefs6, 6);
	Man m7 = Man(mprefs7, 7);

	Man men[7] = {m1, m2, m3, m4, m5, m6 ,m7};
	Woman women[7] = {w1, w2, w3, w4, w5, w6, w7};

	int finalMatches[7];

		//SMP_eval(menArray, womenArray, finalMatches, numOfMarriages);

	SMP_eval(men, women, finalMatches, 7);
	CPPUNIT_ASSERT(finalMatches[0] == 4);
	CPPUNIT_ASSERT(finalMatches[1] == 5);
	CPPUNIT_ASSERT(finalMatches[2] == 1);
	CPPUNIT_ASSERT(finalMatches[3] == 3);
	CPPUNIT_ASSERT(finalMatches[4] == 7);
	CPPUNIT_ASSERT(finalMatches[5] == 6);
	CPPUNIT_ASSERT(finalMatches[6] == 2); 
}
   

	



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_construct_1);
    CPPUNIT_TEST(test_construct_2);
    CPPUNIT_TEST(test_construct_3);

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
    CPPUNIT_TEST(test_propose_3);

    CPPUNIT_TEST(test_wct_1);
    CPPUNIT_TEST(test_wct_2);
    CPPUNIT_TEST(test_wct_3);
    
    CPPUNIT_TEST(test_acceptProposal_1);
    CPPUNIT_TEST(test_acceptProposal_2);
    CPPUNIT_TEST(test_acceptProposal_3);

    CPPUNIT_TEST(test_SMP_print_1);
    CPPUNIT_TEST(test_SMP_print_2);
    CPPUNIT_TEST(test_SMP_print_3);

    CPPUNIT_TEST(test_fillWomanArray_1);
    CPPUNIT_TEST(test_fillWomanArray_2);
    CPPUNIT_TEST(test_fillWomanArray_3);
    
    CPPUNIT_TEST(test_fillManArray_1);
    CPPUNIT_TEST(test_fillManArray_2);
    CPPUNIT_TEST(test_fillManArray_3);

    CPPUNIT_TEST(test_SMP_eval_1); 
    CPPUNIT_TEST(test_SMP_eval_2); 
    CPPUNIT_TEST(test_SMP_eval_3);
  

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
