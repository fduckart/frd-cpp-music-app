// Music.cpp
// This the primary Music Collection Application class.
// The application is started and driven from the class.

#include <cstdlib>
#include <sstream>
#include <memory>
#include <limits>
#include <assert.h>
#include "music.h"

using namespace std;

// Main function.
int main() 
{
    Music musicApp("music://records.xml");
    musicApp.run();
    
    return 0;
}

// Music application constructor.
Music::Music(const string s) : repository(new Repository(s)) 
{
    assert(repository != 0);
    source = s;
}

// Music application copy constructor.
Music::Music(const Music & m)  : repository(new Repository(m.source)) 
{
    assert(repository != 0);
    source = m.source;
}

// Destructor.
Music::~Music()
{
    delete repository;
    repository = 0;
}

// Access to the music collection repository.
Repository * Music::getRepository()
{
    return repository;
}

// Application command loop.
void Music::run()
{
    bool quit = false;
    string command;
        
    while (quit != true) {
    
        // Get command from user.
        cout << "music> " << flush; 
        getline(cin, command);        
        
        // Do something with command.
        commandDispatcher(command);
               
        if (command == "quit") {
            quit = true;
        }
 
    }
}

// Primary command dispatching.
void Music::commandDispatcher(const string & fullCommand)
{   
    Command cmd(fullCommand);
    
    if (cmd.isEmpty())
        return;  // No command, just return now.
    
    string command(cmd.getPrimary());
            
    if (command == "help") {
        displayHelp();
    }
    else if (command == "add") {
        addRecord();
    }
    else if (command == "delete") {
        deleteRecord(cmd);
    }
    else if (command == "search") {
        searchDispatcher(cmd); 
    }
    else if (command == "count") {
        printRecordCount();
    }
    else if (command == "artists") {
        printArtists();
    }
    else if (command == "list") {
        printRecords(cmd);
    }
    else if (command == "update") {
        updateDispatcher(cmd);
    }
    else if (command == "quit") {
        cout << "Goodbye\n";
    }
    else { 
        printUsageError(command);
    } 
} 

// Searching dispatcher.
// 
// Note: those extra type tests ending with 
// an 's' are an attempt to reduce command confusion,
// since some users might think they are searching the
// 'records', but the non-plural version is actually 
// more consistent within the application overall.  
// The the jury is still out regarding whether this is useful.
void Music::searchDispatcher(Command & cmd) 
{
    string type(cmd.getQualifier());
    string term(cmd.getArguments());
    
    if (type == "id" || type == "ID") {
        searchId(term);
    }
    else if (type == "genre"  || type == "genres") {
        searchGenre(term);
    }
    else if (type == "artist" || type == "artists") {
        searchArtist(term);        
    }
    else if (type == "record" || type == "records") {
        searchRecord(term);
    }
    else if (type == "track"  || type == "tracks") {
        searchTracks(term);
    }
    else {
        printUsageError(type);
    }
}

// Dispatcher for the types of update commands.
void Music::updateDispatcher(Command & cmd) 
{
    string type(cmd.getQualifier());
    
    if (type == "record") {
        updateRecord(cmd);
    }
    else if (type == "track") {
        updateTrack(cmd);
    }
    else {
        cout << "Error: No update-type command found.\n";
        cout << "You must specify a type of 'record' or 'track'.\n";
        cout << "Usage 1:   update record (Record ID)\n";
        cout << "Usage 2:   update track (Record ID) (Track Number)\n";
        cout << "Example 1: update record 100001\n";
        cout << "Example 2: update track 100001 3\n";
        cout << endl; 
    }    
}

void Music::printUsageError(const string &command) 
{
    cout << "Invalid command: " << command << endl;
    cout << "Type 'help' to see command choices." << endl;
}

void Music::printRecordCount() 
{
    Repository * rep = getRepository();
    cout << "Record count: " << rep->getRecordCount() << "\n";
    cout << "Artist count: " << rep->getArtistCount() << "\n";
}

void Music::printDivider() 
{
    cout << "-----------------------------------------";
    cout << "---------------------------------" << endl;
}

