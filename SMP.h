//Person Class
//

class Person{


static const int NO_MATCH = 0;

private: bool is_free; 
protected: int* prefs;   
private: int number;  // unique for man/woman
protected: int match;  //number of match //  number of woman/man person is matched to

public: Person() {}

public: Person(int prefsList[], int numberOfPerson) 
{
is_free = true;
prefs = prefsList; // prefsList[0]
number = numberOfPerson;
match = NO_MATCH;
}

//Accessors

public: bool isFree() { return is_free;} //checks if person is free
public: int getNumber() { return number; } 
public: int getMatch() {return match; }

//Setters

public: void engage(int matchTo) // matches person to matchTo 
{ match = matchTo;
  is_free = false; }

public: void disengage() // Haha, I made a funny
{  
  match = NO_MATCH;
  is_free = true;}
};
  
class Man : public Person {

public: Man() {}

private: int next_woman;

public: Man(int prefsList[], int numberOfPerson) 
   : Person(prefsList, numberOfPerson) {
   next_woman = 0; }

public: int propose() {
   return prefs[next_woman++]; }
};


class Woman : public Person {
  
  // We want a structure that allows us to look up a particular Man's ranking, 
  // from the prespective of the Woman, by just his identification number in constant time.
  // revPrefs uses the idendification numbers as the indices and their ranks as the cell-values.
  private: int* revPrefs;
  
  public: Woman() {}
  
  public: Woman(int prefsList[], int length, int numberOfPerson) 
   : Person(prefsList, numberOfPerson) {
      revPrefs = new int[length];
      for(int pref = 0; pref < length; ++pref) {
         int manNum = prefs[pref];
	 revPrefs[manNum - 1] = pref + 1;}
   }
 
  public: bool wants_change_to(int possMatch) {
    if (revPrefs[match - 1] <= revPrefs[possMatch - 1])
      return false;
    else
      return true; }

  public: bool acceptProposal(int numberOfMan) {
     if(isFree() || wants_change_to(numberOfMan)) {
        engage(numberOfMan);
	   return 1;}
    return 0;}
};	
	
     
#include <iostream> 
using namespace std;
enum Sex {woman, man};
Sex current_sex = woman;

void fillManArray(Man men[], std::istream& r, int numOfMarriages) {
	int manNum;
	int prefs[numOfMarriages];
	for(int i = 1; i <= numOfMarriages; ++i) {
        	r >> manNum;
		for(int j = 0; j < numOfMarriages; ++j)
			r >> prefs[j];
			men[i - 1] = Man(prefs, manNum); }}

void fillWomanArray(Woman women[], std::istream& r, int numOfMarriages) {
	int womanNum;
	int prefs[numOfMarriages];
	for(int i = 1; i <= numOfMarriages; ++i) {
        	r >> womanNum;
		for(int j = 0; j < numOfMarriages; ++j)
			r >> prefs[j];
			women[i - 1] = Woman(prefs, numOfMarriages, womanNum); }}

void SMP_eval (Man men[], Woman women[], int finalMatches[], int numOfMatches ) {
	bool disengaged = false;
	Man* beg = men;
	Man* end = men + numOfMatches;
	while(beg < end) {
		Man* current = beg;
		while((*current).isFree()) {
			int numWoman = (*current).propose();
			Woman* lady = &women[numWoman - 1];	
			int prevMatch = (*lady).getMatch();
			if((*lady).acceptProposal((*current).getNumber())) {
				(*current).engage(numWoman);
				if(prevMatch){	
					men[prevMatch - 1].disengage();
					disengaged = true;
				}
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

void SMP_print(int finalMatches[], std::ostream& w, int numOfMatches) {
	for(int i = 0; i < numOfMatches; ++i) 
		w << (i + 1) << " " << finalMatches[i] << endl;
}

// -------------
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void SMP_solve (std::istream& r, std::ostream& w) {
    int numIterations;
    int numOfMarriages;
    r >> numIterations;
    while (numIterations != 0) {
        r >> numOfMarriages;
	Woman womenArray[500];
	Man menArray[500];
	current_sex = woman;
        fillWomanArray(womenArray,r,numOfMarriages);
	current_sex = man;
        fillManArray(menArray,r,numOfMarriages);
        int finalMatches[500];
	SMP_eval(menArray, womenArray, finalMatches, numOfMarriages);
        SMP_print(finalMatches, w, numOfMarriages);
        --numIterations;}
}
