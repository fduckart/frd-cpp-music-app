#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string> 
#include <list>
#include <map>

#include "artist.h"
#include "record.h"

using namespace std;

class Repository {
  public:
    Repository(const string &source);
    Repository(const Repository & r);
    
    ~Repository();
    
    // Artist related data/functions.
    list<Artist> getArtists();  
    int  getArtistCount();   
    const int nextArtistId();
    void printArtists();
    Artist findArtist(const int id);
    Artist findArtist(const string);
    
    // Record related data/functions.
    void saveRecord(Record &record);
    list<Record> getRecords();    
    int  getRecordCount();    
    const string nextRecordId();
    void addRecord(Record &record);
    void deleteRecord(const string);
    void updateRecord(Record &record);
    Record findRecord(const string id);
            
  private:
    void load(const string &source);
    string itos(int i);
    
    string source;

    list<Artist> artists;
    
    int maxRecordId;  // Maybe move to a record manager class.
    int maxArtistId;  // Maybe move to a artist manager class.
    void resetMaxArtistId(int artistId);
    void resetMaxRecordId(string recordId);
    
    // Map to hold records.
    typedef map< const string, Record > recordmap_t;
    recordmap_t recordMap;    
    
    // Helper functions.
    vector<string> readFile(string fileName);
    map<string, string> getFieldValueMap(string fileName);
    vector<string> readDir();
    
};

#endif