// Prompt for and then add record.
void Music::addRecord() 
{
    cout << "Enter Artist Name:  " << flush;
    string artist;
    getline(cin, artist);
 
    cout << "Enter record title: " << flush;
    string title;
    getline(cin, title);
    
    cout << "Enter record genre: " << flush;
    string genre;
    getline(cin, genre);
    
    Repository * rep = getRepository();
    
    int artistId = rep->nextArtistId();
    Artist a(artistId, artist);
    
    string recordId = rep->nextRecordId();
    Record r(recordId, a);
    r.setTitle(title);
    r.setGenre(genre);
  
    // Prompt to add tracks to record.  
    addTracks(r);
    
    // Add the record to the repository.
    rep->addRecord(r);
}

// Prompt for and then add tracks of a given record.
void Music::addTracks(Record & r) 
{    
    string command;
    int trackNum = 1;
    
    cout << "Enter track information (hit CR when done). \n";
    
    while (true) {
        cout << "Track " << trackNum << " ==> " << flush;
        getline(cin, command);
        
        if (command == "") {
            break;
        }
        
        Track t(trackNum, command);
        r.addTrack(t);
        
        trackNum++;
    }
    
    cout << "You entered " << --trackNum << " tracks.\n";
}

// Search the record genre for a given string.
void Music::searchGenre(string & term) 
{
    printDivider();
    
    Repository * rep = getRepository();    
    list<Record> recs = rep->getRecords();
    list<Record>::const_iterator itor;
    for (itor = recs.begin(); itor != recs.end(); ++itor) {
        string genre(itor->getGenre());
        string::size_type position = genre.find(term);
        if (position != string::npos)
            itor->print();                
    } 
    
    printDivider();
}

// Search the artists for a given string.
void Music::searchArtist(string & term) 
{
    printDivider();    
    
    Repository * rep = getRepository();
    list<Artist> artists = rep->getArtists();
    list<Artist>::const_iterator itor;
    for (itor = artists.begin(); itor != artists.end(); ++itor) {
        string nm(itor->getName());
        string::size_type position = nm.find(term);
        if (position != string::npos)
            itor->print();                
    } 
    
    printDivider();
}

// Search the record titles for a given string.
void Music::searchRecord(string & term) 
{    
    printDivider();    
    
    Repository * rep = getRepository();
    list<Record> records = rep->getRecords();
    list<Record>::const_iterator itor;
    for (itor = records.begin(); itor != records.end(); ++itor) {
        const string title(itor->getTitle());
        string::size_type position = title.find(term);
        if (position != string::npos)
            itor->print();                
    } 
    
    printDivider();
}

// Search the record IDs for a given string.
void Music::searchId(string & recordId) 
{
    printDivider();    
        
    Repository * rep = getRepository();
    list<Record> records = rep->getRecords();
    list<Record>::const_iterator itor;
    for (itor = records.begin(); itor != records.end(); ++itor) {
        const string rid(itor->getRecordId());
        string::size_type position = rid.find(recordId);
        if (position != string::npos)
            itor->print();                
    } 
        
    printDivider();
}

// Search the tracks for a given string.
void Music::searchTracks(string & term) 
{
    printDivider();    
   
    Repository * rep = getRepository();
    list<Record> records = rep->getRecords();
    list<Record>::const_iterator itor;
    for (itor = records.begin(); itor != records.end(); ++itor) {

        list<Track> tracks = itor->getTracks();
        list<Track>::const_iterator ir;
     
        for (ir = tracks.begin(); ir != tracks.end(); ++ir) {
            const string title(ir->getTitle());
            string::size_type position = title.find(term);
            if (position != string::npos) {
                cout << "     " 
                     << ir->getNumber()  << ": "
                     << ir->getTitle()    
                     << "  (Record ID: " 
                     << itor->getRecordId() << ")\n";
            }
        }
    }
    
    printDivider();
}

// Print all the records or a specific one based on the command.
void Music::printRecords(Command & cmd) 
{
    printDivider();
    
    // Check to see if there is a qualifing
    // record ID to search against.  
    // Show all records if no qualfier.
    string rid(cmd.getQualifier());
    
    if (cmd.getQualifier().size() > 0) {
        Repository * rep = getRepository();
        Record r = rep->findRecord(rid);
        if (r.getRecordId() != "null")
            printRecord(r);
    }
    else {
        printRecords();
    }
        
    printDivider();
}

