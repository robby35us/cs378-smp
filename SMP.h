//Person Class
//Man Class Preferences structure----- Manprefs[2,3,1,4] --------fav 2    2nd fav - 3
//Woman Class Preferences structre-----Womanprefs[2,3,1,4] -----fav 3    2nd fav - 1
//

class Person{


static const int NO_MATCH = 0;

private: bool is_free; 
protected: int* prefs;   
private: int number;  // unique for man/woman
protected: int match;  //number of match //  number of woman/man person is matched to

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
  
  
  public: Woman(int prefsList[], int length, int numberOfPerson) 
   : Person(prefsList, numberOfPerson) {
      revPrefs = new int[length];
      for(int pref = 0; pref < length; ++pref) {
         int manNum = prefs[pref];
	 revPrefs[manNum - 1] = pref + 1;}
   }
  
  public: int acceptProposal(int numberOfMan) {
     if(isFree()) {
        engage(numberOfMan);
        return 0;}
     else
        if(wants_change_to(numberOfMan)) {
	    match = numberOfMan;
	    return numberOfMan; }
	else
	    return match;
  }
  
  
  public: bool wants_change_to(int possMatch) {
    if (revPrefs[match - 1] <= revPrefs[possMatch - 1])
      return false;
    else { return true; }}
};	
	
     
     