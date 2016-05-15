#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <vector>

#include "repository.h"
#include "artist.h"
#include "record.h"
#include "track.h"

using std::cout;

// Prototypes for helper functions.
// This could get moved to another file.
const string trim(const string& s);
int max(const int a, const int b);
int stoi(string intStr);

// Standard constructor.
Repository::Repository(const string &s)
{
    source = s;
    maxRecordId = 101;

    load(source);

    // Future: Use the connection source string
    // to do something like... get the data.
}

// Copy constructor.
// Make sure this doesn't get accidentally
// called in some way.  Assert statement inside.
Repository::Repository(const Repository & r)
{
    // Make sure we don't call the copy constructor.
    assert(false);
}

// Destructor.
Repository::~Repository()
{
    // Clean up....
    artists.clear();
    assert(artists.size() == 0);

    recordMap.clear();
    assert(recordMap.size() == 0);
}

int Repository::getRecordCount()
{
    return recordMap.size();
}

// Get a list of the record.
// The records are transfer from the backing
// repository map to a list to be consistent
// with the way artists are returned.
list<Record> Repository::getRecords()
{
    list<Record> lst;
    recordmap_t::const_iterator itor;
    for (itor = recordMap.begin(); itor != recordMap.end(); ++itor) {
        lst.push_back(itor->second);
    }

    return lst;
}

// Get the next available record ID.
// Used when creating a new Record.
// Programmer is responsible to call this
// to get the next id before creating a record.
// Note: the next id logic can probably be moved
// into the Record constructor, or a related
// creational design pattern.
const string Repository::nextRecordId()
{
    return itos(++maxRecordId);
}

void deleteRecordFile(const string recordId)
{
    string fileName = recordId + ".muz.dat";

    errno = 0;
    if  (remove(fileName.data())) {
        cerr << "Error deleting file." << endl;
        exit(1);
    }

    if (errno) {
        cerr << "Error deleting file." << endl;
        exit(1);
    }
}

void Repository::deleteRecord(const string rid)
{
    if (recordMap.size() > 0) {
        recordMap.erase(rid);
        deleteRecordFile(rid);
    }
}

void Repository::updateRecord(Record &record)
{
    // Delete old version of the record and then
    // insert a new record with the updated data.
    // The delete is necessary since the collection
    // is storing copies of the records.
    deleteRecord(record.getRecordId());
    addRecord(record);
}

void Repository::addRecord(Record &record)
{
    Artist * artist = record.getArtist();
    const string name(artist->getName());

    // See if we need to add this artist to the list.
    // TODO: Need to replace simple linear with
    //       something more efficient.
    bool isAlreadyInCollection = false;
    list<Artist> arts = getArtists();
    list<Artist>::const_iterator itor;
    for (itor = arts.begin(); itor != arts.end(); ++itor) {
        if (itor->getName() == name) {
            isAlreadyInCollection = true;
            break;
        }
    }

    // Add artist to collection if necessary.
    if (!isAlreadyInCollection) {
        int aid = artist->getArtistId();
        Artist a(aid, name);
        artists.push_back(a);
    }

    const string id = record.getRecordId();
    recordMap.insert(recordmap_t::value_type(id, record));

    saveRecord(record);
}

Record Repository::findRecord(const string recordId)
{
    list<Record> recs = getRecords();
    list<Record>::const_iterator itor;
    for (itor = recs.begin(); itor != recs.end(); ++itor) {
        if (itor->getRecordId() == recordId) {
            return *itor;
        }
    }

    // Couldn't find record; return 'null' Record.
    return Record("null", 0);
}

int Repository::getArtistCount()
{
    return artists.size();
}

list<Artist> Repository::getArtists()
{
    return artists;
}

// Get the next available artist ID.
// Used when creating a new Artist.
// Programmer is responsible to call this
// to get the next id before creating a Artist.
// Note: the next id logic can probably be moved
// into the Artist constructor, or a related
// creational design pattern.
const int Repository::nextArtistId()
{
    return ++maxArtistId;
}

// Find an artist using the artist id.
Artist Repository::findArtist(const int aid)
{
    list<Artist> arts = getArtists();
    list<Artist>::const_iterator itor;
    for (itor = arts.begin(); itor != arts.end(); ++itor) {
        if (itor->getArtistId() == aid) {
            return *itor;
        }
    }

    // Couldn't find artist; return 'null' Artist.
    return Artist(0, "null");
}

// Find an artist using the artist's name.
Artist Repository::findArtist(const string name)
{
    list<Artist> arts = getArtists();
    list<Artist>::const_iterator itor;
    for (itor = arts.begin(); itor != arts.end(); ++itor) {
        if (itor->getName() == name) {
            return *itor;
        }
    }

    // Couldn't find artist; return 'null' Artist.
    return Artist(0, "null");
}

void Repository::resetMaxArtistId(int artistId)
{
    maxArtistId = max(artistId, maxArtistId);
}

void Repository::resetMaxRecordId(string recordId)
{
    // Convert the string of the record id
    // to a int since we will be incrementing it.
    int rid = stoi(recordId);
    maxRecordId = max(maxRecordId, rid);
}