// Print individual record details.
void Music::printRecord(Record r) 
{
    r.print();
    
    // Print the record tracks.
    list<Track> tracks = r.getTracks();
    list<Track>::const_iterator ii;
    for (ii = tracks.begin(); ii != tracks.end(); ++ii) {
        cout << "     ";
        ii->print();
    }
}

// Print all of the records details.
void Music::printRecords() 
{
    Repository * rep = getRepository();
    list<Record> records = rep->getRecords();
    list<Record>::const_iterator itor;
    for (itor = records.begin(); itor != records.end(); ++itor) {        
        printRecord(*itor);
    }
}

// Print the artists.
void Music::printArtists() 
{
    printDivider();
    Repository * rep = getRepository();
    list<Artist> artists = rep->getArtists();
    list<Artist>::const_iterator itor;
    for (itor = artists.begin(); itor != artists.end(); ++itor) {
        itor->print();
    } 
    printDivider();
}

void Music::displayHelp() 
{
    printDivider();
    cout << "" << endl
         << "Command Help" << endl
         << "  Use the following commands:" << endl
         << "  add" << endl
         << "    Add a new record to the system." << endl
         << "    " << endl
         << "  delete record (Record ID)" << endl
         << "    Delete artist record by using the Record ID." << endl
         << "    Example: delete record 100000" << endl
         << "    " << endl
         << "  update record (Record ID)" << endl
         << "    Update artist record by using the Record ID." << endl
         << "    Example: update record 100000" << endl
         << "    " << endl
         << "  update track (Record ID) (Track Number)" << endl
         << "    Update track using the Record ID and track number." << endl
         << "    Example: update track 100001 3" << endl
         << "    " << endl
         << "  count" << endl
         << "    Display the number of records in system." << endl
         << "    " << endl
         << "  help" << endl
         << "    Display help on using program." << endl
         << "    " << endl
         << "  list [Record ID]" << endl
         << "    List all or one of the record entries." << endl
         << "    You can show specific record details by" << endl
         << "    using the optional Record ID argument." << endl
         << "    " << endl
         << "  search id     (keyword)" << endl
         << "  search artist (keyword)" << endl
         << "  search genre  (keyword)" << endl
         << "  search record (keyword)" << endl
         << "  search track  (keyword)" << endl 
         << "    Search by category and keyword." << endl
         << "    Example: search genre Punk" << endl
         << "    " << endl
         << "  quit" << endl
         << "    Quit the program." << endl;
    
    printDivider(); 
}

void Music::deleteRecord(Command & cmd) 
{    
    if (cmd.getQualifier() == "") {
        cout << "Error: No delete type command found.\n\n";
        cout << "You must specify an type to delete.\n";
        cout << "The only supported type is 'record'.\n";
        cout << "Example: delete record 100001\n\n";
        return;  // Get out now.    
    }
    
    if (cmd.getArguments() == "") {
        cout << "Error: Record ID empty.\n\n";
        cout << "You must specify a Record ID to delete.\n";
        cout << "Example: delete record 100001\n\n";
        return;  // Get out now.
    }
    
    // Delete the record.  
    // There is no verification prompt, 
    // which might be helpful.
    const string rid = cmd.getArguments();
    cout << "\nDeleting Record ID " << rid << " ...\n";
    Repository * rep = getRepository();
    rep->deleteRecord(rid);
}

// Update a given record.
Record Music::updateRecord(Record &record) 
{
    cout << "Enter Artist Name:  " << flush;
    string artist;
    getline(cin, artist);
 
    cout << "Enter record title: " << flush;
    string title;
    getline(cin, title);
    
    cout << "Enter record genre: " << flush;
    string genre;
    getline(cin, genre);
    
    Repository * rep = getRepository();
        
    int artistId = rep->nextArtistId();
    Artist a(artistId, artist); 
    
    string recordId = record.getRecordId();
    Record r(recordId, a);
    r.setTitle(title);
    r.setGenre(genre);
  
    // Add tracks to record.  
    addTracks(r);
    
    return r;
}

