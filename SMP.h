//Person Class
//Man Class Preferences structure----- Manprefs[2,3,1,4] --------fav 2    2nd fav - 3
//Woman Class Preferences structre-----Womanprefs[2,3,1,4] -----fav 3    2nd fav - 1
//

class Person{


static const int NO_MATCH = 0;

private: bool is_free; 
protected: int* prefs;   
private: int number;  // unique for man/woman
private: int match;  //number of match //  number of woman/man person is matched to

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


	
	
     
     