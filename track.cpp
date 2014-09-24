#include <iostream>
#include "track.h"

using namespace std;

// Standard constructor.
Track::Track(const int n, const string t)
{
    number = n;
    setTitle(t);
}

// Copy constructor.
Track::Track(const Track &t)
{
    number = t.number;
    setTitle(t.title);
}

// Destructor.
Track::~Track() 
{
    // Empty.
}

// Track number.
int Track::getNumber() const 
{
    return number;
}

const string Track::getTitle() const 
{
    return title;
}

void Track::setTitle(const string t) 
{
    title = t;
}

void Track::print() const 
{
    cout << number << ": " << title << '\n';
}

// End of Track class.
//===========================================================================
