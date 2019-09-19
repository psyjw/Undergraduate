#ifndef ___Robot__
#define ___Robot__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Robot : public DisplayableObject       // a Tree is a DisplayableObject
{
public:
	Robot();                                 // constructor
	~Robot() { };                            // destructor
	void Display();                         // overloaded virtual display function

private:
	string sequence = "[++++ff++ff][----ff--ff]fff[++++ff++ff][----ff--ff]<|";
	float angle = 30.f;
	void branch();                          // draw branch function
	void getSequence();
	int iter = 2;
	string init = "f";
	vector<string> change;
	vector<char> flags;
};
#endif

