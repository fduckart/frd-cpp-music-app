#include "artist.h"

// Standard constructor.
Artist::Artist(const int id, const string n)
{
    setName(n);  
    artistId = id;
}

// Copy constructor.
Artist::Artist(const Artist &a)
{
    setName(a.getName());
    artistId = a.getArtistId();    
}

Artist::~Artist() 
{
    // Empty; so far.
}

const int Artist::getArtistId() const {
    return artistId;
}

const string Artist::getName() const 
{
    return name;
}

void Artist::setName(const string n)
{
    name = n;
}

void Artist::print() const 
{
    cout << artistId << '\t' << name << '\n';
}

// End of Artist class.
//===========================================================================
