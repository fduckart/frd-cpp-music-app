#include "genre.h"

// Constructor.
Genre::Genre(const string n)
{
    setName(n);
}

// Copy constructor.
Genre::Genre(const Genre &a)
{
    setName(a.name);
}

// Destructor.
Genre::~Genre() 
{
    // Empty, so far.
}

const string Genre::getName() const 
{
  return name;
}

void Genre::setName(const string n)
{
    name = n;
}

void Genre::print() const 
{
    cout << name << '\n';
}

// End of Genre class.
//===========================================================================
