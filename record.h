#ifndef RECORD_H
#define RECORD_H

#include <list>
#include <vector>
#include <string>
#include "artist.h"
#include "track.h"

using namespace std;

class Record {
  public:    
    Record(string, int artistId);  // Constructor.
    Record(string, Artist &);      // Constructor.
    Record(const Record &r);       // Copy constructor.
    
    ~Record();
    
    // Functions.
    void print() const;
    
    // Record details.
    const string getRecordId() const;    
    void setTitle(const string);
    const string getTitle() const;    
    const string getGenre() const;
    void setGenre(const string g);
    
    // Artist details.
    Artist * getArtist() const;
    
    // Track details.    
    void addTrack(Track &);
    list<Track> getTracks() const;
    Track getTrack(int) const;
    int getTrackCount();
    void updateTrack(Track &);
    
  private:
    string recordId;
    string title;
    string genre;  
    Artist * artistPtr; 
    vector<Track> tracks;    
    
    // Helper function.
    string itos(int i);
};

#endif
