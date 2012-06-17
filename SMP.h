// -----------------------------
// SMP.h
// Robert Reed and Jordan Graves
// -----------------------------

#include <iostream> 
using namespace std;

// ------------
// Class Person
// ------------

/**
*The person class defines the common data and behaviours of men/women looking for love. 
*This includes, maintaining preferences, number and knowing if they are already engaged,
*and to whom.
*/
class Person{

// -------------------
    // public data members
    // -------------------
  public: static const int NO_MATCH = 0;

   //------------------------
    // non-public data members
    // -----------------------
private: bool is_free; 
public: int prefs[500];   
protected: int number;  // unique for man/woman
protected: int match;  //number of match //  number of woman/man person is matched to

   // ------------------------------------------
    // default constructor - not intended for use
    // ------------------------------------------
    
    /** Makes an invalid person object.
    * This constructor is set to allow an array of Person objects to be construted.*/
public: Person() {}

    // ----------------
    // main constructor
    // ----------------
    
    /** Makes a person looking for a mate, complete with a set of preferences and a person number.
    *@param prefsList A list of ints, representing the number of all the persons of oposite sex, in 
    *	preference order.
    *@param numberOfPerson Is an identifying integer.*/
public: Person(int prefsList[], int numberOfPerson) 
{
is_free = true;
for(int i = 0; i < 500; i++)
	prefs[i] = prefsList[i]; // prefsList[0]
number = numberOfPerson;
match = NO_MATCH;
}

// --------
    //Accessors
    // --------

public: bool isFree() { return is_free;} //checks if person is free
public: int getNumber() { return number; } 
public: int getMatch() {return match; }

    // -------------
    // Person.Engage
    // -------------
    
    /** Engages the person to the person with the number given.
    * @param matchTo The number of their betrothed. */
public: void engage(int matchTo) // matches person to matchTo 
{ match = matchTo;
  is_free = false; }

    // ----------------
    // Person.disengage
    // ----------------
    
    /** Cancles the person's engagement to there previous match, if any.
    * NOTE: This is one sided only, This method has no effect on the other person. */
public: void disengage() // Haha, I made a funny
{  
  match = NO_MATCH;
  is_free = true;}
};
  
    
// ---------
// Class Man 
// ---------

/** A man is a Person. He is the one who proposes. */
class Man : public Person {

      // ------------------------------------------
    // default constructor - not intended for use
    // ------------------------------------------
    
    /** Makes an invalid man object.
    * This constructor is set to allow an array of man objects to be construted.*/
public: Man() {}

    // --------------------
    // Private data members
    // --------------------
    
    // The woman he prefers most from the woman he has not proposed to.
private: int next_woman;

    // ----------------
    // main constructor
    // ----------------
    
    /** Makes a man looking for a mate, complete with a set of preferences and a person number.
    *@param prefsList A list of ints, representing the number of all the women, in order of his preferences.
    *@param numberOfMan Is an identifying integer.*/
public: Man(int prefsList[], int numberOfPerson) 
   : Person(prefsList, numberOfPerson) {			
   next_woman = 0; }

    // -----------
    // Man.propose
    // -----------
    /** @Return the number of a woman he has yet to propose to. His choice is
    * based on his preferences. */
public: int propose() {
	int i = next_woman;
	++next_woman;
	 return prefs[i]; }
};

/** A woman is a Person. She is the one who chooses whether or not to accept a propsal. 
* She is fickle and will accepted a man, if already engaged, if she prefers the new suitor
* to her current fiancee. */
class Woman : public Person {
  
      // --------------------
    // Private data members
    // --------------------
  
    /** We want a structure that allows us to look up a particular Man's ranking, 
    * from the prespective of the Woman, by just his identification number in constant time.
    * revPrefs uses the idendification numbers as the indices and their ranks as the cell-values. */
  private: int* revPrefs;
  
      // ------------------------------------------
    // default constructor - not intended for use
    // ------------------------------------------
    
    /** Makes an invalid Woman object.
    * This constructor is set to allow an array of Woman objects to be construted.*/
  public: Woman() {}
  
    // ----------------
    // Main constructor
    // ----------------
  
    /** Makes a woman looking for a mate. complete with a set of preferences and a person number.
    * @param prefsList Is the list of preferences. 
    * @param revPrefs Is a list the same size as the prefsList, will be changed. 
    * @param length is the length of prefsList
    * @param numberOfWoman the womans' identifying number*/
  public: Woman(int prefsList[], int length, int numberOfPerson) 
   : Person(prefsList, numberOfPerson) {
	  
      revPrefs = new int[length];
      for(int pref = 0; pref < length; ++pref) {
         int manNum = prefs[pref];
	 revPrefs[manNum - 1] = pref + 1;}
   }
 
