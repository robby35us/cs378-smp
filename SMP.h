//Person Class


class Person{


static const int NO_MATCH = 0;

private: bool is_free;
private: int* prefs;
private: int number;
private: int match;

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
  is_free = true;
}};
