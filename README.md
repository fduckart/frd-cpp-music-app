Music Collection C++ Application

Frank Duckart

**Overview**

This app is a simple command driven interface used to add, 
search, and update a music record collection.  The program
was written for UNIX using the C++ programming language.  The
make file currrently uses the g++ compiler, and that is the
only compiler the program has been tested against.  

To start the program, type "music" at the command prompt.
Example:
$ music

The program displays its own prompt, which looks like:
    music>

This readme file includes some simple output examples of the 
commands.  The output is marked with the word "Example:" followed 
by a series of dashes.  The example output is between the 
dashes.  These examples will show you how to use the program.

**Technology**

The program was developed on Apple Mac OS X using 
GNU g++ version 4.9.1 and GNU make version 3.8.1. 

Note that GNU g++ version 4.9.1 will probably need
to be installed since Apple has moved away from GNU.

**Building the Program**

    $ make all
    
**Cleaning up**

    $ make clean

**Running the program**

You can view some simple instructions on using the program
by type help from the music> prompt.

Use the help command to see the possible commands.

**Example -- help**

    music> help
    Command Help
      Use the following commands:

      add
        Add a new record to the system.

      delete record (Record ID)
        Delete artist record by using the Record ID.
        Example: delete record 100

      update record (Record ID)
        Update artist record by using the Record ID.
        Example: update record 100

      update track (Record ID) (Track Number)
        Update track using the Record ID and track number.
        Example: update track 101 3

      count
        Display the number of records in system.

      help
        Display help on using program.

      list [Record ID]
        List all or one of the record entries.
        You can show specific record details by
        using the optional Record ID argument.

      search id     (keyword)
      search artist (keyword)
      search record (keyword)
      search genre  (keyword)
        Search by category and keyword.
        Example: search genre Punk

      quit
        Quit the program.



The program provides a few ways to view data in the system.
One way is to use the list command to view the details for
all of the records or for a specific record ID.

**Example: list**

    music> list

    101: Richard & Linda Thompson   Shoot out the Lights   Folk Rock
            1. Don't Renege on Our Love
            2. Walking on a Wire
            3. Man in Need
            4. Just the Motion
            5. Shoot Out the Lights
            6. Back Street Slide
            7. Did She Jump or Was She Pushed?
            8. Wall of Death
    104: Miles Davis   Kind of Blue   Jazz
            1. So What
            2. Fredie Freeloader
            3. Blue in Green
            4. All Blues
            5. Flamenco Sketches

    music> list 104
    104: Miles Davis   Kind of Blue   Jazz
            1. So What
            2. Fredie Freeloader
            3. Blue in Green
            4. All Blues
            5. Flamenco Sketches



Use the add command to add a record and its tracks to the system.

**Example: add**
-------------------------------------------------------------------
    music> add
    Enter Artist Name :  AC/DC
    Enter record title: Let There Be Rock
    Enter record genre: Hard Rock
    Enter track information (hit CR when done).
    Track 1 ==> Go Down
    Track 2 ==> Dog Eat Dog
    Track 3 ==> Let There Be Rock
    Track 4 ==> Bad Boy Boogie
    Track 5 ==> Problem Child
    Track 6 ==>
    You entered 5 tracks.
-------------------------------------------------------------------


Use the delete command to remove a record.  You need to specify 
the delete-type (record) and the record ID in able to remove 
the entry.

**Example: delete record (Record ID)**
-------------------------------------------------------------------
    music> delete record 115
    music> 
-------------------------------------------------------------------


The program provides an update command to change the record and
the track information.  You need to specify which type of update 
you want to use. The two types of update are record and track. 
To update a record, you need to further specify the record ID.
To update a track, you need to specify the record ID and track #.
The record update replaces all of the values for a record.  Then
track update changes a single track.

Use the help command to see the usage pattern.  

**Example: update for specified track**
-------------------------------------------------------------------
    music> update track 104 5
    updating record 104, track 5.
    Current track value:
            5. Flamengo Sketches
    Enter new track 5 value ==> Flamenco Sketches
    You entered: Flamenco Sketches
    music>
-------------------------------------------------------------------


Use the count command to see a simple record count.
**Example: count**
-------------------------------------------------------------------
    music> count
    Record Count: 3
    Artist Count: 3
    music> 
-------------------------------------------------------------------


Searching
The program provides a way to search parts of the record data.
You need to specify which type of search you would like, along
with the keyword(s).  The search is case-sensitive.

The following are the types of possible searching:
    search id     (keyword)
    search artist (keyword)
    search record (keyword)
    search genre  (keyword)

**Example: search by artist and then by genre**
-------------------------------------------------------------------
    music> search artist Miles
    104: Miles Davis   Kind of Blue   Jazz 
    music> search genre Folk
    101: Richard & Linda Thompson   Shoot out the Lights   Folk Rock
    112: Fairport Convention   Unhalfbricking   Folk-Rock
    music>
-------------------------------------------------------------------


**Known Issues:**
* Up arrow to get command history still does not work.
* Music data files need to have UNIX style End Of Line markers.
  Files with CR/LF (i.e., Windows) and CR (Mac) eol markers
  will not read properly.  
  
===================================================================
More Notes --                                  02 March 2006  

All of the functionality is virtually the same as to version 1. 
I did make a slight change in the terminology of record titles,
though, which makes it more consistent throughout the program.
The previous version refered to records during the search as
'title', but then 'record' during adds and updates.  The 'record'
is what it is now used everywhere.

Another change from version 1 is that I moved the genre from
being defined as an artist atribute, to being one on the record.

Regarding the type of File I/O used in the program, I ultimately
relied on the ostream functionality in the C++ libraries for
those sections where the file is written out.  Likewise, the file
reading is done using the standard ifstream from the C++ libraries.
The directory read, however, is done using the technique we went 
over in class.  I chose to use the standard C++ stream libaries
since they are consistent with the use of other C++ library
functions used throughout the program.  I understand that the C++
stream libraries are buffered, which may or may not be an 
advantage in future assigments.  I guess I'm betting that buffered
I/O will be the only option in future assignemnts, which could be
wrong. ;)  The program file I/O is isolated to a single data 
Repository class, though, so future changes to how data I/O is
done should not effect other parts of the program.