     // ---------------
    // Woman.wants_change_to
    // ---------------
    
    /** The woman needs to decide if she prefers the man to her current fiancee
    *@param possMatch new man's identifying number
    *@return true for yes and false for no. */
  public: bool wants_change_to(int possMatch) {
    if (revPrefs[match - 1] <= revPrefs[possMatch - 1])
      return false;
    else
      return true; }

    // --------------
    // Woman.acceptProposal
    // --------------

    /** Asks the woman if she would like to be engaged. 
    * @param numberOfMan The new man's identifying number.
    * @return true for yes and false for no. */
  public: bool acceptProposal(int numberOfMan) {
     if(isFree() || wants_change_to(numberOfMan)) {
        engage(numberOfMan);
	    return 1;}
    return 0;}
};	
	

// ------------
// fillManArray
// ------------
/** Read in the input information for all of the men's preferences and build
* a list of Man objects to put them in.
* @param men the array to put the men objects into. Will be altered.
* @param r an istram
* @param numOfMarriages The number of matches that need to be arranged */

void fillManArray(Man men[], std::istream& r, int numOfMarriages) {
	int manNum;
	int prefs[500];
	for(int i = 1; i <= numOfMarriages; ++i) {
        	r >> manNum;
		for(int j = 0; j < numOfMarriages; ++j) {
			r >> prefs[j];	}
			men[i - 1] = Man(prefs, manNum); }}

// --------------
// fillWomanArray
// --------------
/** Read in the input information for all of the men's preferences and build
* a list of Man objects to put them in.
* @param men the array to put the men objects into. Will be altered.
* @param r an istram
* @param numOfMarriages The number of matches that need to be arranged */
void fillWomanArray(Woman women[], std::istream& r, int numOfMarriages) {
	int womanNum;
	int prefs[500];
	for(int i = 1; i <= numOfMarriages; ++i) {
        	r >> womanNum;
		for(int j = 0; j < numOfMarriages; ++j) {
			r >> prefs[j]; }
			women[i - 1] = Woman(prefs, numOfMarriages, womanNum); }}

// --------
// SMP_eval
// --------
/** Given a set of men and women of the same size (numOfMatches), create a stable
* marriage arrangement for everyone.
* @param men the array of menArray
* @param women the array of women
* @param finalMatches an int array to represent the final pairings. The index represents 
* 	the man's number (off by one) and the value at that index, the woman he's engaged to.
* @param numOfMatches The number of man/woman/pairs. */
void SMP_eval (Man men[], Woman women[], int finalMatches[], int numOfMatches ) {
	bool disengaged = false;
	Man* beg = men;
	Man* end = men + numOfMatches;
	while(beg < end) {
		Man* current = beg;
		while((*current).isFree()) {
			int numWoman = (*current).propose();
			Woman* lady = women + numWoman - 1;
			int prevMatch = (*lady).getMatch();
			if((*lady).acceptProposal((*current).getNumber())) {
				(*current).engage(numWoman);
				if(prevMatch){	
					men[prevMatch - 1].disengage();
					disengaged = true; }
			}
		}
		++beg;
	}
	if(disengaged)
		SMP_eval(men, women, finalMatches, numOfMatches);			 
	else
		for(int i = 0; i < numOfMatches; ++i)
			finalMatches[i] = men[i].getMatch();
}	

/** Display the man/woman pairs in numerical order based on the man's identification number.
* using the format prescribed by the sphere website.
* @param finalMatches an array of ints, where the index is the man number offset by one, the value
*	the woman's number.
* @param w a std::ostrearm
* @param numOfMatches the size of final*/
void SMP_print(int finalMatches[], std::ostream& w, int numOfMatches) {
	for(int i = 0; i < numOfMatches; ++i) 
		w << (i + 1) << " " << finalMatches[i] << endl;
}

// -------------
// -------------

/**
* Process the single marriage problem for multiple sets of men and women 
* using the format given on the sphere website.
* @param r a std::istream
* @param w a std::ostream
*/
void SMP_solve (std::istream& r, std::ostream& w) {
    int numIterations;
    int numOfMarriages;
    r >> numIterations;
    while (numIterations > 0) {
    r >> numOfMarriages;
	Woman womenArray[500];
	Man menArray[500];
    fillWomanArray(womenArray,r,numOfMarriages);
    fillManArray(menArray,r,numOfMarriages);	
    int finalMatches[500];
    SMP_eval(menArray, womenArray, finalMatches, numOfMarriages);
	SMP_print(finalMatches, w, numOfMarriages);
	--numIterations;}
}


