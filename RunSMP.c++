#include <iostream> 
#include <iostream> // endl, istream, ostream
#include "SMP.h"
using namespace std;
enum Sex {woman, man};

Sex current_sex = woman;

void fillManArray(Man men[], std::istream& r, int numOfMarriages) {
	int manNum;
	int prefs[500];
	for(int i = 1; i <= numOfMarriages; ++i) {
        	r >> manNum;
		for(int j = 0; j < numOfMarriages; ++j)
			r >> prefs[j];
			men[i - 1] = Man(prefs, manNum); }}

void fillWomanArray(Woman women[], std::istream& r, int numOfMarriages) {
	int womanNum;
	int prefs[500];
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
				if(!prevMatch){	
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


int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    SMP_solve(cin, cout);
    return 0; }
