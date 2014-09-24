#ifndef ARTIST_H
#define ARTIST_H

#include <iostream>
#include <string>

using namespace std;

class Artist {
  public:
    Artist(const int id, const string);
    Artist(const Artist &);  // Copy constructor.
    
    ~Artist();
    
    void print() const;    
    const int getArtistId() const;
    const string getName() const;
    void setName(const string);
        
  private:
    int artistId;  // Artist ID.
    string name;   // Artist name.
};

#endif
