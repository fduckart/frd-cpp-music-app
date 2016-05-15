#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
#include "command.h"
#include "record.h"
#include "repository.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::istringstream;
using std::numeric_limits;
using std::string;

class Music {
  public:
    Music(const string);
    Music(const Music &);
    ~Music();

    void run();
    Repository * getRepository();

  private:
    // Command dispatching and messages.
    void printUsageError(const string &);
    void commandDispatcher(const string &);
    void updateDispatcher(Command &);
    void displayHelp();
    int stoi(string);

    // Updates.
    void addRecord();
    void deleteRecord(Command &);
    void addTracks(Record &);
    void updateTrack(Command &);
    void updateRecord(Command &);
    Record updateRecord(Record &);

    // Printing.
    void printRecordCount();
    void printArtists();
    void printRecord(Record);
    void printRecords();
    void printRecords(Command &);
    void printDivider();

    // Searching.
    void searchDispatcher(Command &);
    void searchGenre(string & term);
    void searchArtist(string & term);
    void searchRecord(string & term);
    void searchId(string & term);
    void searchTracks(string & term);

    string source; // Path to repository.  Unused so far.
    Repository * repository;  // Data repository.
};

#endif