void Music::updateRecord(Command & cmd) 
{    
    string rid(cmd.getArguments());  // Record ID to update.

    // Make sure record ID that the user specified
    // is not empty and that it actually exists.
    
    if (rid == "") {
        cout << "Error: Record ID empty.\n";
        cout << "You must specify a Record ID to update.\n";
        cout << "Example: update record 100001\n\n";
        return;  // Get out now.
    }

    Repository * rep = getRepository();
    Record r = rep->findRecord(rid);
    if (r.getRecordId() == "null") {
        cout << "Error: Record ID " << rid << " not found.\n";
        cout << "Example: update record 100001\n\n";
        return;  // Get out now.    
    }
                
    printDivider();
    cout << "Previous values for " << rid << " ...\n";
    printRecord(r); 
    printDivider();
    
    // Okay, update the record.
    printDivider();
    Record ur = updateRecord(r);   
    rep->updateRecord(ur);        
    printDivider();

}

// Update a specific record track.
void Music::updateTrack(Command & cmd) 
{    
    // Make another command using the arguments of the 
    // orginal command so we can get record id and track.
    Command updateCmd(cmd.getArguments());        
    
    // Make sure record ID that the user specified
    // is not empty and that it actually exists.
    string rid(updateCmd.getPrimary());    
    if (updateCmd.getPrimary() == "") {
        cout << "Error: Record ID empty.\n";
        cout << "You must specify a Record ID to update.\n";
        cout << "Usage:   update track (Record ID) (Track Number)\n";
        cout << "Example: update track 100001 3\n\n";
        return;  // Get out now.
    }

    Repository * rep = getRepository();
    Record r = rep->findRecord(rid);
    if (r.getRecordId() == "null") {
        cout << "Error: Record ID " << rid << " not found.\n";
        cout << "You must specify a Record ID to update.\n";
        cout << "Usage:   update track (Record ID) (Track Number)\n";
        cout << "Example: update track 100001 3\n\n";
        return;  // Get out now.    
    }
    
    string trackNumStr(updateCmd.getQualifier());
    if (trackNumStr == "") {
        cout << "Error: No track number in command found.\n";
        cout << "Usage:   update track (Record ID) (Track Number)\n";
        cout << "Example: update track 100001 3\n\n";
        return;  // Get out now.
    }
            
    // Convert the string of the track number into a
    // integer we can use the locate the track.  
    // Note that the track number string is limited to
    // four characters as a design decision.  The 
    // possible truncation of the string effectively 
    // limits the number of tracks to 9999 items.
    int trackNum = stoi(trackNumStr.substr(0, 4));
        
    // Need to make sure the conversion of the string was to 
    // a valid integer. stoi reports back the min (negative) 
    // int if it could not convert the string to a int.
    // The check is made by making sure the number is 
    // within the range of  valid track numbers.
    if ((trackNum < 1) || (trackNum > r.getTrackCount())) {
        cout << "Error: Invalid track number '" << trackNumStr << "'.\n";
        cout << "Usage:   update track (Record ID) (Track Number)\n";
        cout << "Example: update track 100001 3\n\n";
        return;  // Get out now.
    }
    
    // Okay, we should have an actual track number.
    // Try to find the track, if we can't then bail out.    
    Track t = r.getTrack(trackNum);
    if (t.getNumber() == 0) {
        cout << "Error: Track number " << trackNum << " not found.\n";
        return;  // Get out now.
    }

    cout << "Current track " << trackNum << " value: ";
    cout << t.getTitle() << "\n";
                            
    string newTitle;
    cout << "Enter new track " << trackNum << " value ==> ";
    getline(cin, newTitle);
        
    // Create a new track which we will use
    // to replace the previous track values.
    Track newTrack(trackNum, newTitle);
    r.updateTrack(newTrack);
    rep->updateRecord(r);            
}

// Help function to convert a string to an it.
// Reports back the min (negative) int value
// if it could not convert the string to a int.
int Music::stoi(string intStr) 
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

// End of Artist class.
//===========================================================================