void Repository::saveRecord(Record &record)
{
    string fileName = record.getRecordId() + ".muz.dat";
    ofstream outFile(fileName.data(), ios::out);

    if (!outFile) {
        cerr << "File could not be opened..\n";
        exit(1);
    }

    outFile << "recordId:     " << record.getRecordId() << "\n";
    outFile << "title:        " << record.getTitle() << "\n";
    outFile << "genre:        " << record.getGenre() << "\n";

    Artist * aPtr = record.getArtist();
    outFile << "artistId:     " << aPtr->getArtistId() << "\n";
    outFile << "artist:       " << aPtr->getName() << "\n";

    // Write out the track data.
    list<Track> tracks = record.getTracks();
    list<Track>::const_iterator ir;
    outFile << "tracks:" << "\n";
    for (ir = tracks.begin(); ir != tracks.end(); ++ir) {
        outFile << "track " << ir->getNumber()
                << ":      " << ir->getTitle() << "\n";
    }

    outFile << "total-tracks: " << record.getTrackCount() << "\n";

    outFile.close();
}

// Load the record data.
// The source argument is not used at this time, is
// a place holder for a connection string of some kind.
void Repository::load(const string &source)
{

    if (!artists.empty())
        artists.clear();

    if (!recordMap.empty())
        recordMap.clear();

    assert(artists.size() == 0);
    assert(recordMap.size() == 0);

    vector<string> files = readDir();
    for (unsigned int i = 0; i < files.size(); i++) {
        map<string, string> values = getFieldValueMap(files[i]);

        int artistId = stoi(values["artistId"]);
        string artist = values["artist"];
        Artist a(artistId, artist);
        artists.push_back(a);

        string recordId = values["recordId"];
        string title = values["title"];
        string genre = values["genre"];
        Record r(recordId, a);
        r.setTitle(title);
        r.setGenre(genre);

        int trackCount = stoi(values["total-tracks"]);
        for (int i = 1; i <= trackCount; i++) {
            string key = "track " + itos(i);
            Track t(i, values[key]);
            r.addTrack(t);
        }

        // OK, add it to the collection.
        recordMap.insert(recordmap_t::value_type(r.getRecordId(), r));

        // Make sure the properly set so we don't ever
        // try to issue an ID that's already in use.
        resetMaxArtistId(artistId);
        resetMaxRecordId(recordId);
    }

    // If the max Record ID value not greater than
    // 100 right now, something bad happenned.
    // The min record ID is 101 for a empty
    // system, although record IDs 1 through 99
    // can be and are reserved for testing.
    assert(maxRecordId > 100);
}

// Read the music data files off of the file system.
// Note that the music data file extension has changed
// since version 1 of this program.  That's to ensure
// that a older sytle music file is not accidently.
vector<string> Repository::readDir()
{
    vector<string> files;
    const string ext = ".muz.dat";  // Music file extension.

    DIR *ptrDir;
    struct dirent *ptrEntry;

    ptrDir = opendir("."); // "." is the current directory.
    if (!ptrDir) {
        cerr << "Error: cannot open directory to read music files.";
        exit(1);
    }

    errno = 0;
    while ((ptrEntry = readdir(ptrDir))) {
        string fileName(ptrEntry->d_name);
        string::size_type pos = fileName.find(ext, 0);

        // Make note of which files actually
        // ends with a music file extension.
        if (string::npos != pos) {
            if ((fileName.size() - pos - ext.size()) == 0) {
                files.push_back(fileName);
            }
        }
    }

    if (errno) {
        cerr << "Error: there was an error reading the directory.";
        exit(1);
    }

    if (closedir(ptrDir)) {
        cerr << "Error: there was an error closing the directory.";
        exit(1);
    }

    return files;
}

// Create a mapping of fields and values that is
// read from the backing music data file.
map<string, string> Repository::getFieldValueMap(string fileName)
{
    map<string, string> fieldValueMap;

    vector<string> lines = readFile(fileName);
    for (unsigned int i = 0; i < lines.size(); i++) {

        string str(lines[i]);
        string delimiters(":");
        string::size_type lastPos = str.size();

        // Find the first ':' character, and then
        // separate the field and value from each other.
        string::size_type pos = str.find_first_of(':', 0);
        if (string::npos != pos || string::npos != lastPos) {
            const string field = str.substr(0, pos);
            string value = trim(str.substr(pos + 1, lastPos));
            fieldValueMap[field.data()] = value;
        }
    }

    return fieldValueMap;
}

// Load an individual music data file.
vector<string> Repository::readFile(string fileName)
{
    ifstream inFile(fileName.data(), ios::in);
    if (!inFile) {
        cerr << "File could not be opened..\n";
        exit(1);
    }

    vector<string> lines;
    string line;
    while (inFile && !inFile.eof()) {
        getline(inFile, line);
        line = trim(line);
        int len = line.size();
        if (len > 1) {
            lines.push_back(line.substr(0, line.size()));
        }
    }

    inFile.close();

    return lines;
}

// Convert an int to a string.
// Copied from Bjarne Stroustrup's C++ FAQ.
// http://public.research.att.com/~bs
string Repository::itos(int i)
{
    stringstream s;
    s << i;

    return s.str();
}

// Help function to convert a string to an it.
// Reports back the min (negative) int value
// if it could not convert the string to a int.
int Repository::stoi(string intStr)
{
    int num;
    istringstream iss(intStr);
    if (!(iss >> num)) {
        // Error converting to an int.
        // Set to minimum int value.
        num = numeric_limits<int>::min();
    }

    return num;
}



const string trim(const string& s)
{
    if (s.length() == 0)
        return s;

    int f = s.find_first_not_of(" \t");  // Find first char.
    int e = s.find_last_not_of(" \t");   // Find ending char.

    if (e == -1)
        return "";  // Didn't find any chars.

    return string(s, f, e - f + 1);  // Trim off spaces.
}

int max(const int a, const int b)
{
    return (a < b) ? b : a;
}

// End of Repository class.
//===========================================================================
