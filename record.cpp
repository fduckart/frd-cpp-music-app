#include <sstream>
#include <assert.h>
#include "record.h"

using namespace std;

// One of the standard constructors.
Record::Record(string id, int aid) 
{  
    recordId = id;
    artistPtr = new Artist(aid, "");
    assert(artistPtr != 0);
}

// One of the standard constructors.
Record::Record(string id, Artist &a) 
{
    recordId = id;
  
    int aid = a.getArtistId();
    const string name = a.getName();
    artistPtr = new Artist(aid, name);
    assert(artistPtr != 0);
}

// Copy constructor.
Record::Record(const Record &r) 
{
    Artist * a = r.getArtist();
    int aid = a->getArtistId();
    const string name = a->getName();
    artistPtr = new Artist(aid, name);
    assert(artistPtr != 0);
  
    recordId = r.getRecordId();
    setTitle(r.getTitle());  
    setGenre(r.getGenre());
  
    // Add in the tracks.
    list<Track> tks = r.getTracks();
    list<Track>::const_iterator ti;
    for (ti = tks.begin(); ti != tks.end(); ++ti) {
        tracks.push_back(*ti);
    }
}

// Destructor.
Record::~Record() 
{  
    // Free up memory used with artist pointer.
    delete artistPtr;
    artistPtr = 0;
}

const string Record::getRecordId() const 
{
    return recordId;
}

const string Record::getTitle() const {
    return title;
}

void Record::setTitle(const string t) 
{
    title = t;
}

const string Record::getGenre() const
{
    return genre;
}

void Record::setGenre(const string g) 
{    
    genre = g;
}

Artist * Record::getArtist() const 
{
    return artistPtr;
}

void Record::print() const  
{
    cout << recordId << ": " << title;
  
    if (artistPtr != 0) {
        cout << "   " << artistPtr->getName() << "  ";
    } 

    cout << "  " << genre << '\n' << flush;
}

void Record::addTrack(Track &track)
{
    tracks.push_back(track);
}

void Record::updateTrack(Track &track)
{
    int trackIndex = track.getNumber() - 1;
    assert(trackIndex >= 0);
    assert(trackIndex < getTrackCount());
    
    tracks.at(trackIndex) = track;
}

list<Track> Record::getTracks() const 
{
    list<Track> lst;
    vector<Track>::const_iterator itor;
    for (itor = tracks.begin(); itor != tracks.end(); ++itor) {
        lst.push_back(*itor);
    } 

    return lst;
}

Track Record::getTrack(int trackNum) const 
{
    list<Track> tks = getTracks();
    list<Track>::const_iterator ti;
    for (ti = tks.begin(); ti != tks.end(); ++ti) {
        if (ti->getNumber() == trackNum) {
            return *ti;   // Found it.
        }
    }
    
    // Didn't find the track, return null track.
    return Track(0, "null");
}

int Record::getTrackCount() 
{
    return tracks.size();
}

// Convert an int to a string.
// Copied from Bjarne Stroustrup's C++ FAQ.
// http://public.research.att.com/~bs
string Record::itos(int i)
{
    stringstream s;
    s << i;
    
    return s.str();
}

// End of Record class.
//===========================================================================
